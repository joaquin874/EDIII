#include "LPC17xx.h"

void confGPIO(void); // Prototipo de la funci�n de conf. de puertos

uint8_t inte = 0;

int main(void) {
	confGPIO();
	// Configuraci�n del intervalo de tiempo entre interrupciones del systick Timer
	if (SysTick_Config(SystemCoreClock/10)){
		while (1); // AVISO DE ERROR: El programa llega hasta aqui si la funci�n devuelve un 1
	}
	while(1){
		if(inte%2){
			LPC_GPIO0->FIOSET = (1<<22);
		}
		else {
			LPC_GPIO0->FIOCLR = (1<<22);
		}
	}
	return 0;
}
void SysTick_Handler(void) {
	inte++;
	SysTick->CTRL &= SysTick->CTRL;
	return;
}

void confGPIO(void){
	LPC_GPIO0->FIODIR |= (1<<22);
	return;
}
