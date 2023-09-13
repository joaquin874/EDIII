/**
 * Escribir un programa en C que permita sacar por los pines P1.16 al P1.23 el equivalente en ascii de "a" si 
 * la interrupción se ha realizado por interrupción de EINT1 y no hay interrupción pendiente de EINT0. 
 * Para el caso en el cual se produzca una interrupción por EINT1 y exista una interrupción pendiente de EINT0 sacar 
 * por el  puerto el equivalente en ascii de "A". La interrupción de EINT1 es por el flanco de subida producido 
 * por un pulsador identificado como "tecla a/A", mientras que la interrupción EINT0 es por el nivel alto de un pulsador 
 * etiquetado como "Activación de Mayusculas". 
 * 
 * Nota: Valerse de la configuración de los niveles de prioridad para que la pulsación conjunta de "Activación de Mayúsculas" 
 * con "tecla a/A" de como resultado a la salida el equivalente en ascii "A".
*/
#include "LPC17xx.h"
#include <stdlib.h>

void configPorts();
void configInt();
void delay();

int main(void){
    configPorts();
    configInt();
}

void configPorts(void){
    //Configuracion del puerto 1 en los pines del 16 al 23 para salida
    LPC_GPIO1->FIODIR |= (0xFF<<16);

}

void configInt(void){
    //Configuracion de los pines P2.10 y P2.11 como interrupcion externa
    LPC_PINCON->PINSEL4 |= (0x01<<20);
    LPC_PINCON->PINSEL4 |= (0x01<<22);
    
    //EINT0 por nivel ALTO y EINT1 por flanco SUBIDA
    LPC_SC->EXTMODE |= (0x02<<0);
    LPC_SC->EXTPOLAR |= (0x03<<0);

    //Limpio las flags de interrupciones por EINT0 y EINT1
    //Se limpian las flag seteando 1 a EXINT
    LPC_SC->EXTINT |= (0x03<<0);

    //Configuracion de las prioridades
    NVIC_SetPriority(EINT0_IRQn,1);
    NVIC_SetPriority(EINT1_IRQn,0);
    
    //Habilito las interrupciones
    NVIC_EnableIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
    return;
}

void EINT0_IRQnHandler(void){
    if(!NVIC_GetPendingIRQ(EINT1_IRQn)){
        char ascii = 'A';
        LPC_GPIO1->FIOSET |= (ascii<<16);
    }
    LPC_SC->EXTINT &= ~(0x01<<1);
}

void EINT1_IRQnHandler(void){
    if(!NVIC_GetPendingIRQ(EINT0_IRQn)){
        char ascii = 'a';
        LPC_GPIO1->FIOSET |= (ascii<<16);
    }
    LPC_SC->EXTINT &= ~(0x01<<1);
}

void delay(void){
    for(int i = 0; i < 10*10^6; i++){}
}