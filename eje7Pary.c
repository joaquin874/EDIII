/**
 * Realizar un programa que configure el puerto P0.0 y P2.0 para que 
 * provoquen una interrupción por flanco de subida. Si la 
 * interrupción es por P0.0 guardar el valor binario 100111 en la variable 
 * "auxiliar", si es por P2.0 guardar el valor binario 111001011010110.
*/

#include "LPC17xx.h"
#include <stdio.h>

void EINT3_IRQHandler(void);
void delay();
uint32_t auxiliar;

int main(void){
    LPC_GPIO2->FIODIR &= ~(1<<0); //Setea como entrada a P2.0 y P0.0
    LPC_GPIO0->FIODIR &= ~(1<<0);
    
    LPC_GPIOINT->IO0IntEnR |= (1<<0);
    LPC_GPIOINT->IO2IntEnR |= (1<<0);

    //EINT3 se puede utilizar como interrupcion externa de todos los pines del puerto 0 y 2
    NVIC_EnableIRQ(EINT3_IRQn);
    while(1){
    }
}

void EINT3_IRQHandler(void){
    if(LPC_GPIOINT->IO0IntStatR & (1<<0)){
        auxiliar = 0x27;
        LPC_GPIOINT->IO0IntClr &= ~(1<<0);
    }
    else if(LPC_GPIOINT->IO2IntStatR & (1<<0)){
        auxiliar = 0x72D6;
        LPC_GPIOINT->IO2IntClr &= ~(1<<0);
    }
}

void delay(){
    for(int i = 0; i < 12000000; i++){
    }
}
