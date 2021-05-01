/*
Problem statement:
Using backtracking, generate a valid grid of Bs and Rs
using the inputted group and subgroup sizes
as constraints for each row and column. 

Ex) 
5 5         // Represents the dimensions of the grid
1 5         // 1 group of 5 Bs, represents row 0
2 2 1       // 2 groups, the first group being size 2, second being size 1
2 1 1       //row 2
2 3 1       //row 3
1 5         //row 4
2 1 2       //column 0
1 5         //column 1
2 2 2       //column 2
3 1 1 1     //column 3
2 2 2       //column 4

The resulting grid for the above input would be:

BBBBB
rBBrB
rBrBr
BBBrB
BBBBB
*/

#include <stdio.h>
#include <stdlib.h>

/* For ease of understanding */
#define BLACK 1
#define RED 2
#define SUCCESS 1
#define FAIL 0

// Struct for input
typedef struct INFO
{
    int groups;
    int subG[20];
} INFO;

//Struct used to keep track of the amount of groups and subgroups of a current attempt
typedef struct TRACKER
{
    int numGroups;
    int subGroupSizes[20];
} TRACKER;

/* Function Prototypes */
int valid(INFO *rowArray, INFO *colArray, int row, int col);
int solve(INFO *rowArray, INFO *colArray, int row, int col);
void printFinalGrid(void);
int checkRow(INFO *rowArray, int row, int col);
int checkCol(INFO *colArray, int row, int col);
int finalRowCheck(INFO * rowArray, TRACKER trackR, int row);
int finalColCheck(INFO * colArray, TRACKER trackC, int col);
void nukeTheGarden(INFO *rowArray, INFO *colArray);

//global variables for ease of use
int x, y, i, j, **grid;

int main(void)
{
    //obtain user input for size of grid
    scanf("%d %d", &x, &y);

    //allocate an array of structs based on the user inputted grid size
    INFO *rowArray = calloc(x, sizeof(INFO));
    INFO *colArray = calloc(y, sizeof(INFO));

    //allocate the 2d grid array
    grid = (int **)calloc(x, sizeof(int *));
    for (i = 0; i < x; i++)
        grid[i] = (int *)calloc(y, sizeof(int));

    //scan for the group and subgroup counts for the rows
    for (i = 0; i < x; i++)
    {
        scanf("%d", &rowArray[i].groups);
        for (j = 0; j < rowArray[i].groups; j++)
        {
            scanf("%d", &rowArray[i].subG[j]);
        }
    }

    //scan for the group and subgroup counts for the columns
    for (i = 0; i < y; i++)
    {
        scanf("%d", &colArray[i].groups);
        for (int j = 0; j < colArray[i].groups; j++)
        {
            scanf("%d", &colArray[i].subG[j]);
        }
    }

    // pass 0, 0 to the solve function to start at the top left
    if (solve(rowArray, colArray, 0, 0) == SUCCESS)
    {
        printFinalGrid();
    }
    else
    {
        //we should NEVER hit this, but just in case, so the program doesn't just blow up
        printf("No solution \n");
    }

    //blow it up
    nukeTheGarden(rowArray, colArray);

    return 0;
}

/* MAIN BACKTRACKING FUNCTION */
// Move through the grid by using recursive calls to slowly all to the column value
// to simulate moving through a grid from top-left to bottom-right

//Try both black and red flowers for each spot, and check if they're valid, and if they're not
//Backtrack by setting the current spot to 0, and moving back

int solve(INFO *rowArray, INFO *colArray, int row, int col)
{
    /* BASE CASES */
    if (row == x) // end of the grid, solution found
        return SUCCESS;
    if (col == y) // end of the row, move to next row down and reset column to 0
        return solve(rowArray, colArray, row + 1, 0);

    // try black first
    grid[row][col] = BLACK;
    if (valid(rowArray, colArray, row, col) == SUCCESS)
        if (SUCCESS == solve(rowArray, colArray, row, col + 1))
            return SUCCESS;
    
    // backtrack and try red instead
    grid[row][col] = RED;
    if (valid(rowArray, colArray, row, col) == SUCCESS)
        if (SUCCESS == solve(rowArray, colArray, row, col + 1))
            return SUCCESS;

    //Final backtracking step
    grid[row][col] = 0;
    return FAIL; 
}

int valid(INFO *rowArray, INFO *colArray, int row, int col)
{
    // check if the position is valid in terms of the row
    if (checkRow(rowArray, row, col) == FAIL)
        return FAIL;

    // check if the position is valid in terms of the row
    if (checkCol(colArray, row, col) == FAIL)
        return FAIL;

    // successful because we didn't violate any rules :)
    return SUCCESS;
}

/* Counting Functions */
// 1)   Create an instance of the tracker struct, and use that to store information about
//      the current row and column. 

// 2)   Loop through the entire row, and increment the groups whenever we encounter a new group of black flowers
//      fall into a nested while loop to count the amount of flowers within the group that we encounter, and stop when we hit the next red

//          - If we ever encounter a situation where the amount of groups, or the amount of flowers within a certain group exceeds the inputted
//            constraints, we immediately stop, because all future possibilities are now impossible, it would be a waste of time to keep going

// 3)   The amount of groups and amount of flowers within a group is allowed to be less than the constraints when the row or column is only
//      partially filled, but if the row or column is complete, it must be exactly equal to the input, otherwise parts of the row are invalid

int checkRow(INFO *rowArray, int row, int col)
{
    TRACKER trackR = {}; //initialize everything in the struct to 0

    // Count the amount of groups and amount of black flowers within each group in the passed row
    // Store the results in the row tracking struct
    for (i = 0; i <= col; i++)
    {
        //When we run into a black flower, that's a new group
        if (grid[row][i] == BLACK)
        {
            trackR.numGroups++;

            //as soon as the amount of groupings exceeds the input, return out immediately
            if (trackR.numGroups > rowArray[row].groups) return FAIL;

            //Goes through all the black flowers in the current group
            while (grid[row][i] == BLACK)
            {
                // use the group count - 1 as the index, so for the first group, that corresponds to index 0, group 2 goes to index 1, etc...
                trackR.subGroupSizes[trackR.numGroups - 1]++;
                i++; //keep traversing through the array, without this we will infinitely loop

                //as soon as the amount of groupings exceeds the input, return out immediately
                if (trackR.subGroupSizes[trackR.numGroups - 1] > rowArray[row].subG[trackR.numGroups - 1]) return FAIL;

                //stops out of bounds indices
                //indicates that the last flower in the row is black
                if (i == col) break;
            }
        }
    }

    //if we've reached the end of the row, we can only return success if the amount of groups
    //and subgroup counts are EXACTLY accurate
    if (col == y - 1)
        if (finalRowCheck(rowArray, trackR, row) == FAIL)
            return FAIL;

    return SUCCESS;
}

int checkCol(INFO *colArray, int row, int col)
{
    TRACKER trackC = {};

    //Count the amount of groups and amount of flowers within each subgroup
    //Store it in a tracker struct to compare with the input
    for (i = 0; i <= row; i++)
    {
        //when we run into a black flower, that's a new grouping
        if (grid[i][col] == BLACK)
        {
            trackC.numGroups++;

            //as soon as the amount of groupings exceeds the input, return out immediately
            if (trackC.numGroups > colArray[col].groups) return FAIL;

            //count all of the black flowers within the group
            while (grid[i][col] == BLACK)
            {
                //use the group count - 1 as the index, so group 1 represents index 0, group 2 is index 1, etc...
                trackC.subGroupSizes[trackC.numGroups - 1]++;
                i++; //we need to keep moving through the column, without this we will infinitely loop

                //as soon as the amount of black flowers in the group excepts the inputs, return out immediately
                if (trackC.subGroupSizes[trackC.numGroups - 1] > colArray[col].subG[trackC.numGroups - 1]) return FAIL;

                //stops out of bound indices
                //indicates that the last flower in the column is black
                if (i == row) break;
            }
        }
    }

    //if we're at the end of the column, we can only return success if the amount of groups
    //and subgroup counts are EXACTLY equal
    if (row == x - 1) 
        if (finalColCheck(colArray, trackC, col) == FAIL)
            return FAIL;

    return SUCCESS;
}

// The counted groups and subgroups for each of those groups must be EXACTLY equal to the input
int finalRowCheck(INFO * rowArray, TRACKER trackR, int row)
{
    // Checks if the counted groups and subgroups exactly matches the input
    if (trackR.numGroups != rowArray[row].groups)
        return FAIL;

    //checks if all the values in the subgroup array are exactly equal to the input
    for (i = 0; i < trackR.numGroups; i++)
        if (trackR.subGroupSizes[i] != rowArray[row].subG[i])
            return FAIL;

    //no rule violations :)
    return SUCCESS;
}

int finalColCheck(INFO * colArray, TRACKER trackC, int col)
{
    // Compare the counted column groups to the input
    if (trackC.numGroups != colArray[col].groups)
        return FAIL;

    // Compare the amount of black flowers found in each subgroup to the input
    for (i = 0; i < trackC.numGroups; i++)
        if (trackC.subGroupSizes[i] != colArray[col].subG[i])
            return FAIL;

    // no rule violations :)
    return SUCCESS;
}

void printFinalGrid()
{
    //Traverse through the 2d grid array
    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; j++)
        {
            // Since black flowers are represented by a 1, print B for visual reasons
            if (grid[i][j] == BLACK)
                printf("B");

            //Print red flowers represented by a 2 in the program
            else if (grid[i][j] == RED)
                printf("r");
        }
        printf("\n");
    }
}

//kaboom
void nukeTheGarden(INFO *rowArray, INFO *colArray)
{
    free(rowArray);
    free(colArray);
    for (i = 0; i < x; i++)
        free(grid[i]);
    free(grid);
}