/**************************************************************************************
 * Author: Jake Carlson
 * Course: EGR 226 - 902
 * Date: 03/17/2021
 * Project: lab09part3
 * File: part3main.c
 * Description: This program cycles through the 7 segment LED from 0 to 9 or reverse
 * using 2 buttons.
 *
 **************************************************************************************/


#include "msp.h"
#include <stdio.h>
#include <stdlib.h>

void SysTick_init();//function prototypes
void SysTick_Delay(uint16_t delayms);
void LED(int);
void SysTick_Handler();
volatile int i, fl;
void PORT5_IRQHandler();

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

    P5->SEL0 &= ~BIT0;
    P5->SEL1 &= ~BIT0;//button 1
    P5->DIR &= ~BIT0;
    P5->REN |= BIT0;
    P5->OUT |= BIT0;
    P5->IES &= ~BIT0;
    P5->IE |= BIT0;

    P5->SEL0 &= ~BIT1;
    P5->SEL1 &= ~BIT1;//button 2
    P5->DIR &= ~BIT1;
    P5->REN |= BIT1;
    P5->OUT |= BIT1;
    P5->IES &= ~BIT1;
    P5->IE |= BIT1;
    P5->IFG = 0;

    SysTick_init();
    __enable_irq();//enable interrupts
    NVIC_EnableIRQ(PORT5_IRQn);//port 5 interrupts


    fl = 0;//flag set to 0
    i = 0;

    while(1){
        if(fl==1){
            fl = 0;
        }
        LED(i);//cycle through LED
    }


}
void PORT5_IRQHandler(){
    fl = 1;
    SysTick_Delay(50);//delay
    if(P5->IFG & BIT0){//if button 1 is pressed
        if(i==9){
            i = 0;//i starts over if it reaches 9
        }
        else{
            i++;//go to 9
        }
    }
    if(P5->IFG & BIT1){//if button is pressed
        if(i==0){
           i = 9;//reset to 9 if i goes to 0
        }
        else{
            i--;//go to 0
        }
    }
    P5->IFG = 0;
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
void SysTick_Handler(){
    fl = 1;
}
void LED(int c){
    int a = c;

    switch(a){
    case 0:
        P4->OUT |= (BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//turn on 0
        break;

    case 1:
        P4->OUT |=(BIT3|BIT6);//turn on 1
        break;

    case 2:
        P4->OUT |= (BIT0|BIT2|BIT3|BIT4|BIT5);//turn on 2
        break;

    case 3:
        P4->OUT |= (BIT0|BIT2|BIT3|BIT5|BIT6);//turn on 3
        break;

    case 4:
        P4->OUT |= (BIT0|BIT1|BIT3|BIT6);//turn on 4
        break;

    case 5:
        P4->OUT |= (BIT0|BIT1|BIT2|BIT5|BIT6);//turn on 5
        break;

    case 6:
        P4->OUT |= (BIT0|BIT1|BIT2|BIT4|BIT5|BIT6);//turn on 6
        break;

    case 7:
        P4->OUT |= (BIT2|BIT3|BIT6);//turn on 7
        break;

    case 8:
        P4->OUT |= (BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//turn on 8
        break;

    case 9:
        P4->OUT |= (BIT0|BIT1|BIT2|BIT3|BIT5|BIT6);//turn on 9
        break;
    }
    P4->OUT &=~ (BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);//turn off LED
}
