/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 02/28/2021
* Project: lab06part2
* File: part2main.c
* Description: This program collects the users input of a 4 digit PIN code and prints
* this code to the screen. This program will also validate if the pin was entered
* correctly the second time.
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
    P4->SEL1 &= ~0xF;//initialize rows
    P4->DIR &= ~0xF;
    P4->REN |= 0xF;
    P4->OUT |= 0xF;

    P4->SEL0 &= ~0x70;
    P4->SEL1 &= ~0x70;//initialize columns
    P4->DIR &= ~0x70;


int orig[100];//original array
int newp[10];//new pin
int a = 0;
int b =0;


    SysTick_init();//calling initialization function
    printf("\nPlease enter a 4 digit PIN number\n");

    while(1){
        pressed = Keypad_Read();

        if(pressed){
           print();//calling print fucntion
          SysTick_Delay(10);

          if(num!= 10 && num != 12){//storing number is not # or *
              orig[a]= num;
              a++;

          }
    }
        if(num == 12){//if # is entered
            if(a < 4){
                printf("Enter more numbers please.\n");//if the numbers entered are less than 4
                fflush(stdout);
                num = 0;
            }
            else{
                newp[0] = orig[a-4];//assigning the original array to a new one to print correctly
                newp[1] = orig[a-3];
                newp[2] = orig[a-2];
                newp[3] = orig[a-1];

               for(b = 0; b<4; b++){//for loop for 0
                  if(newp[b] == 11){
                     newp[b] = 0;
                  }
               }

               printf("PIN entered: [%d][%d][%d][%d]\n", newp[0], newp[1], newp[2], newp[3]);//printing entered PIN
               fflush(stdout);
               a = 0;
               num = 0;
            }
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
void SysTick_init(){//SysTick Initialization
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000005;
}
void SysTick_Delay(uint16_t delayms){//delay function
    SysTick->LOAD = ((delayms *3000)-1);
    SysTick->VAL = 0;
    while((SysTick->CTRL & 0x00010000)==0);


}
void print(void){//print function


    if(num<10){//if the number is less than 10 it will print that number
     printf("\n[%d]\n", num);
     fflush(stdout);
              }
     if(num==10){//if the number is 10 print *
      printf("\n[*]\n");
      fflush(stdout);
               }
     if(num==11){//if number is 11 print 0
     printf("\n[0]\n");
     fflush(stdout);
              }
     if(num==12){//if number is 12 print #
     printf("\n[#]\n");
     fflush(stdout);
           }

}
