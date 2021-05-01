/*
Problem Statement:
Using a recursive sorting algorithm, sort a given list of people by their total net worth
in terms of units and print them in reverse order. 
Compute their total unit net worth given their bill and token net worth, 
along with the conversion rates of those currencies. 

Written on 03/08/2021
*/

#include <stdio.h>
#include <stdlib.h>

//typedef my struct so that I can refer to it as just "individual" rather than "struct individual"
typedef struct individual
{
    char name[21];
    long long int billCount;  //use of long long int rather than int for precision
    long long int tokenCount; // ^
    long long int totalUnits; // ^^
} individual;

/* Function prototype */
void mergeSort(individual *gamePeople, int n);

//main function
int main(void)
{
    //declare all variables
    int size, i;
    long long int tokenValue, billValue;

    //scan for user inputted amount of gameland citizens
    scanf("%d", &size);

    //dynamically allocate an array of structs representing 
    //all the gameland citizens relative to the user inputted size
    individual *gamePeople = malloc(size * sizeof(individual));

    //scan for the gameland people's names, token count, and bill count, and store in 
    //the array of structs
    for (i = 0; i < size; i++)
    {
        scanf("%s", gamePeople[i].name);
        scanf("%lld", &gamePeople[i].tokenCount);
        scanf("%lld", &gamePeople[i].billCount);
    }

    //obtain currency value ratio from the user
    scanf("%lld", &tokenValue);
    scanf("%lld", &billValue);

    //compute the total unit value of each gameland person and assign it to each
    //element in our array of structs
    for (i = 0; i < size; i++)
    {
        gamePeople[i].totalUnits = (gamePeople[i].tokenCount * billValue) + (gamePeople[i].billCount * tokenValue);
    }

    //call recursive mergeSort function
    mergeSort(gamePeople, size);

    //print only the names of the sorted array of structs in reverse order
    for (i = size; i >= 0; i--)
    {
        printf("%s\n", gamePeople[i].name);
    }
    free(gamePeople); //can't forget to free, no one likes memory leaking :(
}

//Main sorting recursive algorithm, modified to take array of structs as a parameter
void mergeSort(individual *gamePeople, int len)
{
    // Base case
    if (len <= 1)
    {
        return;
    }

    //determine the midpoint of the array and split the array
    int mid = len / 2;

    //recursive calls to sort each side of the array
    mergeSort(gamePeople, mid);
    mergeSort(gamePeople + mid, len - mid);

    // merge the array
    // temp array will dynamically store the current array during the merge
    individual *temp = (individual *)malloc(len * sizeof(individual));
    int fptr = 0;
    int bptr = mid;

    //transverse the array
    for (int i = 0; i < len; i++)
    {
        if (fptr < mid && bptr < len)
        {
            //use the units value within each struct as the "key" that the sort is based on
            //compare the unit values of the structs to each other to sort the array of structs properly
            if (gamePeople[fptr].totalUnits < gamePeople[bptr].totalUnits)
            {
                temp[i] = gamePeople[fptr];
                fptr++;
            }
            else
            {
                temp[i] = gamePeople[bptr];
                bptr++;
            }
        }
        else if (fptr < mid)
        {
            temp[i] = gamePeople[fptr];
            fptr++;
        }
        else
        {
            temp[i] = gamePeople[bptr];
            bptr++;
        }
    }
    for (int i = 0; i < len; i++)
        gamePeople[i] = temp[i];
    free(temp); //always gotta have the free, memory leaking bad :(
}