/**************************************************************************************
 * Author: Jake Carlson
 * Course: EGR 226 - 902
 * Date: 03/17/2021
 * Project: lab08part2
 * File: part2main.c
 * Description: This program controls the speed of a DC motor using Timer A.
 *
 *
 *
 **************************************************************************************/


#include "msp.h"
#include<stdlib.h>
#include<stdio.h>

void PORT2_IRQ(void);
void timer(float dutyCyc);
float dutyCyc =0;

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer




    P5->SEL0 &= ~BIT0;
    P5->SEL1 &= ~BIT0;//button 1
    P5->DIR &= ~BIT0;
    P5->REN |= BIT0;
    P5->OUT |= BIT0;

    P5->SEL0 &= ~BIT1;
    P5->SEL1 &= ~BIT1;//button 2
    P5->DIR &= ~BIT1;
    P5->REN |= BIT1;
    P5->OUT |= BIT1;

    P5->SEL0 &= ~BIT2;
    P5->SEL1 &= ~BIT2;//button 3
    P5->DIR &= ~BIT2;
    P5->REN |= BIT2;
    P5->OUT |= BIT2;

    P2->SEL1 &=~BIT4;//initializing pin 2.4 for timer A use
    P2->SEL0 |= BIT4;
    P2->DIR |= BIT4;





    NVIC->ISER[1] = (1 << ((PORT2_IRQn) & 31));
    __enable_interrupt();

    while(1){

;


    }
}
void PORT2_IRQ(void){
    if(P2->IFG & BIT5){
        timer(0);
        P2->IFG &= ~ BIT5;
    }
    if(P2->IFG & BIT6){
        dutyCyc = (dutyCyc -0.1);
       timer(dutyCyc);
       P2->IFG &= ~ BIT6;
    }
    if(P2->IFG & BIT7){
       dutyCyc = (dutyCyc +0.1);
       timer(dutyCyc);
       P2->IFG &= ~ BIT7;
        }


}
void timer(float dutyCyc){

    TIMER_A0->CCR[0] = 3000;
    TIMER_A0->CCTL[1] = 0b0000000001110000 ;
    TIMER_A0->CTL = 0x0214;

    TIMER_A0->CCR[1] = (dutyCyc * 3000);//multiplying by 1 millisecond
}
