/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 02/28/2021
* Project: lab06part1
* File: main.c
* Description: This program takes user input from a keypad and prints it to the screen.
*
*
*
**************************************************************************************/

#include "msp.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * main.c
 */
uint8_t Keypad_Read(void);
void Systick_init();
void SysTick_Delay(uint16_t delayms);
uint8_t num, pressed;
void print(void);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    P4->SEL0 &= ~0xF;
    P4->SEL1 &= ~0xF;
    P4->DIR &= ~0xF;
    P4->REN |= 0xF;
    P4->OUT |= 0xF;

    P4->SEL0 &= ~0x70;
    P4->SEL1 &= ~0x70;
    P4->DIR &= ~0x70;

    Systick_init();

    while(1){
        pressed = Keypad_Read();

        if(pressed){
           print();
          SysTick_Delay(10);
    }
    }

}

uint8_t Keypad_Read(void){

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
void Systick_init(){
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000005;
}
void SysTick_Delay(uint16_t delayms){
    SysTick->LOAD = ((delayms *3000)-1);
    SysTick->VAL = 0;
    while((SysTick->CTRL & 0x00010000)==0);


}
void print(void){
    if(num<10){
     printf("\n[%d]\n", num);
     fflush(stdout);
              }
     if(num==10){
      printf("\n[*]\n");
      fflush(stdout);
               }
     if(num==11){
     printf("\n[0]\n");
     fflush(stdout);
              }
     if(num==12){
     printf("\n[#]\n");
     fflush(stdout);
           }

}
