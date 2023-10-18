#include "LPC17xx.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_dac.h"

uint8_t valueDAC = 0;
uint8_t typeEdge = 1; //1 rising 2 falling
uint32_t *address = (uint32_t *)0x10004000;

void configDAC(void);
void updateValue(uint8_t max, uint8_t delayValue);
void delay(uint8_t delayValue);
void delayRising(uint8_t delayInc);
void delayFalling(uint8_t delayDec);

int main(void){
    uint32_t *address = (uint32_t *)0x10004000;
    uint32_t data = *address;
    uint8_t maxValueADC = (data & 0xFF);
    uint8_t delayValue = ((data & 0xFF00)>>0xFF);
    uint8_t delayInc = ((data & 0xFF0000)>>0xFFFF);
    uint8_t delayDec = ((data & 0xFF000000)>>0xFFFFFF);
    while(1){
        DAC_UpdateValue(LPC_DAC, valueDAC);
        updateValue(maxValueADC, delayValue);
        if(typeEdge == 1){
            delayRising(delayInc);
        }
        else if(typeEdge == 2){
            delayFalling(delayDec);
        }
    }
    return 0;
}

void configDAC(void){
    DAC_Init(LPC_DAC);
    DAC_SetBias(LPC_DAC, 0);
    return;
}

void updateValue(uint8_t max, uint8_t delayValue){
    if(typeEdge == 1){
        valueDAC++;
        if(valueDAC >= max){
            typeEdge == 2;
            delay(delayValue);
        }
    }
    else if(typeEdge == 2){
        valueDAC--;
        if(valueDAC <= 0){
            typeEdge == 1;
            delay(delayValue);
        }
    }
}

void delay(uint8_t delayValue){    
    for(int i = 0; i < (10000*delayValue); i++){}
    
}

void delayRising(uint8_t delayInc){    
    for(int i = 0; i < (10000*delayInc); i++){}
    
}

void delayFalling(uint8_t delayDec){    
    for(int i = 0; i < (10000*delayDec); i++){}
    
}