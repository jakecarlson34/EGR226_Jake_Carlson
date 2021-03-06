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
void SysTick_Delay(uint16_t delayms);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    enum states{RED, GREEN, YELLOW,
    };

    enum states state;
    int i=0;

    P3->SEL0 &= ~BIT2;
    P3->SEL1 &= ~BIT2;//setting button to output and choosing pull up resistor
    P3->DIR &= ~BIT2;
    P3->REN |= BIT2;
    P3->OUT |= BIT2;

    P4->DIR |= BIT3;//green LED
    P4->DIR |= BIT6;//yellow LED
    P6->DIR |= BIT4;//red LED
    P4->OUT &= ~BIT3;
    P4->OUT &= ~BIT6;//turning LED's off to start
    P6->OUT &= ~BIT4;

    state = GREEN; //start with green LED

    while(1){
        i = debounce();// using debounce function for the button switch
        switch(state){


        case GREEN: //first case using green LED
            if((P3->IN & BIT2)== 0){//if statement for when the button is pushed and held

              P4->OUT |= BIT3;//green on
              SysTick_Delay(1000);//delay 1 second

                       i = debounce();

                if(i==1){//normal cycle if button is held
                  P4->OUT &= ~BIT3; //green off
                  P4->OUT |= BIT6; //yellow on
                  state = YELLOW;
                       }
                    else{
                    P4->OUT &= ~BIT3; //green off
                    P4->OUT |= BIT6; //yellow on
                    state = YELLOW;
                        }
                       }
            break;

        case YELLOW://second case using yellow LED
            if((P3->IN & BIT2)== 0){//if statement for when the button is pushed and held
                SysTick_Delay(1000);//delay one second

                    P4->OUT |= BIT6;//yellow on
                    i = debounce();

                    if(i==1){
                    P4->OUT &= ~BIT6; //yellow off
                    P6->OUT |= BIT4; //red on
                    state = RED;
                        }

                    else{
                    P4->OUT &= ~BIT6; //yellow off
                    P6->OUT |= BIT4; //red on
                    state = RED;
                                  }
           }
            break;

        case RED://third case using blue LED
            if((P3->IN & BIT2)== 0){//if statement for when the button is pushed and held
                SysTick_Delay(1000);

              P6->OUT |= BIT4;//red on
              i = debounce();

                  if(i==1){
                      P6->OUT &= ~BIT4; //red off
                      P4->OUT |= BIT3; //Green on
                    state = GREEN;
                 }

             else{
                  P6->OUT &= ~BIT4; //red off
                  P4->OUT |= BIT3; //green on
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
void SysTick_Delay(uint16_t delayms){

    //systick init
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000005;


    SysTick->LOAD = (3000 * delayms);//using user input for delay
    SysTick->VAL = 0;
    while((SysTick->CTRL & 0x00010000)== 0);
    SysTick->CTRL = 0;//turn timer off
}

