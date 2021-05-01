/*
Problem Statement:
Given a series of words and phrases, print out a "handle" for each word
A "handle" is defined as the first and last letter of each word.
- Ex) John Smith -> JnSh

Written on 04/11/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

//all in main :)
int main()
{
    //Declare variables
    char str[MAX];
    int n;
    
    //obtain user input for amount of handles to generate
    scanf("%d", &n);
    getchar(); //returns chars as a value in fgets

    //Loop through the amount of lines user inputted
    for (int i = 0; i < n; i++)
    {
        //scan entire lines at once
        fgets(str, MAX, stdin); 
        
        //initialize length variable for use in nested for loop
        int len = strlen(str);

        //traverse the individual lines to determine which chars to print
        for (int j = 0; j < len; j++)
        {
            //case for when a line is only 1 character
            if (len == 1 && str[j + 1] == '\n')
            {
                printf("%s", str);
                printf("\n");
                break;
            }

            //Case for the very first character on each line
            if (str[j-1] == NULL && str[j+1] != '\n')
            {
               printf("%c", str[j]);
            }
            //print to the left and right of every space
            else if (str[j] == ' ')
            {
                if (str[j-1] == ' ' || str[j+1] == ' ')
                {
                    continue;
                }
                printf("%c%c", str[j-1], str[j + 1]);
            }
            //case for the very last letter on each line
            else if (str[j + 1] == '\n')
            {
                printf("%c", str[j]);
            }
        }
        //print a new line after each handle is printed
        printf("\n");
    }
    return 0; // yay :)
}