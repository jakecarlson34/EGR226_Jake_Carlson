/**************************************************************************************
 * Author: Jake Carlson
 * Course: EGR 226 - 902
 * Date: 03/17/2021
 * Project: lab08part3
 * File: part3main.c
 * Description: This program controls the speed of a DC motor using a keypad for input
 * of duty cycle.
 *
 *
 **************************************************************************************/


#include "msp.h"
#include<stdlib.h>
#include<stdio.h>

uint8_t Keypad_Read(void);//function prototypes
void SysTick_init();
void SysTick_Delay(uint16_t delayms);
uint8_t num, pressed;


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    P4->SEL0 &= ~0xF;
    P4->SEL1 &= ~0xF;//initialize rows
    P4->DIR &= ~0xF;
    P4->REN |= 0xF;
    P4->OUT |= 0xF;

    P4->SEL0 &= ~0x70;
    P4->SEL1 &= ~0x70;//initialize columns
    P4->DIR &= ~0x70;



    double dutyCyc, on;


    SysTick_init();

    P2->SEL1 &=~BIT4;
    P2->SEL0 |= BIT4;//Timer A initialization
    P2->DIR |= BIT4;

    TIMER_A0->CCR[0] = 30000;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;//Timer A pulse
    TIMER_A0->CTL = 0x0214;

while(1){
    pressed = Keypad_Read();

    if(pressed){
        if(num == 11){//when 0 is pressed the duty cycle is 0
            dutyCyc = 0;
        }
        if(num<10){//when any other key is pressed that key is the dutycycle.
            dutyCyc = num;
        }

        on =((dutyCyc/10)*30000);//duty cycle is multiplied by period
        TIMER_A0->CCR[1] = on;//run DC motor

    }


}


}


uint8_t Keypad_Read(void){//function given by Professor Krug

    uint8_t col, row;

    for(col = 0; col<3; col++){
        P4DIR = 0x00;
        P4DIR |=BIT(4+col);
        P4OUT &= ~BIT(4+col);
        SysTick_Delay(10);
        row = P4IN & 0x0F;

        while(!(P4IN & BIT0)|!(P4IN & BIT1)|!(P4IN & BIT2)|!(P4IN & BIT3));

        if(row != 0x0F){
            break;
        }
    }

    P4DIR = 0x00;
    if(col == 3){
        return 0;
    }
    if(row == 0x0E){
        num = col +1;
    }
    if(row == 0x0D){
        num = 3 + col +1;
    }
    if(row == 0x0B){
        num = 6+ col +1;
    }
    if(row == 0x07){
        num = 9 + col +1;
    }
    return 1;
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

