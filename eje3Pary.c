#include "LPC17xx.h"
#include <stdio.h>

int main(void){
	// Configure P0.4 PullDown
	LPC_PINCON->PINMODE0 &= ~(3<<8);
	LPC_PINCON->PINMODE0 |= (3<<8);
	LPC_GPIO0->FIODIR &= ~(1<<4);
	LPC_GPIO0->FIODIR |= (1<<4);
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
