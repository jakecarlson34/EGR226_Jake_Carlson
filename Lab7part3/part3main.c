/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 02/28/2021
* Project: lab07part3
* File: part3main.c
* Description: This program prints LABORATORY OVER and scrolls the message from left to
* right.
*
*
**************************************************************************************/




#include "msp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SysTick_init();
void SysTick_Delay(uint16_t delayms);
void delay_micro(uint32_t microsec);
void LCD_init();
void pulseEnable();
void pushNibble(uint8_t nibble);
void pushByte(uint8_t byte);
void commandWrite(uint8_t command);
void dataWrite(uint8_t data);
void pininit();



void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

     pininit();
     SysTick_init();
     SysTick_Delay(60);
     LCD_init();



     char lab[18] = "LABORATORY OVER ";

     int i = 0;
     int j = 0;

   commandWrite(0x01);//clearing display
   commandWrite(0x80);//first line address




    while(1){
        commandWrite(0x0C);//turn cursor off
        commandWrite(0x80);//first line

        for(i=j;i<strlen(lab); i++){//for loop to print lab array
            dataWrite(lab[i]);
        }
        j++;//increment count
        SysTick_Delay(500);//delay

        if(j==16){
            commandWrite(0x8F);//move to right side
            for(i = 0; i<strlen(lab); i++){//for loop to print lab array
                dataWrite(lab[i]);
                SysTick_Delay(500);
                commandWrite(0x18);//move left
                if(i==16)//start over when lab is printed
                    break;

            }
            commandWrite(0x01);//clear display
            commandWrite(0x80);//reset to first line
            j=0;//start counting over
        }



    }


}

void LCD_init(){



    commandWrite(3); //start sequence/reset
    SysTick_Delay(100);
    commandWrite(3);
    delay_micro(200);
    commandWrite(3);
    SysTick_Delay(100);
    commandWrite(2);

    delay_micro(100);
    commandWrite(0x28);
    delay_micro(100);

    delay_micro(100);
    commandWrite(0x0F);//turn on cursor
    delay_micro(100);
    commandWrite(0x01);//first home postion
    delay_micro(100);
    commandWrite(0x06);//continue blinking
    SysTick_Delay(10);


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

void delay_micro(uint32_t microsec){//new microsecond delay function given by Professor Krug
    SysTick->LOAD = ((microsec * 3) - 1);//multiplying delay by 3
    SysTick->VAL = 0;//clearing counter
    while((SysTick->CTRL & 0x00010000)== 0);

}

void pulseEnable(){//given by Professor Krug

    P4->OUT &= ~BIT2; //making sure E is 0
    delay_micro(10);
    P4->OUT |= BIT2; //making E HIGH
    delay_micro(10);
    P4->OUT &= ~BIT2; //back to 0
    delay_micro(10);

}

void pushNibble(uint8_t nibble){//given by Professor Krug
    P4->OUT &= ~0xF0; //clears pins 4.4-4.7 (DB4-DB7)
    P4->OUT |= (nibble & 0x0F) << 4;//sets pins 4.4-4.7 to DB4-DB7
    pulseEnable();
}

void pushByte(uint8_t byte){//given by Professor Krug

    uint8_t nibble;

    nibble = (byte & 0xF0) >> 4;
    pushNibble(nibble);//first half
    nibble = byte & 0x0F;
    pushNibble(nibble);//second half
    delay_micro(100);
}

void commandWrite(uint8_t command){//given by Professor Krug
    P4->OUT &= ~BIT0;//Making RS 0 so commands can be used
    pushByte(command);//passing of command
}

void dataWrite(uint8_t data){//given by Professor Krug
    P4->OUT |= BIT0;//Making RS 0 so data can be passed
    pushByte(data);//Passing data
}

void pininit(){//initializing LCD

    P4->SEL0 &= ~BIT0;//RS INIT
    P4->SEL1 &= ~BIT0;
    P4->DIR |= BIT0;
    P4->OUT &= ~BIT0;

    P4->SEL0 &= ~BIT2;//E INIT
    P4->SEL1 &= ~BIT2;
    P4->DIR |= BIT2;
    P4->OUT &= ~BIT2;

    P4->SEL0 &= ~BIT4;//DB4 INIT
    P4->SEL1 &= ~BIT4;
    P4->DIR |= BIT4;
    P4->OUT &= ~BIT4;

    P4->SEL0 &= ~BIT5;//DB5 INIT
    P4->SEL1 &= ~BIT5;
    P4->DIR |= BIT5;
    P4->OUT &= ~BIT5;

    P4->SEL0 &= ~BIT6;//DB6 INIT
    P4->SEL1 &= ~BIT6;
    P4->DIR |= BIT6;
    P4->OUT &= ~BIT6;

    P4->SEL0 &= ~BIT7;//DB7 INIT
    P4->SEL1 &= ~BIT7;
    P4->DIR |= BIT7;
    P4->OUT &= ~BIT7;


}
