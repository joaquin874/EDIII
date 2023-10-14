/**
 * Escribir el código que configure el timer0 para cumplir con las 
 * especificaciones dadas en la figura adjunta. (Pag 510 Figura 115 del manual de 
 * usuario del LPC 1769). Considerar una frecuencia de cclk de 100 Mhz y 
 * una división de reloj de periférico de 2.
*/

#include "LPC17xx.h"
void configTimer(void);
void TIMER0_IRQHandler(void);

uint32_t timerValue = 6;
uint32_t prescaleCounter = 1;

int main(void){
    configTimer();
    while(1){
        LPC_TIM0->PR = prescaleCounter;
        prescaleCounter++;
        if(prescaleCounter == 3){prescaleCounter = 0;} 
    }
}


void configTimer(void){
    LPC_SC->PCONP |= (1<<1);    //Power on TIMER1 
    LPC_SC->PCLKSEL0 |= (2<<2); //Tclock = clock/2

    //Configuration TIMER
    LPC_TIM0->PR = 0;
    LPC_TIM0->MR0 = timerValue;
    LPC_TIM0->MCR |= (1<<0);
    NVIC_EnableIRQ(TIMER0_IRQn);
    LPC_TIM0->TCR |= (3<<0);
    LPC_TIM0->TCR &= ~(1<<1);
}


void TIMER0_IRQHandler(void){
    if(LPC_TIM0->IR & (1<<0)){
        LPC_TIM0->MR0 = timerValue;
        LPC_TIM0->TCR |= (1<<1);
        LPC_TIM0->TCR &= ~(1<<1);
        LPC_TIM0->IR |= (1<<0);
    }
}
