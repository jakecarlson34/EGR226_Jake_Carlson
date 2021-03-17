/**************************************************************************************
 * Author: Jake Carlson
 * Course: EGR 226 - 902
 * Date: 03/17/2021
 * Project: lab08part3
 * File: part2main.c
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


    int var[3];
    double dutyCyc;
    int i, j;
    SysTick_init();

    P2->SEL1 &=~BIT4;
    P2->SEL0 |= BIT4;
    P2->DIR |= BIT4;

    TIMER_A0->CCR[0] = 3000;
    TIMER_A0->CCTL[1] = 0b0000000001110000 ;
    TIMER_A0->CTL = 0x0214;



    do{

        pressed = Keypad_Read();

        if(pressed) {
            if((i<3) && (num<=11)){
                if(num == 11){
                    num = 0;
                }
                if(num==12){
                    var[i] = num;
                    i++;
                    j =1;
                }
                dutyCyc = var[0]*100 +var[1]*10 +var[2];
                dutyCyc = dutyCyc/100;

            }
        }

    }while(j == 0);
    TIMER_A0->CCR[1] = (dutyCyc * 3000);
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
