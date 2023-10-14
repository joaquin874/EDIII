/**
 * a.- Modificar el valor del Match del ejemplo visto en clases para que la frecuencia 
 * de muestreo del ADC sea de 20 Kmuestras/seg. El resultado de la conversión deben 
 * mostrarse por 12 pines de salida del GPIO0.  Adjuntar el código en C.
 * b.- Modificar el código realizado en el punto "a" utilizando ahora el Driver provisto 
 * para este microcontrolador. 
*/

/**
 * Para tener una frecuencia de muestreo de 20Kmuestras/seg. Primero debemos configurar el clock
 * del periferico que su valor minimo a 100Mhz el micro es de 12,5Mhz, luego se usaran los bits
 * CLKDIV del registro AD0CR.
 * Si Cclk = 100 Mhz y ADckl = 12,5 Mhz ==> f_muestreo = 192,30 khz
 * ==> CLKDIV = f_muestreo_192/f_muestreo20 ==> CLKDIV = 9,61 = 9 (Por teorema de muestreo)
*/

#include "LPC17xx.h"
#include "lpc17xx_adc.h"

void confGPIO(void);
void confADC(void);

uint16_t ADC0Value = 0;

int main(void) {
    confGPIO();
    confADC();
    while(1){}
    return 0;
}

void confGPIO(void){
    LPC_GPIO0->FIODIR |= (1<<22);
    return;
}

// void confADC(void){
//     LPC_SC->PCONP |= (1 << 12);
//     LPC_ADC->ADCR |= (1 << 21); //habilita el ADC
//     LPC_SC->PCLKSEL0 |= (3<<24);  //CCLK/8
//     LPC_ADC->ADCR &=~(255 << 8);  //[15:8] CLKDIV
//     LPC_ADC->ADCR |= (9 << 8);     //CLKDIV = 9
//     LPC_ADC->ADCR |= (1 << 0);   // channel
//     LPC_ADC->ADCR |= (1 << 16);   // burst
//     LPC_PINCON->PINMODE1 |= (1<<15); //neither pull-up nor pull-down.
//     LPC_PINCON->PINSEL1 |= (1<<14);
//     LPC_ADC->ADINTEN |= (1<<0);
//     LPC_ADC->ADINTEN &=~ (1<<8);
//     NVIC_EnableIRQ(ADC_IRQn);

//     return;
// }


void confADC(void){
    LPC_PINCON->PINSEL1 |= (1<<14);
    LPC_PINCON->PINMODE1 |= (2<<14);

    ADC_Init(LPC_ADC, 20000);
    ADC_StartCmd(LPC_ADC, ADC_START_CONTINUOUS);
    ADC_ChannelCmd(LPC_ADC, 0, ENABLE);
    ADC_IntConfig(LPC_ADC, ADC_ADINTEN0, ENABLE);
    ADC_BurstCmd(LPC_ADC, ENABLE);
    NVIC_EnableIRQ(ADC_IRQn);
}
void ADC_IRQHandler(void){
    ADC0Value = ((LPC_ADC->ADDR0)>>4) & 0xFFF; //Variable auxiliar para observar el valor del registro de captura

    if (ADC0Value<2054){
        LPC_GPIO0->FIOSET = (1<<22);    
    }
    else{
        LPC_GPIO0->FIOCLR = (1<<22);
    }

    return;
}