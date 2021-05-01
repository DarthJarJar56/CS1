/*
Problem statement:
Using a brute force algorithm, given the phrase inputted by the user, compute an arrangement
of strings that satisfies the following condition:
- All the final letters of a word must match the first letter of the following word:
- Ex) red dads seek karaoke is an example of a "Pretty Phrase"

Written on 02/22/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function prototypes 
int bigRec(int MAX, int index, int * permIndices, int * used, char wordsArray[MAX][21]);
int prettyCheck(int MAX, int * permIndices, char wordsArray[MAX][21]);

//The place where all the magic happens. 
//This function will perform the brunt of the permuation
int bigRec(int MAX, int index, int * permIndices, int * used, char wordsArray[MAX][21])
{
    //Base case to prevent program from infinite looping
    if(MAX == index)
    {
        //pass to prettyCheck to loop through the array and check if it's pretty
        //if prettyCheck returned 1, we enter the if statement
        if(prettyCheck(MAX, permIndices, wordsArray))
        {
            //We have found our pretty phrase! :))
            for (int i = 0; i < MAX; i++)
            {
                int pos = permIndices[i];
                printf("%s ", wordsArray[pos]);
            }
            printf("\n");
            exit(0); //terminates after finding a pretty phrase, we only want 1 pretty phrase
        }
        return 0;
    }

    //The actual permutation and recursive function call
    for (int i = 0; i < MAX; i++)
    {
        if (!used[i])
        {
            permIndices[index] = i;
            used[i] = 1;
            bigRec(MAX, index + 1, permIndices, used, wordsArray); //index + 1 to make sure we hit the base case
            used[i] = 0;
        }
    }
    return 0;
}

//Function to loop through the array, and compare the last letters
//with the first letters of the following word
int prettyCheck(int MAX, int * permIndices, char wordsArray[MAX][21])
{
    for (int i = 0; i < MAX - 1; i++)
    {
        //create variable that updates with every iteration to represent the last character
        int lastChar = strlen(wordsArray[permIndices[i]]) - 1;
        if(wordsArray[permIndices[i]][lastChar] != wordsArray[permIndices[i + 1]][0])
            return 0; //ends the for loop because the current permutation was not pretty :(
    }
    //if a permutation makes it all the way through the for loop without hitting the return 0;
    //the wordsArray must be pretty
    return 1; 
}

int main()
{
    // Declare variables and create 2D array of strings
    int size, i;

    scanf("%d", &size);
    char wordsArray[size][21];

    //read in array of strings from user
    for (i = 0; i < size; i++)
    {
        scanf("%s", wordsArray[i]);
    }

    //initialize our int arrays to all 0s. We will be modifying these
    //to find all permutations of our wordsArray.
    int * used = calloc(size, sizeof(int));
    int * permIndices = calloc(size, sizeof(int));
    
    //call main recursive function
    bigRec(size, 0, permIndices, used, wordsArray);

    free(used);
    free(permIndices);
}
