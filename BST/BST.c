/* 
This program is just a generic Binary Search Tree for the sake
of practice and further understanding. Written on 05/01/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// struct definition of a BST node
typedef struct Node
{
    int data;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

//Insertion function
Node *insert(Node *root, int data)
{
    //base case, we hit a null spot and we want to build a new node
    if (root == NULL)
    {
        Node *newNode = calloc(1, sizeof(Node));
        newNode->data = data;
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;

        return newNode;
    }

    /*
    In a binary search tree, we need to make sure that all values are sorted
    in ascending order from left to right. In other words, the left child
    should always be less than the parent, and the right child should be 
    greater than the parent

    ex)
                        5
                      /   \
                     1    10
    This is a valid tree, because 1 < 5 and 10 > 5
    */


    if (data < root->data) //we need to traverse left to insert on the left side of the BST
    {
        root->leftChild = insert(root->leftChild, data);
    }
    else if (data > root->data) //we need to traverse right to insert on the right side of the BST
    {
        root->rightChild = insert(root->rightChild, data);
    }

    return root;
}

/*
Due to the properties of a Binary Search Tree, the maximum value in the tree will always be the rightmost node
To traverse to the rightmost node, we use a while loop to keep moving right until we hit a null, then return
the value stored in that node to the caller
*/

int findMax(Node *root)
{
    Node *temp = root;
    while (temp->rightChild != NULL)
        temp = temp->rightChild;
    return temp->data;
}

/*
Due to the properties of a Binary Search Tree, the minimum value in the will will always be at the leftmost node
To traverse to the leftmost node, we use a while loop to continuously move left until we reach a null node, in
which case, we return the data held in that node to the caller
*/

int findMin(Node *root)
{
    Node *temp = root;
    while (temp->leftChild != NULL)
        temp = temp->leftChild;
    return temp->data;
}

/*
Very generic and basic search function. If the root is null, then we haven't been able to find the target in the
BST, and we need to return false to signify this to the caller. Our second base case signifies that we've found 
the value, and we should notify the caller that we found their target. Finally, using the properties of a 
Binary Search Tree, we can determine which direction we need to traverse to find our target by comparing it
with the current value held in the node. 
*/

bool isLocated(Node *root, int target)
{
    if (root == NULL)
        return false;

    if (root->data == target)
        return true;

    if (root->data < target)
        return isLocated(root->rightChild, target);
    return isLocated(root->leftChild, target);
}

/*
Post order traversal function. In post order traversal of a tree, we need to start at the leftmost node,
and traverse by hitting the children before reaching their parents. Post order traversal is generally used
to delete and free a tree from memory, because starting on the leaf nodes and working our way up allows us
to prevent hanging nodes
*/

void postPrint(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    postPrint(root->leftChild);
    postPrint(root->rightChild);
    printf("%d ", root->data);
}

/*
Pre order traversal function, recursion demonstrated with a simple print statement. In pre order traversal of a tree, 
we start at the root, and move to the leaves starting from the left. Pre order traversals are generally used to create
a copy of a BST, because it allowsus to start from the root, and add children as we go. 
*/

void prePrint(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->data);
    prePrint(root->leftChild);
    prePrint(root->rightChild);
}

/*
In order traversal function. This type of tree traversal is common for a BST in order to produce a sorted arrangement
of the nodes. Because all left children are less than their parents, we would start on the leftmost node to find the
minimum value, then traverse to its parent, then its right child, completed an in order traversal.
*/

void inPrint(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    inPrint(root->leftChild);
    printf("%d ", root->data);
    inPrint(root->rightChild);
}

int main()
{
    int val;
    bool located;

    //tree starts empty
    Node *root = NULL;

    //insert a bunch of numbers
    root = insert(root, 7);
    root = insert(root, 10);
    root = insert(root, 6);
    root = insert(root, 4);
    root = insert(root, 8);
    root = insert(root, 2);
    root = insert(root, 13);
    root = insert(root, 16);
    root = insert(root, 5);

    printf("\nTree in pre order: ");
    prePrint(root);
    printf("\nTree in order: ");
    inPrint(root);
    printf("\nTree in post order: ");
    postPrint(root);
    printf("\nMax value in BST: %d", findMax(root));
    printf("\nMin value in BST: %d", findMin(root));
    printf("\nEnter value to locate in BST: ");
    scanf("%d", &val);
    located = isLocated(root, val);
    if (located == true)
        printf("Found %d in the BST!", val);
    else
        printf("%d not found in the BST", val);
}