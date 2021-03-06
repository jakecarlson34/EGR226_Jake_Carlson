/**************************************************************************************
 * Author: Jake Carlson
 * Course: EGR 226 - 902
 * Date: 03/17/2021
 * Project: lab09part2
 * File: part2main.c
 * Description: This program changes the 7 segment LED from 0-9 repeatedly.
 *
 *
 **************************************************************************************/


#include "msp.h"
#include <stdio.h>
#include <stdlib.h>

void SysTick_init();//function prototypes
void SysTick_Delay(uint16_t delayms);
void LED();
volatile uint32_t b = 0;
void SysTick_Handler();



/**

 g 4.0
 f 4.1
 a 4.2
 b 4.3
 e 4.4
 d 4.5
 c 4.6
 dp 4.7
 */


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    P4->SEL1 &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);
    P4->SEL0 &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//init LED
    P4->DIR |= (BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);
    P4->OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT5|BIT6);//turn all off




    SysTick_init();
    __enable_irq();



   while(1){

        LED();//call the LED segment
    }


}
void SysTick_Handler(){
    b++;//increment global count variable
}

void SysTick_init(){//SysTick Initialization from previous labs
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000007;//set to 7
}

void SysTick_Delay(uint16_t delayms){//delay function from previous labs
    SysTick->LOAD = ((delayms *3000)-1);
    SysTick->VAL = 0;
    while((SysTick->CTRL & 0x00010000)==0);

}

void LED(){


    switch(b){//count variable
    case 0:
        P4->OUT |= (BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//turn on 0
        SysTick_Delay(1500);//delay 1 second
        P4->OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//turn off
        break;

    case 1:
        P4->OUT |=(BIT3|BIT6);//turn on 1
        SysTick_Delay(1500);//delay
        P4->OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//turn off
        break;

    case 2:
        P4->OUT |= (BIT0|BIT2|BIT3|BIT4|BIT5);//turn on 2
        SysTick_Delay(1500);//delay
        P4->OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//turn off
        break;

    case 3:
        P4->OUT |= (BIT0|BIT2|BIT3|BIT5|BIT6);//turn on 3
        SysTick_Delay(1500);//delay
        P4->OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//turn off
        break;

    case 4:
        P4->OUT |= (BIT0|BIT1|BIT3|BIT6);//turn on 4
        SysTick_Delay(1500);//delay
        P4->OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//turn off
        break;

    case 5:
        P4->OUT |= (BIT0|BIT1|BIT2|BIT5|BIT6);//turn on 5
        SysTick_Delay(1500);//delay
        P4->OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//turn off
        break;

    case 6:
        P4->OUT |= (BIT0|BIT1|BIT2|BIT4|BIT5|BIT6);//turn on 6
        SysTick_Delay(1500);//delay
        P4->OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//turn off
        break;

    case 7:
        P4->OUT |= (BIT2|BIT3|BIT6);//turn on 7
        SysTick_Delay(1500);//delay
        P4->OUT &= ~(BIT2|BIT3|BIT6);//turn off
        break;

    case 8:
        P4->OUT |= (BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//turn on 8
        SysTick_Delay(1500);//delay
        P4->OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//turn off
        break;

    case 9:
        P4->OUT |= (BIT0|BIT1|BIT2|BIT3|BIT5|BIT6);//turn on 9
        SysTick_Delay(1500);//delay
        P4->OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT5|BIT6);//turn off
        b=0;//go back to 0
        break;
    }

}
