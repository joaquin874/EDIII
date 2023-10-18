#include "LPC17xx.h"
#include "lpc17xx_adc.h"

void configGPIO(void);
void configADC(void);
void ADC_IRQHandler(void);
void delay(void);

int main(void){
    configGPIO();
    configADC();
    while(1){}
    return 0;
}

void configGPIO(void){
    LPC_GPIO2->FIODIR |= (1<<12);
    LPC_GPIO0->FIODIR |= (1<<22);
}

void configADC(void){
    LPC_PINCON->PINSEL1 |= (1<<14);
    LPC_PINCON->PINMODE1 |= (2<<14);
    
    LPC_PINCON->PINSEL4 |= (1<<20);
    LPC_PINCON->PINMODE4 |= (0<<20);
    
    LPC_SC->PCONP |= (1<<12);

    ADC_Init(LPC_ADC, 200000);
    ADC_BurstCmd(LPC_ADC, DISABLE);
    ADC_StartCmd(LPC_ADC, ADC_START_ON_EINT0);
    ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, ENABLE);
    ADC_IntConfig(LPC_ADC, ADC_ADINTEN0, ENABLE);
    NVIC_EnableIRQ(ADC_IRQn);
    return;
}

void ADC_IRQHandler(void){
    if(LPC_ADC->ADSTAT & (1<<0)){
        if(LPC_GPIO0->FIOPIN & (1<<22)){
            LPC_GPIO0->FIOCLR = (1<<22);
            delay();
        }
        else{
            LPC_GPIO0->FIOSET = (1<<22);
            delay();
        }
    }
    LPC_ADC->ADGDR &= LPC_ADC->ADGDR;
}

void delay(void){
    for(int i = 0; i < 10000000; i++){}
}