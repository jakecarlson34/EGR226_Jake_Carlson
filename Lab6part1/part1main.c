/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 02/28/2021
* Project: lab06part1
* File: part1main.c
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
uint8_t Keypad_Read(void);//function prototypes
void SysTick_init();
void SysTick_Delay(uint16_t delayms);
uint8_t num, pressed;
void print(void);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    P4->SEL0 &= ~0xF;
    P4->SEL1 &= ~0xF;//initializing rows
    P4->DIR &= ~0xF;
    P4->REN |= 0xF;
    P4->OUT |= 0xF;

    P4->SEL0 &= ~0x70;
    P4->SEL1 &= ~0x70;//initializing columns
    P4->DIR &= ~0x70;

    SysTick_init();//calling the initialization function

    while(1){
        pressed = Keypad_Read();

        if(pressed){//if Keypad_Read is 1 use print function and delay
           print();
          SysTick_Delay(10);
    }
    }

}

uint8_t Keypad_Read(void){//code given in lecture from Professor Krug

    uint8_t col, row;

    for(col = 0; col<3; col++){
        P4DIR = 0x00;//sets columns to inputs
        P4DIR |=BIT(4+col);//column 3 to output
        P4OUT &= ~BIT(4+col);//column 3 to low
        SysTick_Delay(10);//delay while loop
        row = P4IN & 0x0F;//read all rows

        while(!(P4IN & BIT0)|!(P4IN & BIT1)|!(P4IN & BIT2)|!(P4IN & BIT3));

        if(row != 0x0F){//if one of the inputs is low then a key is pressed
            break;
        }
    }

    P4DIR = 0x00;//sets the column to inputs
    if(col == 3){
        return 0;
    }
    if(row == 0x0E){//key in row 0
        num = col +1;
    }
    if(row == 0x0D){//key in row 1
       num = 3 + col +1;
        }
    if(row == 0x0B){//key in row 2
        num = 6+ col +1;
        }
    if(row == 0x07){//key in row 3
        num = 9 + col +1;
        }
    return 1;
}
void SysTick_init(){//Initializing SysTick
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000005;
}
void SysTick_Delay(uint16_t delayms){//delay function using SysTick
    SysTick->LOAD = ((delayms *3000)-1);
    SysTick->VAL = 0;
    while((SysTick->CTRL & 0x00010000)==0);


}
void print(void){

    if(num<10){//if the number is less than 10 it will print that number
     printf("\n[%d]\n", num);
     fflush(stdout);
              }
     if(num==10){//if number is 10 it will print the *
      printf("\n[*]\n");
      fflush(stdout);
               }
     if(num==11){//if number is 11 it will print 0
     printf("\n[0]\n");
     fflush(stdout);
              }
     if(num==12){//if number is 12 it will print #
     printf("\n[#]\n");
     fflush(stdout);
           }

}
