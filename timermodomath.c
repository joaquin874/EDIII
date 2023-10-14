/**
 * Utilizando el Timer 1, escribir un código en C para que por cada presión de un pulsador, la 
 * frecuencia de parpadeo de un led disminuya a la mitad debido a la modificación del reloj 
 * que llega al periférico. El pulsador debe producir una interrupción por GPIO0 con 
 * flanco descendente.
*/

#include "LPC17xx.h"

void configTimer(void);
void configGPIO(void);
void configGPIOInt(void);
void TIMER1_IRQHandler(void);
void EINT3_IRQHandler(void);

uint32_t timerValue = 10000000;

int main(void){
    configGPIO();
    configTimer();
    configGPIOInt();   
}

void configGPIO(void){
    //Input P0.21
    LPC_GPIO0->FIODIR &= ~(1<<21);
    LPC_PINCON->PINMODE0 |= (2<<0);
    //Output P0.22
    LPC_GPIO0->FIODIR |= (1<<22);

    LPC_GPIO0->FIOCLR |= (1<<22);
}

void configTimer(void){
    LPC_SC->PCONP |= (1<<2);    //Power on TIMER1 
    LPC_SC->PCLKSEL0 |= (1<<4); //Select micro clock

    //Configuration TIMER
    LPC_TIM1->PR = 0;
    LPC_TIM1->MR0 = timerValue;
    LPC_TIM1->MCR |= (1<<0);
    LPC_TIM1->TCR |= (3<<0);
    LPC_TIM1->TCR &= ~(1<<1);
    NVIC_EnableIRQ(TIMER1_IRQn);
}

void configGPIOInt(void){
    LPC_GPIOINT->IO0IntEnF |= (1<<21);
    LPC_GPIOINT->IO0IntClr |= (1<<21);
    NVIC_EnableIRQ(EINT3_IRQn);
}

void TIMER1_IRQHandler(void){
    if(LPC_TIM1->IR & (1<<0)){
        if(LPC_GPIO0->FIOPIN & (1<<22)){
            LPC_GPIO0->FIOCLR |= (1<<22);
        }
        else{
            LPC_GPIO0->FIOSET |= (1<<22);
        }
        
        LPC_TIM1->MR0 = timerValue;
        LPC_TIM1->TCR |= (1<<1);
        LPC_TIM1->TCR &= ~(1<<1);
        LPC_TIM1->IR |= (1<<0);
    }
}

void EINT3_IRQHandler(void){
    if((LPC_GPIOINT->IntStatus & (1<<0)) && (LPC_GPIOINT->IO0IntStatF & (1<<21))){
        timerValue += timerValue;
        
        LPC_GPIOINT->IO0IntClr |= (1<<21);
    }
}