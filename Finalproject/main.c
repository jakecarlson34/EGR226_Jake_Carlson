/**************************************************************************************
 * Author: Jake Carlson
 * Course: EGR 226 - 902
 * Date: 04/23/2021
 * Project: final project
 * File: main.c
 * Description: This program uses the LCD to print menus as the user cycles through
 * the different functions of the servo, DC motor, and RGB LED.
 *
 **************************************************************************************/


#include "msp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "SysTick_Library.h"
#include "LCD_Library.h"

//function prototypes
uint8_t num, pressed;
uint8_t Keypad_Read(void);
void keyinit();
void dcmoto();
void servodelay(uint16_t Cycle);
void LEDinit();
void REDLED();
void GREENLED();
void BLUELED();
void PORT3_IRQHandler();
void PORT4_IRQHandler();
int stopflag, rgbFlag;




void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    enum states{MAIN, DC, LIGHTS, DOOR, RED, GREEN, BLUE, OPEN, CLOSE
    };

    enum states state;

    SysTickInit_NoInterrupts();//SysTick init from library
    lcdInit();//init for LCD
    keyinit();//init for pins
    lcdClear();//clear LCD for first commands
    servodelay(5);//start with servo closed (door closed)


    state = MAIN;

    while(1){

        pressed = Keypad_Read();

        switch(state){

        case MAIN://first menu is the main menu
            lcdSetText("[1] Door", 3 , 0);//function from LCD library
            lcdSetText("[2] Motor", 3 , 1);//print different options to LCD for users choice
            lcdSetText("[3] Lights", 3 , 2);

            if(pressed){
                SysTick_delay_ms(10);
                if(num==1){//if 1 is pressed go to door menu
                    lcdClear();
                    state = DOOR;
                }
                if(num==2){//if 2 is pressed go to motor menu
                    lcdClear();
                    state = DC;
                }
                if(num==3){//if 3 is pressed go to LED menu
                    lcdClear();
                    state = LIGHTS;
                }
            }
            break;

        case DOOR://Servo door case menu
            lcdSetText("[1] Open Door", 1 , 0);//function from LCD library
            lcdSetText("[2] Close Door", 1 , 1);//User options printed to LCD
            lcdSetText("* to go back", 1, 3);
            if(pressed){
                SysTick_delay_ms(10);
                if(num==1){//if 1 is entered
                    lcdClear();//clear LCD
                    servodelay(11);//open the door
                    P2->OUT &= ~BIT0;//make sure red LED is off
                    P2->OUT |= BIT1;//turn on green LED
                    state = OPEN;//go to open door case
                }
                if(num==2){//if 2 is entered
                    lcdClear();//clear LCD
                    servodelay(5);//close door
                    P2->OUT &= ~BIT1;//make sure green LED is off
                    P2->OUT |= BIT0;//turn on red LED
                    state = CLOSE;//go to close door case
                }
                if(num==10){//if * is entered
                    P2->OUT &= ~BIT0;//turn off both LEDs
                    P2->OUT &= ~BIT1;
                    servodelay(5);//close door
                    lcdClear();//clear LCD
                    state = MAIN;//go back to the main menu
                }
            }

            break;

        case OPEN://Open door case
            lcdSetText("Door Is Open", 1 , 0);//function from LCD library
            SysTick_delay_ms(3000);//print door is open for 1 second

            lcdClear();//clear LCD
            state = DOOR;//go back to door menu


                break;

        case CLOSE://close door case
            lcdSetText("Door Is Closed", 1 , 0);//function from LCD library
            SysTick_delay_ms(3000);//print door is closed for 1 second

            lcdClear();//clear LCD
            state = DOOR;//go back to door menu


            break;


        case DC://DC motor menu
            lcdSetText("Motor Speed", 2, 0);//print options to LCD
            lcdSetText("[0-9]",5, 1);
            lcdSetText("* to go back", 1, 3);
            dcmoto();//call the motor function

            if(pressed){
                SysTick_delay_ms(10);
                if(num==10){//if * is pressed
                    lcdClear();//clear LCD
                    state = MAIN;//go back to main menu
                }
            }
            break;

        case LIGHTS://RGB LED menu
            lcdSetText("[1] RED", 4, 0);//print options to LCD
            lcdSetText("[2] GREEN", 4, 1);
            lcdSetText("[3] BLUE", 4, 2);
            lcdSetText("* to go back", 1, 3);

            if(pressed){
                SysTick_delay_ms(10);
                if(num==1){//if 1 is pressed
                    lcdClear();//clear LCD
                    state = RED;//go to red state
                }
                if(num==2){//if 2 is pressed
                    lcdClear();//clear LCD
                    state = GREEN;//go to green state
                }
                if(num==3){//if 3 is pressed
                    lcdClear();//clear LCD
                    state = BLUE;//go to blue state
                }

                if(num==10){//if * is pressed
                    lcdClear();//clear LCD
                    state = MAIN;//go back to main menu
                }
            }
            break;

        case RED://Red LED case
            lcdSetText("Pick Brightness", 0, 0);//print options to LCD
            lcdSetText("[0-100]",5, 1);
            lcdSetText("* to go back", 1, 3);
            lcdSetText("RED", 7, 2);
            REDLED();//call Red LED function


            if(pressed){
                if(num==10){//if * is pressed
                    lcdClear();//clear LCD
                    P2->OUT &= ~BIT5;//turn Red LED off
                    state = LIGHTS;//go back to LED menu
                }
            }

            break;

        case GREEN://green LED case
            lcdSetText("Pick Brightness", 0, 0);//print options to LCD
            lcdSetText("[0-100]",5, 1);
            lcdSetText("GREEN", 6, 2);
            lcdSetText("* to go back", 1, 3);
            GREENLED();//call green LED function

            if(pressed){
                if(num==10){//if * is pressed
                    P2->OUT &= ~BIT7;//turn off Green LED
                    lcdClear();//clear LCD
                    state = LIGHTS;//go back to LED menu
                }
            }
            break;

        case BLUE://blue LED case
            lcdSetText("Pick Brightness", 0, 0);//print options to LCD
            lcdSetText("[0-100]",5, 1);
            lcdSetText("BLUE", 6, 2);
            lcdSetText("* to go back", 1, 3);
            BLUELED();//call blue LED function

            if(pressed){
                if(num==10){//if star is pressed
                    P2->OUT &= ~BIT6;//turn blue LED off
                    lcdClear();//clear LCD
                    state = LIGHTS;//go back to light menu
                }
            }
            break;

        }
        if(stopflag == 1){//if button is pushed
            lcdClear();//clear LCD
            lcdSetText("EMERGENCY STOP", 1, 1);//print to LCD
            stopflag = 0;//reset flag
            SysTick_delay_ms(2000);//delay
            lcdClear();//clear LCD
            state = MAIN;//go back to main menu
        }

        if(rgbFlag == 1){//if button 2 is pushed
            lcdClear();//clear LCD
            lcdSetText("EMERGENCY STOP", 1, 1);//print to LCD
            rgbFlag = 0;//reset flag
            SysTick_delay_ms(2000);//delay
            lcdClear();//clear LCD
            state = MAIN;//go back to main menu
        }
    }

}

uint8_t Keypad_Read(void){//function given by Professor Krug

    uint8_t col, row;

    for(col = 0; col<3; col++){
        P4DIR = 0x00;
        P4DIR |=BIT(4+col);
        P4OUT &= ~BIT(4+col);
        SysTick_delay_ms(10);
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

/*This function initializes different pins for
 * keypad, msp on board LED's, and the two emergency stop buttons.
 */
void keyinit(){

    P4->SEL0 &= ~0xF;
    P4->SEL1 &= ~0xF;//initialize rows
    P4->DIR &= ~0xF;
    P4->REN |= 0xF;
    P4->OUT |= 0xF;

    P4->SEL0 &= ~0x70;
    P4->SEL1 &= ~0x70;//initialize columns
    P4->DIR &= ~0x70;

    /////////////////////

    P2->SEL0 &= ~BIT0;
    P2->SEL1 &= ~BIT0;//MSP LED setup
    P2->DIR |= BIT0;//red
    P2->OUT &= ~BIT0;
    P2->SEL0 &= ~BIT1;//green
    P2->SEL1 &= ~BIT1;
    P2->DIR |= BIT1;
    P2->OUT &= ~BIT1;

    //////////////////////

    P3->SEL0 &= ~BIT0;
    P3->SEL1 &= ~BIT0;//button init for DC motor stop
    P3->DIR &= ~BIT0;
    P3->REN |= BIT0;
    P3->OUT |= BIT0;

    P3->IES &= ~BIT0;//DC motor interrupt
    P3->IE |= BIT0;
    P3->IFG = 0;

    NVIC_EnableIRQ(PORT3_IRQn);//interrupt enable
    __enable_irq();

    P4->SEL0 &= ~BIT7;
    P4->SEL1 &= ~BIT7;//button init for RGB stop
    P4->DIR &= ~BIT7;
    P4->REN |= BIT7;
    P4->OUT |= BIT7;

    P4->IES &= ~BIT7;//RGB interrupt
    P4->IE |= BIT7;
    P4->IFG = 0;

    NVIC_EnableIRQ(PORT4_IRQn);//interrupt enable
    __enable_irq();

}

/*This function is from a previous lab that
 * used a PWM to control a DC motor on pin
 * 2.4 TA(2.1).
 */
void dcmoto(){
    double dutyCyc, on;

    P2->SEL1 &=~BIT4;
    P2->SEL0 |= BIT4;//Timer A initialization for Dc motor pin 2.4
    P2->DIR |= BIT4;

    TIMER_A0->CCR[0] = 30000;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;//Timer A pulse DC
    TIMER_A0->CTL = 0x0214;


    if(pressed){
        if(num == 11){//when 0 is pressed the duty cycle is 0
            dutyCyc = 0;
        }
        if(num<10){//when any other key is pressed that key is the dutycycle.
            dutyCyc = num;
        }

        on =((dutyCyc/10)*30000);//duty cycle is multiplied by period
        TIMER_A0->CCR[1] = on;//run DC motor

    }
}

/*This function takes a delay (cycle) given by the functions in
 * the door menu to tell the servo to open or close the door.
 */
void servodelay(uint16_t Cycle){

    P6->SEL1 &=~BIT6;
    P6->SEL0 |= BIT6;//Timer A initialization for servo pin 6.6
    P6->DIR |= BIT6;

    TIMER_A2->CCR[0] = (20*3000);//set period
    TIMER_A2->CCTL[3] = (0x00E0);
    TIMER_A2->CTL = (0x0214);
    TIMER_A2->CCR[3] = ((Cycle * (20*3000))/100);//run servo
}

/*This function is for the Red LED duty cycle.
 * it is similar to the DC moto function, but uses
 * Timer 0.2.
 */
void REDLED(){

    double dutyCyc, on;

    P2->SEL1 &=~BIT5;
    P2->SEL0 |= BIT5;//Timer A initialization for Dc motor pin 2.5
    P2->DIR |= BIT5;

    TIMER_A0->CCR[0] = 3750;
    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;//Timer A pulse DC
    TIMER_A0->CTL = 0x0214;


    if(pressed){
        if(num == 11){//when 0 is pressed the duty cycle is 0
            dutyCyc = 0;
        }
        if(num<10){//when any other key is pressed that key is the dutycycle.
            dutyCyc = num;
        }

        on =((dutyCyc/10)*3000);//duty cycle is multiplied by period
        TIMER_A0->CCR[2] = on;//run DC motor

    }

}

/*This function is for the Green LED duty cycle.
 * it is similar to the DC moto function, but uses
 * Timer 0.4.
 */
void GREENLED(){

    double dutyCyc, on;

    P2->SEL1 &=~BIT7;
    P2->SEL0 |= BIT7;//Timer A initialization for Dc motor pin 2.7
    P2->DIR |= BIT7;

    TIMER_A0->CCR[0] = 3750;
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;//Timer A pulse DC
    TIMER_A0->CTL = 0x0214;


    if(pressed){
        if(num == 11){//when 0 is pressed the duty cycle is 0
            dutyCyc = 0;
        }
        if(num<10){//when any other key is pressed that key is the dutycycle.
            dutyCyc = num;
        }

        on =((dutyCyc/10)*3000);//duty cycle is multiplied by period
        TIMER_A0->CCR[4] = on;//run DC motor

    }

}

/*This function is for the Blue LED duty cycle.
 * it is similar to the DC moto function, but uses
 * Timer 0.3.
 */
void BLUELED(){

    double dutyCyc, on;

    P2->SEL1 &=~BIT6;
    P2->SEL0 |= BIT6;//Timer A initialization for Dc motor pin 2.6
    P2->DIR |= BIT6;

    TIMER_A0->CCR[0] = 3750;
    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;//Timer A pulse DC
    TIMER_A0->CTL = 0x0214;


    if(pressed){
        if(num == 11){//when 0 is pressed the duty cycle is 0
            dutyCyc = 0;
        }
        if(num<10){//when any other key is pressed that key is the dutycycle.
            dutyCyc = num;
        }

        on =((dutyCyc/10)*3000);//duty cycle is multiplied by period
        TIMER_A0->CCR[3] = on;//run DC motor

    }
}


//Dc Motor E STOP interrupt handler
void PORT3_IRQHandler(){

    if((P3->IFG & BIT0)){//if button 1 is pressed
        TIMER_A0->CCR[1] = 0;//turn off motor
        stopflag = 1;//set flag
    }

    P3->IFG = 0;

}

//RGB E STOP interrupt handler
void PORT4_IRQHandler(){

    if((P4->IFG & BIT7)){//if button 1 is pressed
        TIMER_A0->CCR[2] = 0;//turn off all LED's
        TIMER_A0->CCR[3] = 0;
        TIMER_A0->CCR[4] = 0;
        rgbFlag = 1;//set flag
    }

    P4->IFG = 0;

}
