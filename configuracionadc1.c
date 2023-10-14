/**
 * A partir del código ejemplo visto en clase:
 * 1.- Determine la frecuencia de trabajo y de muestreo del ADC suponiendo una 
 * frecuencia de cclk de 100 Mhz. ¿En que modo se encuentra trabajando el ADC? 
 * 2.- Modifique el ejemplo para considerar la utilización de dos canales de conversión. 
 * Adjuntar el código en C. ¿A que frecuencia se encuentra muestreando cada canal?
*/

/**
 * Si el clock de micro es de 100Mhz entonces para que funcione correctamente, se configura
 * para obtener una frecuencia de trabajo menor o igual a 13Mhz con el registro PCLKSEL0 
 * bit 24-25 con el valor 3 para tener una frecuencia de trabajo de 12,5Mhz
 * Y para la frecuencia de muestreo, para digitalizar una muestra se necesitan 65 pulsos,
 * entonces la frecuencia de muestreo seria fs = (f_trab)/(65) = 192,3khz
 * 
 * Para el caso de usar 2 canales, se disminuye a la mitad la frecuencia de muestreo, 
 * dejando 96,15khz para cada canal 
*/
#include "LPC17xx.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"

void configADC(void){
    LPC_SC->PCONP |= (1<<12);
    LPC_SC->PCLKSEL0 |= (3<<24);
    
    LPC_PINCON->PINSEL4 |= (1<<20); //Select EINT0
    LPC_PINCON->PINMODE4 &= ~ (3<<20); //Pull-Down
    LPC_PINCON->PINSEL1 |= (5<<14); //Select AD0.0 - AD0.1
    LPC_PINCON->PINMODE1 |= (10<<14);
    
    LPC_ADC->ADCR = (1<<21);
    LPC_ADC->ADCR &= ~(7<<24);
    LPC_ADC->ADCR |= (2<<24);
    LPC_ADC->ADCR |= (1<27);
    LPC_ADC->ADINTEN | (3<<0); //Active INT AD0,AD1
    NVIC_EnableIRQ(ADC_IRQn);
}

void ADC_IRQHandler(void){
    //mostrar en channel();
}

int main(void){
    configADC();

}
