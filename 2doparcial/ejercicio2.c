/**
 * Utilizando el timer0, un dac, interrupciones y el driver del LPC1769 , escribir un código que permita generar 
 * una señal triangular periódica simétrica, que tenga el mínimo periodo posible, la máxima excursión de voltaje 
 * pico a pico posible y el mínimo incremento de señal posible por el dac. Suponer una frecuencia de core cclk de 100 Mhz. 
 * El código debe estar debidamente comentado.
*/

#include "LPC17xx.h"
#include "lpc17xx_dac.h"

void updateValue(void);
void configDAC(void);
void configTimer0(void);
void TIMER0_IRQHandler(void);

uint8_t edge = 1; //1 para subida y 2 para bajada
int dacValue = 0;

int main(void){
    configDAC();
    while(1){
    }
}

void configDAC(void){
    LPC_PINCON->PINSEL1 |= (2<<20);

    DAC_Init(LPC_DAC);
    DAC_SetBias(LPC_DAC, 0);
    return;
}

void updateValue(void){
    if(edge == 1){
        dacValue++;
        if(dacValue >= 1023){
            edge = 2;
        }
    }
    else if(edge == 2){
        dacValue--;
        if(dacValue <= 0){
            edge = 1;
        }
    }
}

void configTimer0(void){
    LPC_SC->PCONP |= (1<<1);
    LPC_SC->PCLKSEL0 |= (1<<2);
    
    LPC_TIM0->PR = 0;
    LPC_TIM0->MR0 = 0;
    LPC_TIM0->MCR |= (3<<0);
    LPC_TIM0->TCR &= ~(1<<0);
    LPC_TIM0->IR |= 0x3F;
    LPC_TIM0->TCR = 3;
    LPC_TIM0->TCR &= ~(1<<1);
    NVIC_EnableIRQ(TIMER0_IRQn);
}

void TIMER0_IRQHandler(void){
    DAC_UpdateValue(LPC_DAC, dacValue);
    updateValue();
    LPC_TIM0->IR |= (1<<0);
}
// No sirve, si se usa el Driver
// void newValue(void){
//     if(edge == 1){
//         count++;
//         data[9]++;
//         for(int i = 9; i >= 0; i--){
//             if(data[i] > 1){
//                 data[i-1]++;
//                 data[i] = 0;
//             }
//         }
//         if(count >= 1024){
//             count = 0;
//             edge = 2;
//         }
//     }
//     else if(edge == 2){
//         count++;
//         data[9]--;
//         for(int i = 9; i >= 0; i--){
//             if(data[i] < 1){
//                 data[i-1]--;
//                 data[i] = 1;
//             }
//         }
//         if(count >= 1024){
//             count = 0;
//             edge = 1;
//         }
//     }
//     return;
// }