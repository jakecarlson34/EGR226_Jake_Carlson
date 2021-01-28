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
void getColorBands(char*, char*, char*, char*);
void calcResistance(char, char, char, char);
void prompt(void);//Declaring functions
int calcResistorColors(int x);
int getIntBetween ();
int getinput();

int main(){

int enteredVal;

  prompt();
  enteredVal = getIntBetween(); //function calls
  calcResistorColors(enteredVal);

 return (0);}


    void prompt(void){ //printf statements for prompt

 printf("---------------Resistor Codes-----------------------------\n");
 printf("|Character| Color  | Band 1 & 2 |  Band 3   |  Tolerance  |\n");
 printf("|    K    | Black  |      0     |*1         |             |\n");
 printf("|    N    | Brown  |      1     |*10        | +/-1%%       |\n");
 printf("|    R    | Red    |      2     |*100       | +/-2%%       |\n");
 printf("|    O    | Orange |      3     |*1,000     |             |\n");
 printf("|    Y    | Yellow |      4     |*10,000    |             |\n");
 printf("|    G    | Green  |      5     |*100,000   | +/-0.5%%     |\n");
 printf("|    B    | Blue   |      6     |*1,000,000 | +/-0.25%%    |\n");
 printf("|    V    | Violet |      7     |*10,000,000| +/-0.1%%     |\n");
 printf("|    E    | Grey   |      8     |           | +/-0.05%%    |\n");
 printf("|    W    | White  |      9     |           |             |\n");
 printf("|    D    | Gold   |            |   *0.1    | +/-5%%       |\n");
 printf("|    S    | Silver |            |   *0.01   | +/-10%%      |\n");
 printf("----------------------------------------------------------\n\n");
 printf("Choose which resistor function you would like to perform:\n");
 printf("\t(1): Determine color-code for given resistance value\n");
 printf("\t(2): Determine resistance value from given color-code\n");
}
int getinput()


void getColorBands(char*, char*, char*, char*){
    char color[10][1] = {"K",  "N", "R", "O", "Y", "G", "B", "V", "E", "W", "D", "S"};
    char *b1, *b2, *b3, *b4;

    scanf("%c%c%c%c", b1, b2, b3, b4)//to print use printf("%c", *b1)

}
void calcResistance(char, char, char, char){
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

