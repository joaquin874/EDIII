#include "LPC17xx.h"

/**
 * Los perifericos Timer0-1-2-3 son configurados usando los siguentes registros
 * 1) Alimentacion: Usando el registro PCONP, usando PCTIM0/1/2/3
 * 2) Clock del periferico: Usando el registro PCLOKSEL0, selecionando PCKL_TIMER0/1
 * 3) Pines: Seleccionar los pines a traves de los registros PINSEL. Seleccionar el pinmode
 * para el puerto
 * 4) Interrupcion: Ver registros T0/1/2/3MCR y T0/1/2/3CCR para matchear y capturar eventos.
 * Las interrupciones son habilitadas in la NVIC usando la apropiada Interrupt Set Enable Register.
 * 5) DMA: Se pueden usar hasta 2 de match para generar solicitudes timeadas de DMA. ver tabla 554
*/
//void confGPIO(void); // Prototipo de la funcion de conf. de puertos
void confTimer(void);
int main(void) {

//	confGPIO();
	confTimer();
	while(1){}
	return 0;
}

/*void confGPIO(void){
	LPC_GPIO0->FIODIR |= (1<<22);
	return;
}
*/

void confTimer(void){
	LPC_SC->PCONP       |= (1<<1);  // pag. 65 Habilita el Timer
	LPC_SC->PCLKSEL0    |= (1<<2);  // pag. 59 Funciona al clock del micro
	LPC_PINCON->PINSEL3 |= (3<<24); // pag. 120 Selecciona a MAT0 como pin
	//LPC_PINCON->PINSEL7 |= (2<<18);
	LPC_TIM0->EMR       |=(3<<4);   // pag. 509 
	LPC_TIM0->MR0        = 70000000;//
	LPC_TIM0->MCR       |= (1<<1);       // pag. 507
	LPC_TIM0->MCR       &= ~(1<<0);       // pag. 507
	LPC_TIM0->TCR        = 3;       // pag. 505
	LPC_TIM0->TCR       &= ~(1<<1);
	// NVIC_EnableIRQ(TIMER0_IRQn);
	return;
}

/*
void TIMER0_IRQHandler(void) //ISR del timer0
{
static uint8_t i = 0;
if (i==0){
LPC_GPIO0->FIOSET = (1<<22);
i = 1;
}
else if (i==1){
LPC_GPIO0->FIOCLR = (1<<22);
i = 0;
}
LPC_TIM0->IR|=1; //Limpia bandera de interrupci�n
return;
}
 */