/**************************************************************************************
* Author: Jake Carlson
* Course: EGR 226 - 902
* Date: 02/1/2021
* Project: lab2part2
* File: main.c
* Description: This program uses structures to create a database of books from
* an external file.
*
**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifndef NULL
#define NULL 0
#endif // NULL

typedef struct{//Defining the book structure
    char title[255];
    char author_name[50];
    char ISBN[10];
    int pages;
    int year_published;
}book;
int input(int low, int high); //Functions used in program
int parse_file(char name[], book my_book_array[]);
void print_book(book entered_array[], int enter);
void search_title(book my_book_array[]);
void search_author(book my_book_array[]);
void search_ISBN(book my_book_array[]);



int main()
{
   int i , j =1, low = 0, high = 2;
   char name[25] = "BookList.csv";
   book my_book_array[360];


  parse_file(name, my_book_array);//calling function to fill array

  while(j){
        i= input(low, high);//calling input function to use what user has entered
  if(i == 0){
    search_title(my_book_array);// if 0 the program will use title function
  }
  else if(i == 1){
    search_author(my_book_array);//if 1 the program will use author function
  }
  else{
    search_ISBN(my_book_array);// if 2 the program will use ISBN function
  }}

    return 0;

}
int input(int low, int high){

    int test = 1;
    int user, loop;
    char che[10];

    printf("What would you like to search by? [0] Title, [1] Author, or [2] ISBN\n");//user prompt

    while(test){//error checking loop
        loop = scanf("%d", &user);//sets whatever the user enters to loop
        if(loop != 1){
            printf("Try again.\n");
        }
        else if (user > high){
            printf("Try again.\n");//else if's to make sure the user enters between 0 and 2
        }
        else if (user < low){
            printf("Try again.\n");
        }
        else{
        test = 0;
        }
        fflush(stdin);
    }

    che[0] = user;
    che[strlen(che) - 2] = '\0';//using array to set the entry to the first value

    user = che[0];

    return user;

}

int parse_file(char name[], book my_book_array[]){
    int i = 0;
    char chec[512];

    FILE* infile = fopen(name, "r");//opening file and returning 0 in case the file does not exist
    if (infile == NULL){
        return 0;
    }

    while(fgets(chec, 512, infile)){//loop to collect each line from given csv file

        char* point = strtok(chec, ",");//adding commas and newline

        if(strcmp(point, "N/A"))//validate string
            strcpy(my_book_array[i].title, point);//title parse

        point = strtok(NULL, ",\n");
        if(strcmp(point, "N/A"))//validate string
            strcpy(my_book_array[i].author_name, point);//author parse

        point = strtok(NULL, ",\n");
        if(strcmp(point, "N/A"))//validate string
            strcpy(my_book_array[i].ISBN, point);//ISBN parse

        else
            strcpy(my_book_array[i].ISBN, "N/A");

        point = strtok(NULL, ",\n");
        if (strcmp(point, "N/A")){//validate string
            my_book_array[i].pages = atoi (point);//page count parse
        }
        else {
            my_book_array[i].pages = -1;
        }
        point = strtok(NULL, ",\n");
        if(strcmp(point, "N/A"))//validate string
            my_book_array[i].year_published = atoi(point);//year published parse

        else {
            my_book_array[i].year_published = -1;
        }
        i++;
    }
    fclose(infile);//closing file
    return (1);
}

void print_book(book entered_array[], int enter){

    int i;

    for(i = 0; i < enter; i++){//loop that prints title, author, ISBN, page, and year published in that order
        printf("Title: %s\n", entered_array[i].title);//title print
        printf("Author: %s\n", entered_array[i].author_name);//author print
        printf("ISBN: %s\n", entered_array[i].ISBN);//ISBN print

        if(entered_array[i].pages == -1){
            printf("Pages: N/A\n");//used in case pages are N/A
        }
        else{
            printf("Pages: %d\n", entered_array[i].pages);//prints pages
            fflush(stdout);
        }
        if(entered_array[i].year_published == -1){
            printf("Published: N/A\n");//used if year published is N/A
        }
        else{
            printf("Published: %d\n\n", entered_array[i].year_published);//prints year published
        }
    }
    return (0);

}

void search_title(book my_book_array[]){

    char cha1[50], cha2[50], cha3[50];
    int i, j = 0, num = 360;
    char* posis = NULL; //pointer in case no title is found
    book my_entered[512];

    printf("Enter Title criteria:\n");//user prompt


    fgets(cha1, 50, stdin);
    fflush(stdin);
    cha1[strlen(cha1)-1] = '\0';//fgets for the users search input

    strcpy(cha2, cha1);//copying the entered characters and changing the first to an uppercase character
    cha2[0] = toupper(cha2[0]);

    strcpy(cha3, cha1);//copying again to make all of the characters uppercase

    for(i = 0; i < strlen(cha1); i++){
        cha3[i] = toupper(cha3[i]);
    }

    for(i = 0; i < num; i++){

        posis = (strstr(my_book_array[i].title, cha1));

        if(posis != NULL){//if statement when not NULL there is a match
            strcpy(my_entered[j].title, my_book_array[i].title);//copying one array to the others
            strcpy(my_entered[j].author_name, my_book_array[i].author_name);
            strcpy(my_entered[j].ISBN, my_book_array[i].ISBN);
            my_entered[j].pages = my_book_array[i].pages;
            my_entered[j].year_published = my_book_array[i].year_published;

            j++;
        }
        posis = (strstr(my_book_array[i].title, cha2));
        if(posis != NULL){//if statement when not NULL there is a match
            strcpy(my_entered[j].title, my_book_array[i].title);//copying one array to the others
            strcpy(my_entered[j].author_name, my_book_array[i].author_name);
            strcpy(my_entered[j].ISBN, my_book_array[i].ISBN);
            my_entered[j].pages = my_book_array[i].pages;
            my_entered[j].year_published = my_book_array[i].year_published;

            j++;
        }
        posis = (strstr(my_book_array[i].title, cha3));
        if(posis != NULL){//if statement when not NULL there is a match
            strcpy(my_entered[j].title, my_book_array[i].title);//copying one array to the others
            strcpy(my_entered[j].author_name, my_book_array[i].author_name);
            strcpy(my_entered[j].ISBN, my_book_array[i].ISBN);
            my_entered[j].pages = my_book_array[i].pages;
            my_entered[j].year_published = my_book_array[i].year_published;

            j++;
        }
    }
    if(strlen(my_entered[0].title) == 0){//check to see if character string exists and the length if it does
        printf("No Title found.\n");
    }
    print_book(my_entered, j);//passing needed array and int back to print book

    return (0);

}

void search_author(book my_book_array[]){

    char cha1[50], cha2[50], cha3[50];
    int i, j =0, num = 360;
    char* posis = NULL;//pointer in case no title is found
    book my_entered[512];

    printf("Enter Author criteria:\n");//user prompt


    fgets(cha1, 50, stdin);//fgets for user search input
    fflush(stdin);
    cha1[strlen(cha1)-1] = '\0';

    strcpy(cha2, cha1);//copying the entered characters and changing the first to an uppercase character
    cha2[0] = toupper(cha2[0]);

    strcpy(cha3, cha1);//copying again to make all of the characters uppercase

    for(i = 0; i < strlen(cha1); i++){
        cha3[i] = toupper(cha3[i]);
    }


    for(i = 0; i < num; i++){

        posis = strstr(my_book_array[i].author_name, cha1);

        if(posis != NULL){//if statement when not NULL there is a match
            strcpy(my_entered[j].title, my_book_array[i].title);//copying one array to the others
            strcpy(my_entered[j].author_name, my_book_array[i].author_name);
            strcpy(my_entered[j].ISBN, my_book_array[i].ISBN);
            my_entered[j].pages = my_book_array[i].pages;
            my_entered[j].year_published = my_book_array[i].year_published;

            j++;
        }
        posis = (strstr(my_book_array[i].author_name, cha2));
        if(posis != NULL){//if statement when not NULL there is a match
            strcpy(my_entered[j].title, my_book_array[i].title);//copying one array to the others
            strcpy(my_entered[j].author_name, my_book_array[i].author_name);
            strcpy(my_entered[j].ISBN, my_book_array[i].ISBN);
            my_entered[j].pages = my_book_array[i].pages;
            my_entered[j].year_published = my_book_array[i].year_published;

            j++;
        }
        posis = (strstr(my_book_array[i].author_name, cha3));
        if(posis != NULL){//if statement when not NULL there is a match
            strcpy(my_entered[j].title, my_book_array[i].title);//copying one array to the others
            strcpy(my_entered[j].author_name, my_book_array[i].author_name);
            strcpy(my_entered[j].ISBN, my_book_array[i].ISBN);
            my_entered[j].pages = my_book_array[i].pages;
            my_entered[j].year_published = my_book_array[i].year_published;

            j++;
        }
    }

    if(strlen(my_entered[0].title) == 0){//check to see if character string exists and the length if it does
        printf("No Author found.\n");
    }
    print_book(my_entered, j);//passing array and int to print book

    return (0);


}

void search_ISBN(book my_book_array[]){

    book my_entered[512];
    int i, j = 0, num = 360;
    char* posis = NULL;//pointer in case no title is found
    char cha1[50];

    printf("Enter ISBN criteria:\n");//user prompt

    fgets(cha1, 50, stdin);//fgets the users search input
    fflush(stdin);
    cha1[strlen(cha1)-1] = '\0';

    for(i = 0; i < num; i++ ){//going throughout the array to locate users search input
        posis = strstr(my_book_array[i].ISBN, cha1);

        if(posis != NULL){//match found again as long as not NULL
            strcpy(my_entered[j].title, my_book_array[i].title);//copying one array to the others
            strcpy(my_entered[j].author_name, my_book_array[i].author_name);
            strcpy(my_entered[j].ISBN, my_book_array[i].ISBN);
            my_entered[j].pages = my_book_array[i].pages;
            my_entered[j].year_published = my_book_array[i].year_published;

            j++;
        }
    }
    if(strlen(my_entered[0].title) == 0){//check to see if character string exists and the length if it does
        printf("ISBN not found.\n");
    }
    print_book(my_entered, j);//passing array and int to print book

    return (0);
}
