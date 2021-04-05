/**************************************************************************************
 * Author: Jake Carlson
 * Course: EGR 226 - 902
 * Date: 04/1/2021
 * Project: lab10part2
 * File: part2main.c
 * Description: This program takes the signal from the temp sensor and converts to
 * a digital sample to be printed.
 *
 **************************************************************************************/


#include "msp.h"
#include <stdio.h>
#include <stdlib.h>

//function prototype
void adcsetup(void);
void SysTick_initinter();
void SysTick_Handler();



void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    P5->SEL1 |= BIT5;
    P5->SEL0 |= BIT5;//pin used for temp sensor
    P5->DIR &= ~BIT5;



    SysTick_initinter();
    adcsetup();
    __enable_irq();


    while(1){

       ;//hardwar doing work

    }


}
void SysTick_Handler(){//systick interrupt handler
    float f, c;
        uint16_t var;
    ADC14->CTL0 |=1;//start the conversion
    while(!ADC14->IFGR0);
    var= ADC14->MEM[5];//save value from ADC to var


    c = ((((var * 3.3)/16384)*1000)-500)/10;//Celsius calculation
    f = (1.8*c)+32;//Fahrenheit calculation
    printf("Celsius = %g\n",c);//print
    fflush(stdout);
    printf("Fahrenheit = %g\n", f);//print
    fflush(stdout);

}
void adcsetup(void){//code given by Professor Krug
    ADC14->CTL0 = 0x00000010;
    ADC14->CTL0 |= 0x04D80300;

    ADC14->CTL1 = 0x00000030;
    ADC14->MCTL[5] = 0;
    P5->SEL1 |= 0x20;
    P5->SEL0 |= 0x20;
    ADC14->CTL1 |= 0x00050000;
    ADC14->CTL0 |= 2;


}
void SysTick_initinter(){//SysTick Initialization from previous labs
    SysTick->CTRL = 0;
    SysTick->LOAD = 3000000; //3000 * 1 ms for 1 second interrupt
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000007;
}


