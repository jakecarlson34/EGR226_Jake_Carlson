/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 02/14/2021
* Project: lab05part3
* File: main.c
* Description: This program uses the button on the MSP432 and toggles through the Red,
* Green, and Blue LED's using a delay function and can reverse the order using a second
* button.
*
**************************************************************************************/

#include "msp.h"
#include <stdlib.h>


/**
 * main.c
 */


void SysTick_Delay(uint16_t delayms);
uint16_t debounce();//function prototypes



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

    P5->SEL0 &= ~BIT5;
    P5->SEL1 &= ~BIT5;//setting button 2 to output and choosing pull up resistor
    P5->DIR &= ~BIT5;
    P5->REN |= BIT5;
    P5->OUT |= BIT5;


    P4->DIR |= BIT3;//green LED
    P4->DIR |= BIT6;//yellow LED
    P6->DIR |= BIT4;//red LED
    P4->OUT &= ~BIT3;
    P4->OUT &= ~BIT6;//turning LED's off to start
    P6->OUT &= ~BIT4;

    state = GREEN;


    while(1){
        i = debounce();// using debounce function for the button switch
        switch(state){

        case GREEN: //green LED
          if((P3->IN & BIT2)== 0){//if statement for when the button is pushed and held
              SysTick_Delay(1000);//delay 1 second
              P4->OUT |= BIT3;//green on

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
            else if((P5->IN & BIT5)==0){//checks if second button is held
                SysTick_Delay(1000);//delay one second
               P4->OUT |= BIT3;//green on
              if(P5->IN & BIT5){
                   i =debounce();
                      if(i==2){//reverse cycle
               P4->OUT &= ~BIT3; //green off
               P6->OUT |= BIT4;//red on
                  state = RED;
              }
           }
             else{
               P4->OUT &= ~BIT3; //green off
               P6->OUT |= BIT4;//red on
               state = RED;
           }
        }
                break;


        case YELLOW: //yellow case

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
                    else if((P5->IN & BIT5)==0){//check for second button input
                        SysTick_Delay(1000);//delay one second
                        P4->OUT |= BIT6;//yellow on
                        if(P5->IN & BIT5){
                            i =debounce();
                            if(i==2){//reverse cycle
                                P4->OUT &= ~BIT6; //yellow off
                                P4->OUT |= BIT3;//green on
                                state = GREEN;
                            }
                        }
                        else{
                            P4->OUT &= ~BIT6; //yellow off
                            P4->OUT |= BIT3;//green on
                            state = GREEN;
                        }
                    }
                    break;

        case RED: //red case
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
                            else if((P5->IN & BIT5)==0){//check for second button
                                SysTick_Delay(1000);//delay 1 second
                                P6->OUT |= BIT4;//red on
                                if(P5->IN & BIT5){
                                    i =debounce();
                                    if(i==2){
                                        P4->OUT &= ~BIT4; //red off
                                        P4->OUT |= BIT6;//yellow on
                                        state = YELLOW;
                                    }
                                }
                                else{
                                    P6->OUT &= ~BIT4; //red off
                                    P4->OUT |= BIT6;//yellow on
                                    state = YELLOW;
                                }
                            }
                            break;


      }
   }
}

uint16_t debounce(){
   static uint16_t pinVal1 = 0;//making variable low
   static uint16_t pinVal2 = 0;//variable for second push button

        pinVal1 = (pinVal1<<1) | ((P3->IN & BIT2) / BIT2) | 0xf800;
        pinVal2 = (pinVal2<<1) | ((P3->IN & BIT2) / BIT2) | 0xf800;
        SysTick_Delay(1000);

       if(pinVal1 == 0xfc00){//if button 1 is pushed
           return 1;
       }

       else if(pinVal2 == 0xfc00){//if button 2 is pushed
           return 2;
       }

        return 0; //returning 0 if not pushed and 1 or 2 depending which button is pushed
}
void SysTick_Delay(uint16_t delayms){

    //systick init
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000005;


    SysTick->LOAD = (1500 * delayms);//using user input for delay
    SysTick->VAL = 0;
    while((SysTick->CTRL & 0x00010000)== 0);
    SysTick->CTRL = 0;//turn timer off
}
