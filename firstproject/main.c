#include "msp.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	P1->DIR = BIT0;//Configure GPIO for output on P1.0 LED1 on MSP432 Launchpad

	int i;
	 while(1){
	     P1->OUT ^= BIT0; //Toggle LED status
	     for(i=20000; i>0; i--); //Crude delay
	 }
}
