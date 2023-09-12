/**
 * Una famosa empresa de calzados a incorporado a sus zapatillas 10 luces leds comandadas por un microcontrolador LPC1769 
 * y ha pedido a su grupo de ingenieros que diseñen 2 secuencias de luces que cada cierto tiempo se vayan 
 * intercalando (secuencia A - secuencia B- secuencia A- ... ). Como todavía no se ha definido la frecuencia a la cual va a 
 * funcionar el CPU del microcontrolador, las funciones de retardos que se incorporen deben tener como parametros de 
 * entrada variables que permitan modificar el tiempo de retardo que se vaya a utilizar finalmente. Se pide escribir el 
 * código que resuelva este pedido, considerando que los leds se encuentran conectados en los puertos P0,0 al P0.9. 
*/

#include "LPC17xx.h"

//El microcontrolador puede no reconocer varias librerias de C,
//por lo que es mejor no incluirla
//#include <stdio.h>

void sequence1();
void sequence2();
void delay(uint32_t);

int main(void) {
	// LPC_GPIO0->FIODIR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) |
	// 		(1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);
	LPC_GPIO0->FIODIR |= (0x2FF<<0);
	uint32_t value;
    while(1) {
    	//scanf("%u", &value);
    	value = 10000000;	//Delay de 1 segundo
    	for(int i = 0; i <= 20; i++){
    		sequence1();
    		delay(value);
    		sequence2();
    		delay(value);
    	}
    }
    return 0 ;
}

//Otra forma mas corta para setear las secuencias
void sequence1(){
	LPC_GPIO0->FIOCLR |= (0x2FF<<0);	//11 1111 1111
	LPC_GPIO0->FIOSET |= (0x2AA<<0);	//10 1010 1010
	LPC_GPIO0->FIOCLR |= (0x155<<0); 	//01 0101 0101

}

void sequence2(){
	LPC_GPIO0->FIOCLR |= (0x2FF<<0);	//11 1111 1111
	LPC_GPIO0->FIOSET |= (0x155<<0);	//01 0101 0101
	LPC_GPIO0->FIOCLR |= (0x2AA<<0); 	//10 1010 1010

}

// void sequence1(){
// 	LPC_GPIO0->FIOCLR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) |
// 			(1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);

// 	LPC_GPIO0->FIOSET |= (1 << 0) | (1 << 2) | (1 << 4) | (1 << 6) | (1 << 8);
// 	LPC_GPIO0->FIOCLR |= (1 << 1) | (1 << 3) | (1 << 5) | (1 << 7) | (1 << 9);
// }

// void sequence2(){
// 	LPC_GPIO0->FIOCLR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) |
// 			(1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);

// 	LPC_GPIO0->FIOSET |= (1 << 1) | (1 << 3) | (1 << 5) | (1 << 7) | (1 << 9);
// 	LPC_GPIO0->FIOCLR |= (1 << 0) | (1 << 2) | (1 << 4) | (1 << 6) | (1 << 8);
// }

void delay(uint32_t value){
	for(int i = 0; i < value; i++){}
}
