/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 03/17/2021
* Project: lab08part2
* File: part2main.c
* Description: This program controls the speed of a DC motor using Timer A
* by modifying duty cycle in the debugger.
*
*
**************************************************************************************/


#include "msp.h"
#include<stdlib.h>
#include<stdio.h>



void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer



    double dutyCyc, inv;


    P2->SEL1 &=~BIT4;//initalizing pin 2.4 for timer A use
    P2->SEL0 |= BIT4;
    P2->DIR |= BIT4;

    TIMER_A0->CCR[0] = 3000;
    TIMER_A0->CCTL[1] = 0b0000000001110000 ;//Timer A pulse
    TIMER_A0->CTL = 0x0214;



    inv = 1 - dutyCyc;

    while(1){
        TIMER_A0->CCR[1] = (inv * 3000);//multiplying by 1 millisecond


    }
}



