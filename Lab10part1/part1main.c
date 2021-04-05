/**************************************************************************************
 * Author: Jake Carlson
 * Course: EGR 226 - 902
 * Date: 04/1/2021
 * Project: lab10part1
 * File: part1main.c
 * Description: This program print the voltage that is changed by the 10k Potentiometer
 * every second.
 *
 **************************************************************************************/


#include "msp.h"
#include <stdio.h>
#include <stdlib.h>

//function prototypes
void adcsetup(void);//adc initialization
void SysTick_Delay(uint16_t delayms);
void SysTick_init();


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	P5->SEL1 |= BIT5;
	P5->SEL0 |= BIT5;//potentiometer init
	P5->DIR &= ~BIT5;

	float volt;
	uint16_t var;

	SysTick_init();
	adcsetup();

	while(1){
	    ADC14->CTL0 |=1;//start the a to d converting
	    while(!ADC14->IFGR0);
	    var= ADC14->MEM[5];//saving to variable
	    volt = (var * 3.3)/16384;//voltage calculation
	    printf("VOLTAGE = %g\n",volt);//print voltage
	    SysTick_Delay(1000);//delay 1 second

	}


}
void adcsetup(void){//code given by Professor Krug in lecture
    ADC14->CTL0 = 0x00000010;
    ADC14->CTL0 |= 0x04D80300;

    ADC14->CTL1 = 0x00000030;
    ADC14->MCTL[5] = 0;
    P5->SEL1 |= 0x20;
    P5->SEL0 |= 0x20;
    ADC14->CTL1 |= 0x00050000;
    ADC14->CTL0 |= 2;


}
void SysTick_init(){//SysTick Initialization from previous labs
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000005;
}

void SysTick_Delay(uint16_t delayms){//delay function from previous labs
    SysTick->LOAD = ((delayms *3000)-1);
    SysTick->VAL = 0;
    while((SysTick->CTRL & 0x00010000)==0);

}
