/**
 * Configurar el pin P0.4 como entrada digital con resistencia de pull down y utilizarlo para decidir si el valor 
 * representado por los pines P0.0 al P0.3 van a ser sumados o restados al valor guardado en la variable "acumulador".
 * El valor inicial de "acumulador" es 0.
*/
#include "LPC17xx.h"
//#include <stdio.h>

int main(void){
	//Configurcion P0.4 PullDown
	LPC_PINCON->PINMODE0 &= ~(0x03<<8);
	LPC_PINCON->PINMODE0 |= (0x03<<8);
	
	//Configuracion de P0.4 como entrada
	LPC_GPIO0->FIODIR &= ~(1<<4);

	//Configuracion de P0.0 al P0.3 como salida
	LPC_GPIO0->FIODIR |= (1<<0) | (1<<1) | (1<<2) | (1<<3);

	int acumulador = 0;

	while(1){
		int state = (LPC_GPIO0->FIOPIN>>4) & 0x01;

		if(state){
			acumulador += (LPC_GPIO0->FIOPIN & 0x0F);
		}
		else{
			acumulador -= (LPC_GPIO0->FIOPIN & 0x0F);
		}
	}

}
