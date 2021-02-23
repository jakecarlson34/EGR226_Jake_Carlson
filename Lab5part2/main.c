/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 02/14/2021
* Project: lab05part2
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
    enum states{RED, GREEN, YELLOW,
    };

    enum states state;
    int i=0;
    int j = 0;
    P3->SEL0 &= ~BIT2;
    P3->SEL1 &= ~BIT2;//setting button to output and choosing pull up resistor
    P3->DIR &= ~BIT2;
    P3->REN |= BIT2;
    P3->OUT |= BIT2;

    P4->DIR |= BIT3;//green
    P4->DIR |= BIT6;//yellow
    P6->DIR |= BIT4;//red
    P4->OUT &= ~BIT3;
    P4->OUT &= ~BIT6;//turning LED's off to start
    P6->OUT &= ~BIT4;

    state = GREEN;

    while(1){
        i = debounce();// using debounce function for the button switch
        switch(state){

        case GREEN: //first case using green LED
            if((P3->IN & BIT2)== 0){//if statement for when the button is pushed and held
                P4->OUT |= BIT3;//turn on yellow LED if button is pushed
                j=delay();//call delay function to delay for desired amount of time
                if(j==1){ //if statement for when button is released
                    P4->OUT |= BIT3;//keep yellow LED on when button is released
                }
                else{
                     P4->OUT &= ~BIT3;//turn LED off when switching states
                     state = YELLOW;
                }
            }
            break;

        case YELLOW://second case using yellow LED
            if((P3->IN & BIT2)==0){//if statement for when the button is pushed and held
                P4->OUT |= BIT6;//turn on yellow LED if button is pushed
                j=delay();//delay for desired amount of time
                if(j==1){//if statement for when button is released
                    P4->OUT |= BIT6;//keep yellow LED on when released
                }
                else{
                    P4->OUT &= ~BIT6;//turn LED off when switching states
                    state = RED;
                }
            }
            break;

        case RED://third case using blue LED
                    if((P3->IN & BIT2)==0){//if statement for when the button is pushed and held
                        P6->OUT |= BIT4;//turn on red LED if button is pushed
                        j=delay();//delay for desired amount of time
                        if(j==1){//if statement for when button is released
                            P6->OUT |= BIT4;//keep red LED on when released
                        }
                        else{
                            P6->OUT &= ~BIT4;//turn LED off when switching states
                            state = GREEN;
                        }
                    }
                    break;

        }
    }


}

uint8_t debounce(){
    uint8_t pinVal = 0;//making variable low

        if((P3->IN & BIT2) == 0){ //checking if button is pushed
            _delay_cycles(30000);//pausing for 10 milliseconds

            if((P3->IN & BIT2))//checking if button still pushed
                pinVal = 1;
        }

        return pinVal; //returning 0 if not pushed and 1 if pushed
}
int delay(){
    int i = 0;
    for(i=0; i<=1000; i++){
        if(P3->IN & BIT2)//for loop to used for 1 second to delay
            return 1;
        __delay_cycles(3000);//change this value to change delay time
    }
    return 0;
}