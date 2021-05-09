/*
Generic Stack Data Structure program created for the sake
of practice and furthering my understanding

A stack is a way of storing data in a LIFO (Last in, First out) fashion
Meaning, the last value that puts put onto the stock is the first thing
to get removed. One example of a practical use of a stack is when you're
using web browser, the back button essentially pops the current website you're
on, very similar to the function of a stack, where the most recent site is on
top, and is the first to get popped off

The following program is the Linked List implementation of a stack. An Array
Implementation is also possible. 

The goal of a stack is to be able to access the top element, at any time, in O(1)
time. Pushing and Popping should both be O(1) operations, seeing as we don't have
to traverse the entire stack to find the spot where we need to insert, as we would
with a Queue data structure

Written on 05/09/2021
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node * next;
}Node;

Node * buildNode(int val)
{
    Node * new = calloc(1, sizeof(Node));
    new->data = val;
    new->next = NULL;
    return new;
}

/*
Push a value to the top of the stack. To do this, we need to
1) Create a new node with the passed value
2) Link the new node to the current head
3) Set the new node as the new top of the stack
*/

Node * push(Node * top, int val)
{
    if (top == NULL)
    {
        Node * temp = buildNode(val);
        top = temp;
        return top;
    }
    Node * temp = buildNode(val);
    temp->next = top;
    return temp;
}

/*
Pop the top value of the stack and delete it from memory. To do this:
1) create a temp node to store the current top node
2) set top->next as the new top of the stack
3) free the temp node
*/
Node * pop(Node * top)
{
    if (top == NULL)
    {
        return top; // nothing to pop
    }
    Node * temp = top;
    top = top->next;
    free(temp);
    return top;
}

/*
Peek at the top of the stack, just return the value that's contained
in the top node of the stack, very simple function
*/
int peek (Node * top)
{
    if (top != NULL)
        return top->data;
}

/*
Helper function to print the stack for visualization
*/
void printStack(Node * top)
{    
    printf("(TOP) ");
    Node * temp = top;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("NULL (BOTTOM)\n");
    }
}

/*
Helper function to free the entire stack at the end of the program
We can continuously call the pop function, which moves the top down
and frees the previous top, as a way to free our entire stack
*/
void freeStack(Node * top)
{
    while (top != NULL)
    {
        top = pop(top);
    }
    printf("Stack empty :)\n");
}

/* Driver Main to demonstrate the functions of the stack */
int main()
{
    Node * top = NULL;

    /* Push some values to the stack */
    printf("STARTING STACK\n");
    top = push(top, 1);
    top = push(top, 6);
    top = push(top, 2);
    top = push(top, 3);
    top = push(top, 4);
    top = push(top, 7);
    top = push(top, 8);
    printStack(top); //Display the current stack

    /* Demonstrating Pop Function */
    printf("\nPOPPING 4 VALUES....\n");
    top = pop(top);
    printStack(top);
    top = pop(top);
    printStack(top);
    top = pop(top);
    printStack(top);
    top = pop(top);
    printStack(top);

    /* Let's push a few more values */
    printf("\nPushing: 58, 13, 12, 38, 53\n");
    top = push(top, 58);
    printStack(top);
    top = push(top, 13);
    printStack(top);
    top = push(top, 12);
    printStack(top);
    top = push(top, 38);
    printStack(top);
    top = push(top, 53);
    printStack(top);

    printf("\nPeeking at current top...\n");
    printStack(top);
    printf("Value at top: %d\n", peek(top));
    printf("Popping...\n");
    top = pop(top);
    printStack(top);
    printf("Value at top: %d\n", peek(top));

    /* Make sure to free the memory before exiting the program to prevent memory leaks */
    freeStack(top);
}