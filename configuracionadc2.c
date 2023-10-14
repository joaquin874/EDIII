/**
 * Configurar 4 canales del ADC para que funcionando en modo burst se obtenga una 
 * frecuencia de muestreo en cada uno de 50Kmuestras/seg. Suponer un cclk = 100 Mhz
*/

/**
 * Cclk = 100Mhz
 * ADclk = 13Mhz  => clockdiv = Cclk/ADclk = 7,69 = 8
*/
#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

void configPort(void){
    LPC_PINCON->PINSEL1 |= (0x55<<14);
    LPC_PINCON->PINMODE1 |= (0xAA<14);
    LPC_GPIO0->FIODIR |= (0xFFF<<0);
    LPC_GPIO0->FIOCLR |= (0xFFF<<0);
}

void configADC(void){
    LPC_SC->PCONP |= (1<<12);
    LPC_SC->PCLKSEL0 |= (3<<24);

    LPC_ADC->ADCR |= (0x0F<<0);
    LPC_ADC->ADCR &= ~(7<<24);
    
    LPC_ADC->ADINTEN |= (0x0F<<0);
    LPC_ADC->ADCR |= (1<<16);

    NVIC_EnableIRQ(ADC_IRQn);
}

void ADC_IRQHandler(void){
    uint32_t value = 0;
    if(LPC_ADC->ADSTAT & (1<<0)){
        value = LPC_ADC->ADDR0;
    }
    else if(LPC_ADC->ADSTAT & (1<<0)){
        value = LPC_ADC->ADDR1;
    }
    else if(LPC_ADC->ADSTAT & (1<<0)){
        value = LPC_ADC->ADDR2;
    }
    else if(LPC_ADC->ADSTAT & (1<<0)){
        value = LPC_ADC->ADDR3;
    }
    uint32_t newValue = (value>>0xF);
    LPC_GPIO0->FIOCLR |= (0xFFF<<0);
    LPC_GPIO0->FIOSET |= (newValue<<0);
}

int main(void){
    configPort();
    configADC();
}
