/**************************************************************************************
 * Author: Jake Carlson
 * Course: EGR 226 - 902
 * Date: 04/5/2021
 * Project: lab11part2
 * File: part2main.c
 * Description: This program sends an IR signal and captures it. While captured the
 * Red LED on the MSP will stay on until it is interrupted.
 *
 **************************************************************************************/



#include "msp.h"
#include <stdio.h>
uint16_t period;//make period global

/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer


    P2->SEL0 |= BIT4;
    P2->SEL1 &= ~BIT4;//emitter pin
    P2->DIR |= BIT4;

    P5->SEL0 |= BIT7;
    P5->SEL1 &= ~BIT7;//receiving pin
    P5->DIR &= ~BIT7;

    P2->SEL0 &= ~BIT0;
    P2->SEL1 &= ~BIT0;//MSP LED setup
    P2->DIR |= BIT0;
    P2->OUT &= ~BIT0;


    NVIC_EnableIRQ(TA2_N_IRQn);
    __enable_interrupt();

    TIMER_A0->CTL = 0b1000010100;//Timer A set up
    TIMER_A0->CCR[0] = 37500-1;//1 ms period
    TIMER_A0->CCR[1] = 37500*.5-1;//duty cycle
    TIMER_A0->CCTL[1] = 0b11100000;//out mode
    TIMER_A2->CTL = 0b1000100100;//Timer A2 for capture
    TIMER_A2->CCTL[2] = 0b0100100100010000;



    while(1){
   //  printf("Period = %d\n", period);
    // __delay_cycles(3000000);

    }
}

void TA2_N_IRQHandler(){
    static uint16_t first = 0, second = 0;

    if(TIMER_A2->CCTL[2]&BIT0){//check for interrupt

        first = second;
        second = TIMER_A2->CCR[2];//second capture
        period = second - first;//period calculation

        if(period == 37500){
            P2->OUT |= BIT0;//keep LED on
        }
        else{
            P2->OUT &=~BIT0;//turn off LED
        }
    }
    TIMER_A2->CCTL[2] &= ~(BIT0);//off


}
