#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <stdio.h>

void sequence1();
void sequence2();
void delay(uint32_t);

int main(void) {
	LPC_GPIO0->FIODIR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) |
			(1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);
	uint32_t value;
    while(1) {
    	scanf("%u", &value);
    	value *= 12000000;
    	for(int i = 0; i <= 20; i++){
    		sequence1();
    		delay(value);
    		sequence2();
    		delay(value);
    	}
    }
    return 0 ;
}

void sequence1(){
	LPC_GPIO0->FIOCLR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) |
			(1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);

	LPC_GPIO0->FIOSET |= (1 << 0) | (1 << 2) | (1 << 4) | (1 << 6) | (1 << 8);
	LPC_GPIO0->FIOCLR |= (1 << 1) | (1 << 3) | (1 << 5) | (1 << 7) | (1 << 9);
}

void sequence2(){
	LPC_GPIO0->FIOCLR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) |
			(1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);

	LPC_GPIO0->FIOSET |= (1 << 1) | (1 << 3) | (1 << 5) | (1 << 7) | (1 << 9);
	LPC_GPIO0->FIOCLR |= (1 << 0) | (1 << 2) | (1 << 4) | (1 << 6) | (1 << 8);
}

void delay(uint32_t value){
	for(int i = 0; i < value; i++){}
}
