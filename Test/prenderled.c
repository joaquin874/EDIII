#include "LPC17xx.h"

void delay(void);

int main(void){
    LPC_GPIO2->FIODIR &= ~(1<<13);
    LPC_GPIO2->FIOCLR |= (1<<13);
    while(1){
        LPC_GPIO2->FIOSET |= (1<<13);
        delay();
        LPC_GPIO2->FIOCLR |= (1<<13);
        delay();
    }
}

void delay(){
    for(int i = 0; i < 10000000; i++){
        //NOP
    }
}