#include "msp.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	P1->SEL1 &= ~2;
	P1->SEL0 &= ~2;
	P1->DIR &= ~2;
	P1->REN |= 2;
	P1->OUT |= 2;

	P2->SEL1 &= ~1;
	P2->SEL0 &= ~1;
	P2->DIR |= 1;

	    while(1){
	        if((P1->IN & 2)==0x02)
	            P2->OUT &= ~1;
	        else
	            P2->OUT |= 1;
	    }






}