/**************************************************************************************
 * Author: Jake Carlson
 * Course: EGR 226 - 902
 * Date: 04/5/2021
 * Project: lab11part1
 * File: part1main.c
 * Description: This program generates a 10 HZ IR signal.
 *
 *
 **************************************************************************************/

#include "msp.h"
#include <stdio.h>


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer


	P2->SEL0 |= BIT4;
	P2->SEL1 &= ~BIT4;//emitter pin
	P2->DIR |= BIT4;

	TIMER_A0->CTL = 0b1000010100;//Timer A setup
	TIMER_A0->CCR[0] = 37500-1;//1 ms period
	TIMER_A0->CCR[1] = 37500*.5-1;//duty cycle 50%
	TIMER_A0->CCTL[1] = 0b11100000;//Out mode

	while(1){
	    ;
	}
}
