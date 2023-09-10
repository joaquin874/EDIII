#include "LPC17xx.h"

void configINT(void){
    //Selecciono el puerto P2.11 y P2.12 como EINT1 y EINT2
    LPC_PINCON->PINSEL4 |= (0x01<<22);
    LPC_PINCON->PINSEL4 |= (0x01<<24);

    //Configuro las interrupciones externas por flanco (ya sea de subida o bajada)
    LPC_SC->EXTINT &= ~(0x03<<1);
    LPC_SC->EXTMODE |= (0x03<<1);

    //EINT1 por flanco de bajada
    //EINT2 por flanco de subida
    LPC_SC->EXTPOLAR |= (0x01<<1);

    NVIC_SetPriority(EINT1_IRQn, 0);
    NVIC_SetPriority(EINT2_IRQn, 1);

    NVIC_EnableIRQ(EINT1_IRQn);
    NVIC_EnableIRQ(EINT2_IRQn);
    
    return;
}

void EINT1_IRQnHandler(void){
    //SysTick->LOAD = (SystemCoreClock/100) - 1; systick para 10ms
    //systick para 25ms
    if(SysTick_Config(SystemCoreClock/40)){
        while(1){}
    }
    return;
}

void EINT2_IRQnHandler(void){
    //sytick para 60ms
    if(SysTick_Config(SystemCoreClock/(3/50))){
        while(1){}
    }
    return;
}

void SysTick_Handler(void){
    return;
}

int main(void){
    configINT();
}