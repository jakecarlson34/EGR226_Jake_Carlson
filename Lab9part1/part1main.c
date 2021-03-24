/**************************************************************************************
 * Author: Jake Carlson
 * Course: EGR 226 - 902
 * Date: 03/17/2021
 * Project: lab09part1
 * File: part1main.c
 * Description: This program controls the speed of a DC motor using Timer A and 3
 * buttons.
 *
 **************************************************************************************/


#include "msp.h"
#include<stdlib.h>
#include<stdio.h>

void SysTick_init();//function prototypes
void SysTick_Delay(uint16_t delayms);
uint8_t buttonDebounce();


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer


    int i;
    float dutyCyc = .33;

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


    TIMER_A0->CCR[0] = 30000;//period set
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CTL = 0x0214;

    SysTick_init();

    while(1){

        TIMER_A0->CCR[1] = dutyCyc * 30000 ;
        i = buttonDebounce();//sets i to what button is pushed

        if(i==1){//first button pushed
           if(dutyCyc < 1.0){
                dutyCyc = dutyCyc + .1;//increase duty cycle
            }
        }
        if(i==2){//second button pushed
          if(dutyCyc > 0.0){
                dutyCyc = dutyCyc - .1;//decrease duty cycle
            }
          if(dutyCyc == 0.0){
              dutyCyc = 0.0;
          }
        }
        if(i==3){//third button pushed
            dutyCyc = 0.0;//set duty cycle to 0
        }


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
    while((SysTick->CTRL & 0x00010000)==0);

}

uint8_t buttonDebounce(){//debounce used in previous labs
    static uint16_t button1 = 0;
    static uint16_t button2 = 0;
    static uint16_t button3 = 0;//declaring each button

    button1 = (button1<<1)|((P5IN & BIT0)/BIT0)|0xf800;
    button2 = (button2<<1)|((P5IN & BIT1)/BIT0)|0xf800;
    button3 = (button3<<1)|((P5IN & BIT2)/BIT0)|0xf800;

    SysTick_Delay(10);

    if(button1 == 0xfc00){
        return 1;//return 1 if first button pushed
    }
    else if(button2 == 0xfc00){
            return 2;//return 2 if second button pushed
        }
    else if(button3 == 0xfc00){
            return 3;//return 3 if third button pushed
        }
    return 0;

}
