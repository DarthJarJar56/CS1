/*
Problem Statement:
Using a Binary Search Tree, create a program that will calculate the sum of all differences
between players skills in a tournament. For example, a match with player skills '5' and '1'
should produce a value of 4 to be added to the running total. 

Written on 04/04/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Main BSTNode struct
typedef struct BSTNode
{
    int data;
    long long int winner;
    struct BSTNode *leftChild;
    struct BSTNode *rightChild;
    long long int leftPlayer;  //store the skill of the left player
    long long int rightPlayer; //store the skill of the right player
} BSTNode;

//Global variables to avoid having to pass it around the functions
int nullCtr = 0;
long long int ex = 0;

/* Utility Function Prototypes */
int maxOf(int x, int y);
long long int findExcitement(int x, int y);
void destroyTree(BSTNode *root);

/* Main Function Prototypes for BST and tournament */
BSTNode *addToBST(BSTNode *root, int value);
void playTheGames(BSTNode *root, int *skills);

//Main function
int main(void)
{
    BSTNode *root = NULL; //set the tree to null to begin with
    int i, n;             //initialize variables

    //obtain user input for amount of players
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("%lld", ex);
        return 0;
    }

    //declare and allocate memory for the array of values to add to the BST and the skill values to use in the tournament
    int *playerSkills = calloc(n, sizeof(int));
    int addedValues[n - 1];

    //get tree values and player skills
    for (i = 0; i < n - 1; i++)
    {
        scanf("%d", &addedValues[i]);
    }
    for (i = 0; i < n; i++)
    {
        scanf("%d", &playerSkills[i]);
    }

    //add table values to the bst
    for (i = n - 2; i >= 0; i--)
    {
        root = addToBST(root, addedValues[i]);
    }

    //call the big Play Game function after adding everything to the BST
    playTheGames(root, playerSkills);

    //Because excitement is global, we can just print it without having to get a returned value from playTheGames function
    printf("%lld\n", ex);

    //destroy the tree and skill array
    destroyTree(root);
    free(playerSkills);

    return 0;
}

/*                               UTLITY FUNCTIONS                               */

//Function to find which of the players at a table has a higher skill value
//parameters must be passed in order
int maxOf(int x, int y)
{
    if (x > y)
    {
        return x;
    }
    if (x < y)
    {
        return y;
    }
    return x;
}

//Function to compute the difference between the max and the min value of the skills at a table
long long int findExcitement(int x, int y)
{
    long long int z;
    z = x - y;
    return z;
}

//function to free the entire tree
void destroyTree(BSTNode *root)
{
    if (root == NULL)
    {
        return;
    }
    destroyTree(root->leftChild);
    destroyTree(root->rightChild);
    free(root);
}

/*                               BST and TOURNAMENT FUNCTIONS                               */

//Function to add the table IDs in a binary search tree
//function based off of Santy's code in his BST add functions session
BSTNode *addToBST(BSTNode *root, int value)
{
    if (root == NULL) //base case
    {
        BSTNode *newNode = calloc(1, sizeof(BSTNode)); //allocate new node
        newNode->data = value;                         //set the new nodes data to the passed value
        newNode->leftChild = NULL;                     //show that the new node has no children yet
        newNode->rightChild = NULL;

        return newNode;
    }

    if (value < root->data) //must insert to the left of the current node if the new value is less than it
    {
        root->leftChild = addToBST(root->leftChild, value);
    }
    else if (value > root->data) //must insert to the right of the current node if the new value is less than it
    {
        root->rightChild = addToBST(root->rightChild, value);
    }

    return root;
}

//Main function to traverse the tree and play all of the games
void playTheGames(BSTNode *root, int *skills)
{
    long long int z = 0;
    if (root == NULL) //base case
    {
        return;
    }

    if (root->leftChild == NULL && root->rightChild == NULL) //node has no children
    {
        root->leftPlayer = skills[nullCtr++];  //pull left player from array
        root->rightPlayer = skills[nullCtr++]; //pull right player from array
    }
    else if (root->leftChild == NULL || root->rightChild == NULL) //one side of node is null, the other has another node
    {
        if (root->leftChild == NULL) //if the left one is null, we need to first set the left skill then recurse right
        {
            root->leftPlayer = skills[nullCtr++];   //pull from skill array to set left player
            playTheGames(root->rightChild, skills); //recurse to the right
            root->rightPlayer = root->rightChild->winner; //right player is the winner of the right childs game
        }
        else if (root->rightChild == NULL) //if the right is null, we need to recurse all the way left first before we add anything to the right
        {
            playTheGames(root->leftChild, skills);      //recurse left
            root->rightPlayer = skills[nullCtr++];      //when we get back here, add right plsyer from the array
            root->leftPlayer = root->leftChild->winner; //left player is the winner of the left childs game
        }
    }
    else if (root->leftChild != NULL && root->rightChild != NULL) //the node has 2 children that are real nodes, recurse to the left then the right
    {
        playTheGames(root->leftChild, skills);        //recurse left
        playTheGames(root->rightChild, skills);       //recurse right
        root->leftPlayer = root->leftChild->winner;   //left player is the winner of the left childs game
        root->rightPlayer = root->rightChild->winner; //right player is the winner of the right childs game
    }

    //Play out the games and set new winner values
    //winner of the current table is whichever skill value is highest
    root->winner = maxOf(root->rightPlayer, root->leftPlayer);

    if (root->leftPlayer > root->rightPlayer) //if the left skill was higher, |left - right|
    {
        z = findExcitement(root->leftPlayer, root->rightPlayer);
    }
    else if (root->leftPlayer < root->rightPlayer)
    {
        z = findExcitement(root->rightPlayer, root->leftPlayer); //if the right skill was higher, |right - left|
    }
    ex = ex + z; //add excitement of the match to the total excitement value
}