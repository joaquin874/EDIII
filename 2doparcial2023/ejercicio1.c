/**
 * Programar el microcontrolador LPC1769 en un codigo de lenguaje C para que, utilizando
 * un timer y un pin de capture de esta placa sea posible demodular una senial PWM que
 * ingresa por dicho pin (calcular el ciclo de trabajo y el periodo) y sacar 
 * una tension continua proporcional al ciclo de trabajo a traves del DAC de rango dinamico 0-2V
 * con un rate de actualizacion de 0.5seg del promedio de los ultimos 10 valores obtenidos
 * en la captura
*/

//TIMER1 para DAC para 0.5s ===> f = 2Hz
//PCLK = 100 Mhz ==> PR = 99 ==> f_res = 1Mhz ==> MR0 = f_res/f = 500000

#include "LPC17xx.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_dac.h"

uint32_t data[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32_t highValue, lowValue;
uint32_t egde = 0; //edge%2 != 0 low level, edge%2 = 0 high level
//TIMER 0 como capture y TIMER1 como match
void configTimer0(void){
    LPC_PINCON->PINSEL3 |= (3<<20); //Select Cap0.0
    LPC_PINCON->PINMODE3 |= (2<<20); //Pinmode Neither
    
    LPC_SC->PCONP |= (1<<1);
    LPC_SC->PCLKSEL0 |= (1<<2);

    LPC_TIM0->PR = 0;
    LPC_TIM0->CCR |= (7<<0); //Capture for Rising, Falling and Interrupt Event on
    LPC_TIM0->IR |= (0x3F<<0);
    LPC_TIM0->TCR |= (3<<0);
    LPC_TIM0->TCR &= ~(1<<1);
    NVIC_EnableIRQ(TIMER0_IRQn);
}

void configTimer1(void){
    LPC_SC->PCONP |= (1<<2);
    LPC_SC->PCLKSEL0 |= (1<<4);

    LPC_TIM1->MR0 = 500000;
    LPC_TIM1->MCR |= (3<<0); //Interrupt MR0 and Reset TC on match MR0
    LPC_TIM1->IR |= (0x3F<<0);
    LPC_TIM1->TCR |= (3<<0);
    LPC_TIM1->TCR &= ~(1<<1);
    NVIC_EnableIRQ(TIMER1_IRQn);
}

void configDAC(void){
    LPC_PINCON->PINSEL1 |= (2<<20);
    LPC_PINCON->PINMODE1 |= (2<<20);
    DAC_Init(LPC_DAC);
    DAC_SetBias(LPC_DAC, 0);
}

void movData(void){
    for(int i = 9; i > 0; i--){
        data[i] = data[i-1];
    }
}
void TIMER0_IRQHandler(void){
    static uint8_t count = 0;
    if(egde%2 == 0){
        highValue = LPC_TIM0->CR0;
    }
    else{
        lowValue = LPC_TIM0->CR0;
    }
    if((highValue > 0) && (lowValue > 0)){
        uint32_t dutyCycle = (highValue/(highValue + lowValue))*100;    //8 2 = 10
        uint32_t period = (highValue + lowValue)/10000000; //Timer Clock 100Mhz and PR 0
        movData();
        data[0] = dutyCycle;
        highValue = 0;
        lowValue = 0;
        LPC_TIM0->IR |= (1<<4);
    }
}

void TIMER1_IRQHandler(void){
    uint32_t DACValue = (average()*620)/100;
    DAC_UpdateValue(LPC_DAC, DACValue);
    LPC_TIM1->IR |= (1<<0);
}

uint32_t average(void){
    uint32_t sum = 0;
    for(int i = 0; i < 10; i++){
        sum += data[i];
    }
    return sum/10;
}

int main(void){
    configTimer0();
    configTimer1();
    configDAC();
    while(1){
    }
    return 0;
}