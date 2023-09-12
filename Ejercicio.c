#include "LPC17xx.h"

int main(void) {
	LPC_GPIO0->FIODIR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);

	LPC_GPIO0->FIOSET |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 4) | (1 << 5);
	LPC_GPIO0->FIOCLR |= (1 << 3) | (1 << 6) | (1 << 7);
    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");
    }
    return 0 ;
}
