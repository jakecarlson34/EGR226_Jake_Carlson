/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 02/14/2021
* Project: lab04part1
* File: main.c
* Description: This program uses the button on the MSP432 and toggles through the Red,
* Green, and Blue LED's.
*
**************************************************************************************/



#include "msp.h"


/**
 * main.c
 */

uint8_t debounce(void);
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    int i = 0;
    int j = 0;


    P1->SEL1 &= ~2;
    P1->SEL0 &= ~2;
    P1->DIR &= ~2;
    P1->REN |= 2;
    P1->OUT |= 2;

    P2->SEL1 &= ~1;
    P2->SEL0 &= ~1;
    P2->DIR |= 1;
    P2->OUT &= ~1;

    P2->SEL1 &= ~2;
    P2->SEL0 &= ~2;
    P2->DIR |= 2;
    P2->OUT &= ~2;

    P2->SEL1 &= ~4;
    P2->SEL0 &= ~4;
    P2->DIR |= 4;
    P2->OUT &= ~4;



           while(1){
               if(debounce()){

                   if((i==0) && (j==0)){
                    P2->OUT |= 1;// Toggle LED P1
                    j = 1;
                    i++;

                   }
                   else if((i==1) && (j==1)){
                       P2->OUT &= ~1; //red off
                       P2->OUT |= 2; //green on
                       i++;
                   }

                   else if((i==2) && (j==1)){
                       P2->OUT &= ~2; //green off
                       P2->OUT |= 4; //blue on
                       i++;
                   }

                   else{
                      P2->OUT |= 1; //red on
                      P2->OUT &= ~2; //green off
                      P2->OUT &= ~4; //blue off
                       i=1;

                   }

                   }
}
}
uint8_t debounce(void){

    uint8_t pinVal = 0;//making variable low

    if((P1->IN & 2) == 0){ //checking if button is pushed
        _delay_cycles(30000);//pausing for 10 milliseconds

        if((P1->IN & 2))//checking if button still pushed
            pinVal = 1;
    }

    return pinVal; //returning 0 if not pushed and 1 if pushed


}
