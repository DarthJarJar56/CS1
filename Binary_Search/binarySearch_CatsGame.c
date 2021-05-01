/*
Problem Statement:
Using a binary search, create a warmer or colder "Guess The Number" game
in which given the range of values, the computer will continuously guess numbers
until it finds the correct value that the user is thinking of.

To signal that a guess is warmer, the user should input "No. Warmer."
To signal that a guess is colder, the user should input "No. Colder."
To signal that a guess is exactly equidistant from the users value and the previous guess,
the user should input "No. No Change."

Written on 02/09/2021
*/

// This code is pretty inefficient and could definitely be way better
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void);
int main()
{
    //Define all variables
    int high, low, mid, lastGuess;
    char feedback[30];

    //Scan in user inputted max value for the range of numbers in the binary search
    scanf("%d", &high);

    //initialize the minimum value to 1, calculate initial mid value
    low = 1;
    mid = (high + low) / 2;

    //Give initial guess. Not a useful number
    printf("%d\n", mid);
    fflush(stdout);
    scanf(" %s", feedback);

    if (strcmp(feedback, "Yes.") == 0) //If the initial midpoint somehow ends up being the correct value, this will terminate the program.
    {
        return 0;
    }

    else if (strcmp(feedback, "No.") == 0) //This will determine the direction that the target is in.
    {
        mid = mid - 1;
        printf("%d\n", mid);
        fflush(stdout);
    }

    while (low <= high) //Main loop of the program
    {
        scanf(" %s", feedback);            //Scans for the first word of user input
        if (strcmp(feedback, "Yes.") == 0) //Terminates program when first word of user input is "Yes.", signaling success
        {
            return 0;
        }
        else if (strcmp(feedback, "Game") == 0) //Terminates program when first word of user input is "Game", signaling Game Over
        {
            return 0;
        }
        else if (strcmp(feedback, "No.") == 0) //Main if statement. Executes when first word is "No.", signaling either "No. Colder", "No. Warmer.", "No. No Change."
        {
            scanf(" %s", feedback);

            if (strcmp(feedback, "Colder.") == 0) //If initial midpoint - 1 is determined to be colder, changes range of search to top half
            {
                low = mid + 1;
                mid = (high + low) / 2;
                printf("%d\n", mid);
                fflush(stdout);
            }
            else if (strcmp(feedback, "Warmer.") == 0) //If initial midpoint - 1 is determined to be warmer, changes range of search to bottom half
            {
                high = mid;
                mid = (high + low) / 2;
                printf("%d\n", mid);
                fflush(stdout);
            }
            else if (strncmp(feedback, "No", 5) == 0) //Searches for "No. No Change"
            {
                lastGuess = mid;
                mid = (lastGuess + low) / 2;
                printf("%d\n", mid);
                fflush(stdout);
            }
        }

        scanf(" %s", feedback);

        if (strcmp(feedback, "Yes.") == 0) //Terminates program if "Yes." is detected, signaling success
        {
            return 0;
        }
        else if (strcmp(feedback, "Game") == 0) //Terminates program if "Game" is detected, signaling "Game Over"
        {
            return 0;
        }
        else if (strcmp(feedback, "No.") == 0) //Main if statement. Detects "No. " signaling, "No. Colder.", "No. Warmer", or "No. No Change."
        {
            
            scanf("%s", feedback);

            if (strcmp(feedback, "Colder.") == 0) //Checks for which direction to shift the range to
            {
                mid = mid - 1;
                printf("%d\n", mid);
                fflush(stdout);
            }
            else if (strcmp(feedback, "Warmer.") == 0) //Checks for which direction to shift the range to
            {
                mid = mid - 1;
                printf("%d\n", mid);
                fflush(stdout);
            }
            else if (strncmp(feedback, "No", 5) == 0) //Calculates the exact middle of the range between current guess and previous guess to find the correct value
            {
                lastGuess = mid;
                mid = (lastGuess + low) / 2;
                printf("%d\n", mid);
                fflush(stdout);
            }
        }
    }
}
