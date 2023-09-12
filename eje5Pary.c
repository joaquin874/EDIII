/**
 * Escribir un programa en C que permita realizar un promedio movil con los últimos 8 datos ingresados por el puerto 1. 
 * Considerar que cada dato es un entero signado y está formado por los 16 bits menos significativos de dicho puerto. 
 * El resultado, también de 16 bits, debe ser sacado por los pines P0.0 al P0.11 y P0.15 al P0.18.  
 * Recordar que en un promedio movil primero se descarta el dato mas viejo de los 8 datos guardados, se ingresa un nuevo 
 * dato proveniente del puerto y se realiza la nueva operación de promedio con esos 8 datos disponibles, así sucesivamente. 
 * Considerar el uso de un retardo antes de tomar una nueva muestra por el puerto. 
*/
#include "LPC17xx.h"

//#include <stdio.h>

int average(uint32_t value[8]){
    uint32_t add = 0;
    for(int i = 0; i < 8; i++){
        add += (value[i]);
    }
    return add/8;
}

void delay(){
    for(int i=0 ; i < 10000000 ; ++i); //delay de 1 seg
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
        uint32_t avg2sli = avg2<<16;    //Desplazamiento de los bits para que quede en la posicion LBS
        LPC_GPIO0->FIOSET |= (avg1>>0);
        LPC_GPIO0->FIOSET |= (avg2sli>>15);
    }

}