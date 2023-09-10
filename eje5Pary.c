#include "LPC17xx.h"
#include <stdio.h>

int average(uint32_t value[8]){
    uint32_t add = 0;
    for(int i = 0; i < 8; i++){
        add += (value[i]);
    }
    return add/8;
}

void delay(){
    for(int i=0 ; i < 12000000 ; ++i); //delay of 4 seconds
}
int main(void){
    // Tomando en cuenta que los valores de los pines del P1.0 al P1.15
    // Estan configurados como entrada y reciben valores
    LPC_GPIO0->FIODIR |= (0xF0FFF<<0);   //Configuracion para output P0.0 al P0.11 y P0.15 al P0.18
    uint32_t value[8] = {0,0,0,0,0,0,0,0};
    uint32_t avgvalue;
    int i = -1;
    while(1){
        i++;
        LPC_GPIO0->FIOCLR |= (0x0F0FFF<<0);
        delay();
        value[i] += (LPC_GPIO1->FIOPIN & 0xFFFF);
        avgvalue = average(value);
        if(i >= 7){
            i = -1;
        }
        uint32_t avg1 = avgvalue & 0x00FFF;
        uint32_t avg2 = avgvalue & 0XF0000;
        LPC_GPIO0->FIOSET |= (avg1<<0);
        LPC_GPIO0->FIOSET |= (avg2>>15);
    }

}