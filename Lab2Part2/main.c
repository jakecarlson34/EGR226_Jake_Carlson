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

typedef struct{
    char title[255];
    char author_name[50];
    char ISBN[10];
    int pages;
    int year_published;
}book;
int parse_file(char, book);
void print_book();
void search_title();
void search_author();
void search_ISBN();


int main()
{
    book my_book_array[360];
    int user, loop;
    int low = 0, high = 2, checkVal = 1;
    char name[12] = "BookList.csv";



    printf("What would you like to search by? [0] Title, [1] Author, or [2] ISBN\n");
    fflush(stdout);

    while(checkVal){
        loop = scanf("%d", &user);
        if(loop != 1){
            printf("Try again.\n");
            fflush(stdout);
        }
        else if (loop > high){
            printf("Try again.\n");
            fflush(stdout);
        }
        else if (loop < low){
            printf("Try again.\n");
           fflush(stdout);
        }
        checkVal = 0;
    }
    fflush(stdin);
  //  printf("%d", user);

  pars_file(name, my_book_array);

    return 0;
}

int parse_file(char name, book my_book_array[]){
    int i = 0;
    char chec[550];


}
