#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "LPC17xx.h"

int main(void){
    PINSEL_CFG_Type pinselconfig;
    pinselconfig.Portnum = PINSEL_PORT_0;
    pinselconfig.Pinnum = PINSEL_PIN_10;
    pinselconfig.Funcnum = PINSEL_FUNC_0;
    PINSEL_ConfigPin(&pinselconfig);
}