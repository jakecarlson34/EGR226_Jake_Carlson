#include <stdio.h>
#include <stdlib.h>

/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 02/1/2021
* Project: lab21part1
* File: lab2part1main.c
* Description: This program takes an input from the user in ohms and solves to find the
* resistors color-bands or takes color-bands and converts to resistance.
*
**************************************************************************************/
void getColorBands(char*, char*, char*, char*);
void calcResistance(char, char, char, char);
void prompt(void);//Declaring function protoypes
int calcResistorColors(int x);
int getIntBetween ();
int getinput();

int main(){

int enteredVal;
int userChoice;
int goodEnter = 0;
char c1, c2, c3, c4;


prompt();
do{
    printf("Please enter a 1 to convert a resistance value to a color code.\n");//new user prompt
    printf("Please enter a 2 to convert a color code to a resistance value.\n");
    scanf("%d", &userChoice);

    if(userChoice == 1){//if user chooses 1 then call functions from previous lab
        enteredVal = getIntBetween(); //function calls
        calcResistorColors(enteredVal);
        goodEnter = 1;
    }
    else if(userChoice == 2){//if 2 call new functions and new prompt
    printf("Enter A Character for band 1:");
    scanf(" %c", &c1);
    printf("\nEnter A Character for band 2:");
    scanf(" %c", &c2);
    printf("\nEnter A Character for band 3:");
    scanf(" %c", &c3);
    printf("\nEnter A Character for band 4:");
    scanf(" %c", &c4);

        getColorBands(c1, c2, c3, c4);
        calcResistance(c1, c2, c3, c4);
        goodEnter = 1;
    }

    else{
        printf("Error\n");//error check
        goodEnter = 0;
    }
} while(goodEnter != 1);

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

}
int getIntBetween (int val){

    printf("Please enter a value from 1 to 99M ohms\n");
    val = 0; //Value entered
    char wrong[100]; //storage for error when using alphabet
    int pro, i=0;

while(i == 0){ //while loop to make sure value is between 1 and 99

    pro= scanf("%d", &val);

    if (pro == 1){
    if (val > 0 && val <= 99000000){//checking value
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

    if (counter == 0){//assigning band 3 with 0-7
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

 void getColorBands(char* c1, char* c2, char* c3, char* c4){//new function that passes with pointers
   char color[4] = {c1, c2, c3, c4};

   printf("Resistor color code entered: %c, %c, %c, %c\n", c1, c2, c3, c4);

   return (0);
 }

 void calcResistance(char c1, char c2, char c3, char c4){


    int b1, b2, b3, total;
    double b4;

//band 1
    if(c1 == 'K'){//assigning band 1 with 0-90
        b1 = 0;
    }
    else if(c1 == 'N'){//going by increments of 10 since it is added to band 2 later
        b1 = 10;
    }
    else if(c1 == 'R'){
        b1 = 20;
    }
    else if(c1 == 'O'){
        b1 = 30;
    }
    else if(c1 == 'Y'){
        b1 = 40;
    }
    else if(c1 == 'G'){
        b1 = 50;
    }
    else if(c1 == 'B'){
        b1 = 60;
    }
    else if(c1 == 'V'){
        b1 = 70;
    }
    else if(c1 == 'E'){
        b1 = 80;
    }
    else {
        b1 = 90;
    }

//band 2

    if(c2 == 'K'){//assigning band 2 with 0-9
        b2 = 0;
    }
    else if(c2 == 'N'){
        b2 = 1;
    }
    else if(c2 == 'R'){
        b2 = 2;
    }
    else if(c2 == 'O'){
        b2 = 3;
    }
    else if(c2 == 'Y'){
        b2 = 4;
    }
    else if(c2 == 'G'){
        b2 = 5;
    }
    else if(c2 == 'B'){
        b2 = 6;
    }
    else if(c2 == 'V'){
        b2 = 7;
    }
    else if(c2 == 'E'){
        b2 = 8;
    }
    else {
        b2 = 9;
    }

//band 3

     if(c3 == 'K'){//assigning band 3 with appropriate multiplier
        b3 = 1;
    }
    else if(c3 == 'N'){
        b3 = 10;
    }
    else if(c3 == 'R'){
        b3 = 100;
    }
    else if(c3 == 'O'){
        b3 = 1000;
    }
    else if(c3 == 'Y'){
        b3 = 10000;
    }
    else if(c3 == 'G'){
        b3 = 100000;
    }
    else if(c3 == 'B'){
        b3 = 1000000;
    }
    else if(c3 == 'V'){
        b3 = 10000000;
    }
    else if(c3 == 'D'){
        b3 = 0.1;
    }
    else if(c3 == 'S'){
        b3 = 0.01;
    }

    else {
        b3 = 0;
    }

    //band 4
    if(c4 == 'K'){//assigning band 4 with appropriate tolerance
        b4 = 1;
    }
    else if(c4 == 'N'){
        b4 = 2;
    }
    else if (c4 == 'G'){
        b4 = 0.5;
    }
    else if(c4 == 'B'){
        b4 = 0.25;
    }
    else if(c4 == 'V'){
        b4 = 0.1;
    }
    else if(c4 == 'E'){
        b4= 0.05;
    }
    else if(c4 == 'D'){
        b4 = 5;
    }
    else if(c4 == 's'){
        b4 = 10;
    }
    else {
        b4 = 0;
    }

    total = ((b1+b2)*b3);//adding band 1 and 2 then multiplying by the multiplier

    printf("This resistor is [%d]Ohms with a +/-%g%% tolerance.", total, b4);//final print


return (0);
}

