/**
 * Escribir un programa para que por cada presión de un pulsador, la frecuencia 
 * de parpadeo de un led disminuya a la mitad debido a la modificación del pre-escaler 
 * del Timer 2. El pulsador debe producir una interrupción por EINT1 con flanco descendente. 
*/

#include "LPC17xx.h"

void configTimer2(void);
void configEINT(void);
void TIMER2_IRQHandler(void);
void EINT1_IRQHandler(void);

uint32_t timerValue = 1000000;
uint32_t prescaleValue = 0;

void configGPIO(void){
    LPC_GPIO0->FIODIR |= (1<<22);
    LPC_GPIO0->FIOCLR |= (1<<22);
}

int main(void){
    configGPIO();
    configTimer2();
    configEINT();
}

void configTimer2(void){
    LPC_SC->PCONP |= (1<<22);   //Power on TIMER2 with PCONP bit 22
    LPC_SC->PCLKSEL1 |= (1<<12);//Select Clock

    LPC_TIM2->PR = prescaleValue;
    LPC_TIM2->MR0 = timerValue;
    LPC_TIM2->MCR &= ~(1 << 0);
    LPC_TIM2->TCR |= (3<<0);
    LPC_TIM2->TCR &= ~(1<<1);
    NVIC_EnableIRQ(TIMER2_IRQn);
}

void configEINT(void){
    LPC_PINCON->PINSEL4 |= (1<<20);
    LPC_PINCON->PINMODE4 &= ~(3<<20);

    LPC_SC->EXTMODE |= (1<<1);  //Active for Egde
    LPC_SC->EXTPOLAR &= ~(1<<1);//Active for Falling Edge

    LPC_SC->EXTINT |= (1<<1);   //Clear flag

    NVIC_EnableIRQ(EINT1_IRQn);
}

void TIMER2_IRQHandler(void){
    if((LPC_TIM2->IR & (1<<0))){
        LPC_TIM2->PR = prescaleValue;
        if(LPC_GPIO0->FIOPIN & (1<<22)){
            LPC_GPIO0->FIOCLR |= (1<<22);
        }
        else{
            LPC_GPIO0->FIOSET |= (1<<22);
        }
        LPC_TIM2->IR = (1<<0);
    }
}

void EINT1_IRQHandler(void){
    if(prescaleValue == 0){
        prescaleValue = 1;
    }
    else{
        prescaleValue *= 2;
    }
    LPC_SC->EXTINT |= (1<<1);
}