/**************************************************************************************
 * Author: Jake Carlson
 * Course: EGR 226 - 902
 * Date: 03/17/2021
 * Project: lab08part1
 * File: part1main.c
 * Description: This program runs a DC motor off of a given duty cycle in CCS.
 *
 *
 **************************************************************************************/


#include "msp.h"

void SysTick_init();
void SysTick_Delay(uint16_t delayms);//function declaration

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    SysTick_init();
    float dutyCyc, on;

    P2->SEL1 &=~BIT4;//initializing DC motor pin
    P2->SEL0 &=~BIT4;
    P2->DIR |= BIT4;



    on = abs(100*dutyCyc);//decimal entered by user to give percentage


    while(1){

        P2->OUT |= BIT4;//turn motor on
        SysTick_Delay(on);//delay for duty cycle
        P2->OUT &= ~BIT4;//turn motor off
        SysTick_Delay(100 - on);//off for the opposite of the given duty cycle

    }
}


void SysTick_init(){//SysTick Initialization from previous labs
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000005;
}

void SysTick_Delay(uint16_t delayms){//delay function from previous labs
    SysTick->LOAD = ((delayms *3000)-1);
    SysTick->VAL = 0;
    SysTick->CTRL |= (0x05);
    while((SysTick->CTRL & 0x00010000)==0);

}
