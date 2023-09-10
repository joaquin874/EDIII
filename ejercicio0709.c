/**
 * Escribir una funcion de configuracion de interrupcion por
 * GPIO y un handler que modifique la condicion del pin P0.1
 * si se interrumpio por P0.0 y modifique la condicion de P2.1
 * si se interrumpio por P2.0
*/
#include "LPC17xx.h"
#include <stdio.h>

void configGPIO(void);
void configIntr(void);
void EINT3_IRQHandler(void);
void delay(void);

void main(void){
    configGPIO();
    configIntr();
    while(1){

    }
}

void configGPIO(void){
    LPC_GPIO0->FIODIR &= ~(1<<0);
    LPC_GPIO2->FIODIR &= ~(1<<0);

    LPC_GPIO0->FIODIR |= (1<<1);
    LPC_GPIO2->FIODIR |= (1<<1);
}

void configIntr(void){
    LPC_GPIOINT->IO0IntEnR |= (1<<0);
    LPC_GPIOINT->IO2IntEnR |= (1<<0);
    
    LPC_GPIOINT->IO0IntClr |= (1<<0);
    LPC_GPIOINT->IO2IntClr |= (1<<0);
    NVIC_EnableIRQ(EINT3_IRQn);
}

void EINT3_IRQHandler(void){
    if((LPC_GPIOINT->IntStatus & 0x01) && (LPC_GPIOINT->IO0IntStatR & 0x01)){
        LPC_GPIO0->FIOSET |= (1<<1);
        delay();
        delay();
        LPC_GPIO0->FIOCLR |= (1<<1);
        LPC_GPIOINT->IO0IntClr |= (1<<0);
    }
    else if((LPC_GPIOINT->IntStatus & 0x02) && (LPC_GPIOINT->IO2IntStatR & 0x01)){
        LPC_GPIO2->FIOSET |= (1<<1);
        delay();
        delay();
        LPC_GPIO2->FIOCLR |= (1<<1);
        LPC_GPIOINT->IO2IntClr |= (1<<0);
    }
}

void delay(void){
    for(int i = 0; i < 12000000; i++){

    }
}