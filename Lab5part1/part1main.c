/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 02/14/2021
* Project: lab05part1
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


    P3->SEL1 &= ~BIT2;
    P3->SEL0 &= ~BIT2;
    P3->DIR &= ~BIT2;//initializing button 1
    P3->REN |= BIT2;
    P3->OUT |= BIT2;

    P6->SEL1 &= ~BIT4;
    P6->SEL0 &= ~BIT4;//initializing red LED
    P6->DIR |= BIT4;
    P6->OUT &= ~BIT4;

    P4->SEL1 &= ~BIT3;
    P4->SEL0 &= ~BIT3;//initializing green LED
    P4->DIR |= BIT3;
    P4->OUT &= ~BIT3;

    P4->SEL1 &= ~BIT6;
    P4->SEL0 &= ~BIT6;//initializing yellow LED
    P4->DIR |= BIT6;
    P4->OUT &= ~BIT6;



           while(1){
               if(debounce()){//calling debounce function

                   if((i==0) && (j==0)){//i and j are 0 to start
                    P4->OUT |= BIT3;// Toggle LED green
                    j = 1;
                    i++;//green if

                   }
                   else if((i==1) && (j==1)){//i and j go to 1 to start yellow
                       P4->OUT &= ~BIT3; //green off
                       P4->OUT |= BIT6; //yellow on
                       i++;//yellow if
                   }

                   else if((i==2) && (j==1)){//i goes to 2 and j stays 1 to start red
                       P4->OUT &= ~BIT6; //yellow off
                       P6->OUT |= BIT4; //red on
                       i++;//blue if
                   }

                   else{
                      P4->OUT |= BIT3; //keep yellow on to now cycle back to green and skip first yellow
                      P4->OUT &= ~BIT6; //green off
                      P6->OUT &= ~BIT4; //red off
                       i=1;

                   }

                   }
}
}
uint8_t debounce(void){

    uint8_t pinVal = 0;//making variable low

    if((P3->IN & BIT2) == 0){ //checking if button is pushed
        _delay_cycles(30000);//pausing for 10 milliseconds

        if((P3->IN & BIT2))//checking if button still pushed
            pinVal = 1;
    }

    return pinVal; //returning 0 if not pushed and 1 if pushed


}
