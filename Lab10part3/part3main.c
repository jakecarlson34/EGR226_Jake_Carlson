/**************************************************************************************
 * Author: Jake Carlson
 * Course: EGR 226 - 902
 * Date: 04/1/2021
 * Project: lab10part3
 * File: part3main.c
 * Description: This program uses the LCD to print the current temp and a push button
 * to cycle between Farenheit and Celsius.
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
void adcsetup(void);
void PORT5_IRQHandler();
volatile int i = 0, x = 0;




void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    P5->SEL1 |= BIT5;
    P5->SEL0 |= BIT5;//temp sensor
    P5->DIR &= ~BIT5;

    P5->SEL0 &= ~BIT0;
    P5->SEL1 &= ~BIT0;//button init from previous lab
    P5->DIR &= ~BIT0;
    P5->REN |= BIT0;
    P5->OUT |= BIT0;
    P5->IES &= ~BIT0;
    P5->IE |= BIT0;



//calling functions
    adcsetup();
    __enable_irq();
    SysTickInit_NoInterrupts();
    lcdInit();

    NVIC_EnableIRQ(PORT5_IRQn);//interrupt enable
    NVIC_EnableIRQ(TA0_0_IRQn);

    TIMER_A0->CCR[0] = 23450;
    TIMER_A0->CTL = 0b1011010000;
    TIMER_A0->EX0 = 0b111;
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;//Timer A set up

    lcdSetText("TEMP:", 5 ,0);//function from LCD library
    x=0;

    while(1){

        float f, c;
        uint16_t var = 0;
        ADC14->CTL0 |=1;//start ADCX
        while(!ADC14->IFGR0);
        var= ADC14->MEM[5];//save value of ADC to var



        c = ((((var * 3.3)/16384)*1000)-500)/10;//temp calculations
        f = (1.8*c)+32;

        if(i==1){
            if(x==1){//if button is pushed switch to Celsius

                lcdSetInt(c, 5, 1);//print celsius value on LCD
                lcdWriteData(0b11011111);//degree symbol
                lcdSetChar('C', 8 , 1);//print C
                i = 0;
            }
            if(x==0){//start with Farenheit

                lcdSetInt(f, 5, 1);//print Farenheit value on LCD
                lcdWriteData(0b11011111);//degree symbol
                lcdSetChar('F', 8 , 1);//print F
                i=0;
            }
        }


    }


}

void PORT5_IRQHandler(){//button handler
    SysTick_delay_ms(40);
    if((P5->IFG & BIT0)&&(x==0)){//if button 1 is pressed
         x++;

    }
        else{
            x--;

    }
    P5->IFG = 0;

}
void TA0_0_IRQHandler(void){//timer a handler

    i = 1;
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
}
void adcsetup(void){//ADC setup from Professor Krug
    ADC14->CTL0 = 0x00000010;
    ADC14->CTL0 |= 0x04D80300;

    ADC14->CTL1 = 0x00000030;
    ADC14->MCTL[5] = 0;
    P5->SEL1 |= 0x20;
    P5->SEL0 |= 0x20;
    ADC14->CTL1 |= 0x00050000;
    ADC14->CTL0 |= 2;


}



