/**
 * Utilizando Systick, programar al microcontrolador para que cada vez que se produzca una interrupcion por flanco ascendente
 * en el pin P2.4 se saque por el pin P2.5 la secuencia mostrada en la figura. En caso que se produzca una nueva interrupcion por P2.4 
 * mientras se esta realizando la secuencia, esta volvera a realizarse desde su incio descartando la que se venia sacando por el pin.
 * El programa NO debe hacer uso de retardos por software y deben enmascararse los pines del puerto 2 que no van a ser utilizados.
 * Suponer una frecuencia de reloj cclk de 80 Mhz (NO se pide configuracion del reloj).
 *  
*/
#include "LPC17xx.h"

//Secuencia del dibujo
uint32_t sec[19] = {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0};
int flagreset = 0;

void EINT3_IRQHandler(void);
void SysTick_Handler(void);
void configPorts(void);
void configInt(void);

int main(void){
    configPorts();
    configInt();
}

void configPorts(void){
    //Configuracion P2.4 como entrada y P2.5 como salida
    LPC_GPIO2->FIODIR &= ~(0x01<<4);
    LPC_GPIO2->FIODIR |= (0x01<<5);

    //Enmascaracion del resto de pines del puerto 2
    //1111 1111 1100 1111 = 0xFFFFFFCF
    LPC_GPIO2->FIOMASK |= (0xFFFFFFCF<<0);
    return;
}

void configInt(void){
    //Configuracion de interrupcion en P2.4 por flanco ascendente
    LPC_GPIOINT->IO2IntEnR |= (1<<4);

    //Limpiar bandera
    LPC_GPIOINT->IO2IntClr |= (1<<4);

    //Activo la interrupcion
    NVIC_EnableIRQ(EINT3_IRQn);
    return;
}

void EINT3_IRQHandler(void){
    //Verifico que la interrupcion fue por puerto 2 pin 4
    if((LPC_GPIOINT->IntStatus & 0x02) && (LPC_GPIOINT->IO2IntStatR & 0x10)){
        //Configuracion SysTick 10ms
        //clock = 80Mhz
        //Tclock = 1,25x10^-8 seg
        //1 cuenta ----- 1,25x10^-8 seg
        //x cuentas ---- 10x10^-3 seg
        //x = 800000
        //La funcion Systick_Config se encarga de restarle 1
        uint32_t x = 800000;
        SysTick_Config(x);
        flagreset = 1;
        //Limpiar bandera de P2.4
        LPC_GPIOINT->IO2IntClr |= (1<<4);
    } 
    return;
}

void SysTick_Handler(void){
    static int i = 0;
    if(flagreset == 1){
        i = 0;
    }
    if(sec[i] == 1){
        LPC_GPIO2->FIOSET |= (1<<5);
    }
    else{
        LPC_GPIO2->FIOCLR |= (1<<5);
    }
    if(i == 18){
        //Deshabilito el SysTick si se termino toda la sec
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    }
    i++;
}