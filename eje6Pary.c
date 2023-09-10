/**
 * Realizar un programa que configure el puerto P2.0 y P2.1
 * para que provoquen una interrupción por flanco de subida
 * para el primer pin y por flanco de bajada para el segundo.
 * Cuando la interrupción sea por P2.0 se enviará por el pin
 * P0.0 la secuencia de bits 010011010.
 * Si la interrupción es por P2.1 se enviará por el pin P0.1
 * la secuencia 011100110. Las secuencias se envían únicamente
 * cuando se produce una interrupción, en caso contrario la salida de los
 * pines tienen valores 1 lógicos. ¿que prioridad tienen configuradas por
 * defecto estas interrupciones?
*/

#include "LPC17xx.h"
#include <stdio.h>

void EINT3_IRQHandler(void);
void setValues(uint32_t aux[9], int type);
void delay();
uint32_t value[9];

int main(void){
    //Configuramos la interrupcion del puerto P2.0 y P2.1
    //Ademas de P0.0 como salida
    LPC_GPIO2->FIODIR &= ~(3<<0); //Setea como entrada a P2.0 y P2.1
    LPC_GPIO0->FIODIR |= (1<<0);
    LPC_GPIO0->FIODIR |= (1<<1);

    LPC_GPIOINT->IO2IntEnR |= (1<<0);
    LPC_GPIOINT->IO2IntEnF |= (1<<1);
    NVIC_EnableIRQ(EINT0_IRQn);
    while(1){
        LPC_GPIO0->FIOSET |= (3<<0);
    }
}

void EINT3_IRQHandler(void){
    if(LPC_GPIOINT->IO2IntStatR & (1<<0)){
        uint32_t valueaux = {0,1,0,0,1,1,0,1,0};
        setValues(valueaux, 0);
        delay();
    }
    else if(LPC_GPIOINT->IO2IntStatF & (1<<1)){
        uint32_t valueaux = {0,1,1,1,0,0,1,1,0};
        setValues(valueaux, 1);
        delay();
    }
}

void setValues(uint32_t aux[9], int type){
    for(int i=8; i >= 0; --i){
        if(type == 0){
            if(aux[i] == 0){
                LPC_GPIO0->FIOCLR |= (aux[i]<<0);
                delay();
            }
            else{
                LPC_GPIO0->FIOSET |= (aux[i]<<0);
                delay();
            }
        }
        else if(type == 1){
            if(aux[i] == 0){
                LPC_GPIO0->FIOCLR |= (aux[i]<<1);
                delay();
            }
            else{
                LPC_GPIO0->FIOSET |= (aux[i]<<1);
                delay();
            }
        }
    }
}

void delay(){
    for(int i = 0; i < 12000000; i++){
    }
}
