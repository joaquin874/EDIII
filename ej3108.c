#include "LPC17xx.h"


#include <stdio.h>

/*
 * Puerto 0.0	Entrada
 * Puerto 0.1	Salida
 * Puerto 0.2	Salida
 * Puerto 0.3   Salida
 */
void setup1(){
	LPC_GPIO0->FIODIR &= (0<<0) & (0<<1) & (0<<2) & (0<<3);
	LPC_GPIO0->FIODIR |= (0<<0) | (1<<1) | (1<<2) | (1<<3);
}
/*
 * Puerto 0.0	Salida
 * Puerto 0.1	Entrada
 * Puerto 0.2	Salida
 * Puerto 0.3	Salida
 */
void setup2(){
	LPC_GPIO0->FIODIR &= (0<<0) & (0<<1) & (0<<2) & (0<<3);
	LPC_GPIO0->FIODIR |= (1<<0) | (0<<1) | (1<<2) | (1<<3);
}
/*
 * Puerto 0.0	Salida
 * Puerto 0.1	Salida
 * Puerto 0.2	Entrada
 * Puerto 0.3	Salida
 */
void setup3(){
	LPC_GPIO0->FIODIR &= (0<<0) & (0<<1) & (0<<2) & (0<<3);
	LPC_GPIO0->FIODIR |= (1<<0) | (1<<1) | (0<<2) | (1<<3);
}
/*
 * Puerto 0.0	Salida
 * Puerto 0.1	Salida
 * Puerto 0.2	Salida
 * Puerto 0.3	Entrada
 */
void setup4(){
	LPC_GPIO0->FIODIR &= (0<<0) & (0<<1) & (0<<2) & (0<<3);
	LPC_GPIO0->FIODIR |= (1<<0) | (1<<1) | (1<<2) | (0<<3);
}

void delay(uint32_t value){
	for(int i = 0; i < value; i++){

	}
}
int main(void){
	uint32_t value = 12000000; // 1segundo  12mhz
	while(1){
		setup1();
		//LPC_GPIO0->FIOSET |= (1<<1) | (1<<2) | (1<<3);
		delay(value);
		setup2();
		delay(value);
		setup3();
		delay(value);
		setup4();
		delay(value);
	}
}

