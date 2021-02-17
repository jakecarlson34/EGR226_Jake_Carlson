/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 02/14/2021
* Project: lab04part2
* File: main.c
* Description: This program uses the button on the MSP432 and toggles through the Red,
* Green, and Blue LED's using a 1 second delay.
*
**************************************************************************************/


#include "msp.h"
#include <stdlib.h>
#include <stdio.h>



uint8_t init_mask = 0b00000111;

int delay(int n);
uint8_t debounce();
void LED();


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer




    P1->SEL1 &= ~2;
    P1->SEL0 &= ~2;
    P1->DIR &= ~2;
    P1->REN |= 2;
    P1->OUT |= 2;

    P2->SEL1 &= ~init_mask;
    P2->SEL0 &= ~init_mask;
    P2->DIR |= init_mask;


    while(1){
        LED();
    }

}

void LED(){
        int i;
        int j = 0;
        int k = 1000;
        static unsigned int state;
        enum State_enum {OFF, RED, GREEN, BLUE};

        i = debounce();

                       switch(state){
                       case OFF:
                           if(i){
                               state = RED;
                           }
                           else{
                               P2->OUT &= ~init_mask;
                           }
                           break;
                       case RED:
                           if((P1->IN & 2) == 0){
                               P2->OUT |= 1;
                               j = delay(k);
                               if(j == 1)
                               P2->OUT |= 1;
                               else{
                                   P2->OUT &= ~1;
                                   state = GREEN;
                               }
                           }
                           else if(P1->IN & 2){
                               P2->OUT |= 1;
                           }
                           else if(i){
                               P2->OUT &= ~1;
                               state = GREEN;
                           }
                           break;
                       case GREEN:
                           if((P1->IN & 2) == 0){
                               P2->OUT |= 2;
                               j = delay(k);
                               if(j == 1)
                                   P2->OUT |= 2;
                               else{
                                   P2->OUT &= ~2;
                                   state = BLUE;
                               }
                           }
                           else if(P1->IN & 2){
                               P2->OUT |= 2;
                           }
                           else if(i){
                               P2->OUT &= ~2;
                               state = BLUE;
                           }
                           break;
                       case BLUE:
                           if((P1->IN & 2) == 0){
                               P2->OUT |= 4;
                             j = delay(k);
                             if(j == 1)
                                 P2->OUT |= 4;
                             else{
                                P2->OUT &= ~4;
                                state = RED;
                               }
                           }
                             else if(P1->IN & 2){
                                 P2->OUT |= 4;
                             }
                             else if(i){
                                 P2->OUT &= ~4;
                                 state = RED;
                             }
                           break;


                       }




}
uint8_t debounce(){

    static uint16_t pinVal = 0;//making variable low

    pinVal = (pinVal<<1) | ((P1->IN & 2) / 2) | 0xf800;
    __delay_cycles(5);

    if(pinVal == 0xfc00)
        return 1;


    return 0; //returning 0 if not pushed and 1 if pushed

}

int delay(int n){
    int i;
    for(i = 0; i < n; i++){
        if((P1->IN & 2) == 0){
            return 1;
        }
        __delay_cycles(3000);
    }
    return 0;
}

