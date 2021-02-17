/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 02/14/2021
* Project: lab04part2
* File: main.c
* Description: This program uses the button on the MSP432 and toggles through the Red,
* Green, and Blue LED's using a delay function.
*
**************************************************************************************/

#include "msp.h"
#include <stdlib.h>


/**
 * main.c
 */

uint8_t debounce();//function prototypes
int delay();

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    enum states{RED, GREEN, BLUE,
    };

    enum states state;
    int i=0;
    int j = 0;
    P1->SEL0 &= ~2;
    P1->SEL1 &= ~2;//setting button to output and choosing pull up resistor
    P1->DIR &= ~2;
    P1->REN |= 2;
    P1->OUT |= 2;

    P2->DIR |= 1;//setting LED's to out put
    P2->DIR |= 2;
    P2->DIR |= 4;
    P2->OUT &= ~1;
    P2->OUT &= ~2;//turning LED's off to start
    P2->OUT &= ~4;


    while(1){
        i = debounce();// using debounce function for the button switch
        switch(state){

        case RED: //first case using red LED
            if((P1->IN & 2)== 0){//if statement for when the button is pushed and held
                P2->OUT |= 1;//turn on red LED if button is pushed
                j=delay();//call delay function to delay for desired amount of time
                if(j==1){ //if statement for when button is released
                    P2->OUT |= 1;//keep red LED on when button is released
                }
                else{
                     P2->OUT &= ~1;//turn LED off when switching states
                     state = GREEN;
                }
            }
            break;

        case GREEN://second case using green LED
            if((P1->IN & 2)==0){//if statement for when the button is pushed and held
                P2->OUT |= 2;//turn on green LED if button is pushed
                j=delay();//delay for desired amount of time
                if(j==1){//if statement for when button is released
                    P2->OUT |= 2;//keep green LED on when released
                }
                else{
                    P2->OUT &= ~2;//turn LED off when switching states
                    state = BLUE;
                }
            }
            break;

        case BLUE://third case using blue LED
                    if((P1->IN & 2)==0){//if statement for when the button is pushed and held
                        P2->OUT |= 4;//turn on blue LED if button is pushed
                        j=delay();//delay for desired amount of time
                        if(j==1){//if statement for when button is released
                            P2->OUT |= 4;//keep blue LED on when released
                        }
                        else{
                            P2->OUT &= ~4;//turn LED off when switching states
                            state = RED;
                        }
                    }
                    break;

        }
    }


}

uint8_t debounce(){
    static uint8_t pinVal = 0;//variable for button value

    pinVal = (pinVal<<1) | ((P1->IN & 2)/ 2) | 0xf800;
    __delay_cycles(30000);//delaying for debounce

    if(pinVal == 0xfc00)
    return 1;//returning 1 if button value is 0xfc00

    return 0;//returning 0  if not
}
int delay(){
    int i = 0;
    for(i=0; i<=1000; i++){
        if(P1->IN & 2)//for loop to used for 1 second to delay
            return 1;
        __delay_cycles(3000);//change this value to change delay time
    }
    return 0;
}
