#include <stdio.h>
#include <stdlib.h>

/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 01/20/2021
* Project: lab01part1
* File: main.c
* Description: This program takes an input from the user in ohms and solves to find the
* resistors color-bands.
*
**************************************************************************************/

void prompt(void);//Declaring functions
int calcResistorColors(int x);
int getIntBetween ();

int main(){

int enteredVal;

  prompt();
  enteredVal = getIntBetween(); //function calls
  calcResistorColors(enteredVal);

 return (0);}


    void prompt(void){ //printf statements for prompt

 printf("---------------Resistor Codes---------------\n");
 printf("|Character| Color  | Band 1 & 2 |  Band 3   |\n");
 printf("|    K    | Black  |      0     |*1         |\n");
 printf("|    N    | Brown  |      1     |*10        |\n");
 printf("|    R    | Red    |      2     |*100       |\n");
 printf("|    O    | Orange |      3     |*1,000     |\n");
 printf("|    Y    | Yellow |      4     |*10,000    |\n");
 printf("|    G    | Green  |      5     |*100,000   |\n");
 printf("|    B    | Blue   |      6     |*1,000,000 |\n");
 printf("|    V    | Violet |      7     |*10,000,000|\n");
 printf("|    E    | Grey   |      8     |           |\n");
 printf("|    W    | White  |      9     |           |\n");
 printf("|    D    | Gold   |            |           |\n");
 printf("|    S    | Silver |            |           |\n");
 printf("---------------------------------------------\n\n");
 printf("Choose a resistance value to have decoded into it's color-bands.\n");
}


int getIntBetween (int val){

val = 0; //Value entered
char wrong[100]; //storage for error when using alphabet
int pro, i=0;

while(i == 0){ //while loop to make sure value is between 1 and 99

    pro= scanf("%d", &val);

    if (pro == 1){
    if (val > 0 && val <= 99000000){
        i += 1;
    }
    else {
        printf("Please enter a value from 1 to 99M ohms\n");
    }
    }
    else{
        scanf("%s", &wrong);//saving the incorrect characters to wrong
        printf("Please enter a value from 1 to 99M ohms\n");
    }
}
return (val);

}



int calcResistorColors(int enteredVal){

    char colors [10][10] = {
    "Black", "Brown", "Red", "Orange", "Yellow", "Green", "Blue", "Violet", "Grey", "White" //array for colors of resistor bands
};

    int b1, b2, b3; //declaring band 1 band 2 and band 3;
    int counter = 0;


 printf("A resistor of %d Ohms would have a color code of: ", enteredVal);




        do{
            enteredVal = enteredVal/10;
            counter = counter +1;
}
    while (enteredVal >= 100);//do while loop to divide the resistor value by 10 and increment a counter variable

    if (counter == 0){
        b3 =0;
 }
    else if (counter ==1){
        b3 =1;
 }
    else if (counter ==2){
        b3 =2;
 }
    else if (counter ==3){
        b3 =3;
 }
    else if (counter ==4){
        b3 =4;
 }
    else if (counter ==5){
        b3 =5;
 }
    else if (counter ==6){
        b3 =6;
 }
    else if (counter ==7){
        b3 =7;
 }
            b1 = enteredVal / 10;
            b2 = enteredVal % 10;

printf(" %s-%s-%s", colors[b1], colors[b2], colors[b3]); //final printf




 return (enteredVal);}

