/**
 * Programar el microcontrolador LPC1769 para que mediante su ADC digitalice  dos señales analógicas 
 * cuyos anchos de bandas son de 10 Khz cada una. Los canales utilizados deben ser el 2 y el 4 y los datos 
 * deben ser guardados en dos regiones de memorias distintas que permitan contar con los últimos 20 datos 
 * de cada canal. Suponer una frecuencia de core cclk de 100 Mhz. El código debe estar debidamente comentado.
*/

#include "LPC17xx.h"
#include "lpc17xx_adc.h"

void configADC(void);
void ADC_IRQHandler(void);
void shortData(int num);

uint32_t dataChannel2[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32_t dataChannel4[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int main(void){
    configADC();
    while(1){}
    return 0;
}

void configADC(void){
    LPC_PINCON->PINSEL1 |= (1<<18);
    LPC_PINCON->PINSEL3 |= (3<<28);
    LPC_PINCON->PINMODE1 |= (2<<18);
    LPC_PINCON->PINMODE3 |= (2<<28);
    //Por teorema de muestreo la frec de muestreo tiene que se de 20Khz y al ser 2 en total 40Khz
    ADC_Init(LPC_ADC, 40000);    
    ADC_ChannelCmd(LPC_ADC, 2, ENABLE);
    ADC_ChannelCmd(LPC_ADC, 4, ENABLE);
    ADC_StartCmd(LPC_ADC, ADC_START_CONTINUOUS);
    ADC_BurstCmd(LPC_ADC, ENABLE);
    ADC_IntConfig(LPC_ADC, 2, ENABLE);
    ADC_IntConfig(LPC_ADC, 4, ENABLE);
    NVIC_EnableIRQ(ADC_IRQn);
    return;
}
//0000 1111 1111 1111 0000
void ADC_IRQHanlder(void){
    if(LPC_ADC->ADSTAT & (1<<2)){
        uint32_t data2 = ((LPC_ADC->ADDR2 & 0x0FFF0)>>0xF);
        dataChannel2[0] = data2;
        shortData(2);
    }
    else if(LPC_ADC->ADSTAT & (1<<4)){
        uint32_t data4 = ((LPC_ADC->ADDR4 & 0x0FFF0)>>0xF);
        dataChannel4[0] = data4;
        shortData(2);
    }
}

void shortData(int num){
    if(num == 2){
        for(int i = 19; i > 0; i--){
            dataChannel2[i] = dataChannel2[i-1];
        }
    }
    else if(num == 4){
        for(int i = 19; i > 0; i--){
            dataChannel4[i] = dataChannel4[i-1];
        }
    }
    
}