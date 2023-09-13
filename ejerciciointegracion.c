/**
 * Algoritmo de antirrebote de un pulsador: Escribir un programa en C que ante la interrupción por flanco de subida del pin P0.1, 
 * configurado como entrada digital con pull-down interno, se incremente un contador de un dígito, se deshabilite esta interrupción 
 * y se permita la interrupción por systick cada 20 milisegundos. En cada interrupción del systick se testeará una vez el pin P0.1. 
 * Solo para el caso de haber testeado 3 estados altos seguidos se sacará por los pines del puerto P2.0 al P2.7 el equivalente en 
 * ascii del valor del contador, se desactivará las interrupción por systick y se habilitará nuevamente la interrupción por P0.1. 
 * Por especificación de diseño se pide que los pines del puerto 2 que no sean utilizados deben estar enmascarados por hardware. 
 * Considerar que el CPU se encuentra funcionando con el oscilador interno RC (4Mhz). 
*/
// se suma 48 para obtener el valor en ascii

#include "LPC17xx.h"

void configPorts(void);
void configInt(void);

void EINT3_IRQHandler(void){
    if((LPC_GPIOINT->IntStatus & 0x01) && (LPC_GPIOINT->IO0IntStatR & 0x01)){
        //1c --- 2,5x10^-7
        //xc --- 20x10^-3
        //x = 80000
        SysTick_Config(80000);
    }
}

void SysTick_Handler(void){
    NVIC_DisableIRQ(EINT3_IRQn);
    static int count = 0;
    static int countsec = 0;
    if((LPC_GPIOINT->IntStatus & 0x01) && (LPC_GPIOINT->IO0IntStatR & 0x01)){
        count++;
        countsec++;
    }
    else{
        count++;
        countsec = 0;
    }
    if(countsec == 3){
        uint32_t ascii = count + 48;
        LPC_GPIO2->FIOSET |= (ascii<<0);
    }
    LPC_GPIOINT->IO0IntClr |= (0x01<<1);
}
int main(void){
    configPorts();
}

void configPorts(void){
    LPC_PINCON->PINMODE0 |= (0x03<<2);
    LPC_GPIO0->FIODIR &= ~(0x01<<1);

    LPC_GPIO2->FIODIR |= (0xFF<<0);
    LPC_GPIO2->FIOMASK |= ~(0xFF<<0);
}

void configInt(void){
    LPC_GPIOINT->IO0IntEnR |= (0x01<<1);
    LPC_GPIOINT->IO0IntClr |= (0x01<<1);
    NVIC_EnableIRQ(EINT3_IRQn);
}

