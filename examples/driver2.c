#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "LPC17xx.h"

int main(void){
    PINSEL_CFG_Type pinselconfig;
    pinselconfig.Portnum = PINSEL_PORT_0;
    pinselconfig.Pinnum = PINSEL_PIN_10;
    pinselconfig.Pinmode = PINSEL_PINMODE_NORMAL;
    pinselconfig.Funcnum = PINSEL_FUNC_0;
    PINSEL_ConfigPin(&pinselconfig);

    LPC_PINCON->PINSEL4 |= (0<<20);
    LPC_PINCON->PINMODE4 |= (1<<20);
    
}