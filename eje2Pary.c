/**
 * En los pines P2.0 a P2.7 se encuentra conectado un display de 7 segmentos. Utilizando la variable 
 * numDisplay [10] ={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67} que codifica los números del 0 a 9 para ser 
 * mostrados en el display, realizar un programa que muestre indefinidamente la cuenta de 0 a 9 en dicho display.
*/
#include "LPC17xx.h"

//#include <stdio.h>

#define SEGA (1<<0)
#define SEGB (1<<1)
#define SEGC (1<<2)
#define SEGD (1<<3)

#define SEGE (1<<4)
#define SEGF (1<<5)
#define SEGG (1<<6)
#define DIGP (1<<7)

const uint32_t digit[10] = {
		SEGA | SEGB | SEGC | SEGD | SEGE | SEGF,   	// 0x3F
		SEGB | SEGC,								// 0x06
		SEGA | SEGB | SEGD | SEGE | SEGG,			// 0x5B
		SEGA | SEGB | SEGC | SEGD | SEGG,			// 0x4F
		SEGB | SEGC | SEGF | SEGG,					// 0x66
		SEGA | SEGB | SEGD | SEGF | SEGG,			// 0x6D
		SEGA | SEGB | SEGD | SEGE | SEGF | SEGG,	// 0x7D
		SEGA | SEGB | SEGC,							// 0x07
		SEGA | SEGB | SEGC | SEGD | SEGE | SEGF | SEGG, //0x7F
		SEGA | SEGB | SEGC | SEGF | SEGG
};

void delay(uint32_t);

int main(void){
	LPC_GPIO2->FIODIR |= (SEGA | SEGB | SEGC| SEGD | SEGE | SEGF | SEGG);
	LPC_GPIO2->FIOCLR |= (SEGA | SEGB | SEGC| SEGD | SEGE | SEGF | SEGG);
	while(1){
		for(int i = 0; i < 10; i++){
			LPC_GPIO2->FIOCLR |= (SEGA | SEGB | SEGC| SEGD | SEGE | SEGF | SEGG);
			LPC_GPIO2->FIOSET |= digit[i];
			delay(10000000);	//Delay 1 seg
		}
	}
}

void delay(uint32_t value){
	for(int i = 0; i < value; i++){}
}
