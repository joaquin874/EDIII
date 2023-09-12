/**
 * Considerando pulsadores normalmente abiertos conectados en un extremo a masa y en el otro directamente a las entradas P0.0 y p0.1. 
 * Realizar un programa que identifique en una variable cual o cuales pulsadores han sido presionados. 
 * Las identificaciones posibles a implementar en esta variable van a ser "ninguno", "pulsador 1", "pulsador 2", "pulsador 1 y 2". 
*/
#include "LPC17xx.h"
//#include <stdio.h>

void onled(int value, uint32_t timems);
void delay(int timems);

int main(void){
    LPC_PINCON->PINMODE0 &= ~(0x0F<<0); //Configura el pin P0.0 y P0.1 como pull down
    LPC_GPIO0->FIODIR &= ~(0x03<<0);  //Configura el pin P0.0 y P0.1 como entrada 

    //El pin P0.22 contiene un led
    LPC_GPIO0->FIODIR |= (0x01<<22);

    int pinvalue;
    while(1){
        // pinvalue = 0  ninguno    led prende continuamente    1 seg
        // pinvalue = 1  pulsador1  led prende y apaga 1 vez    2 seg
        // pinvalue = 2  pulsador2  led prende y apaga 2 veces   3 seg
        // pinvalue = 3  pulsador1 y pulsador2  led prende y apaga 3 veces  4 seg
        pinvalue = LPC_GPIO0->FIOPIN & 0x03;
        delay(20000000);
        if(pinvalue == 0){
            onled(1, 12000000);
        }
        else if(pinvalue == 1){
            onled(2, 12000000);
        }
        else if(pinvalue == 2){
            onled(3, 12000000);
        }
        else{
            onled(4, 12000000);
        }
    }
}

void onled(int value, uint32_t timems){
    for(int i = 0; i < value; i++){
        LPC_GPIO0->FIOSET |= (1<<22);
        delay(timems);
        LPC_GPIO0->FIOCLR |= (1<<22);
        delay(timems);
    }
}

void delay(int timems){
    for(int i = 0; i < timems; i++){

    }
}