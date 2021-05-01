/* 
This is a generic program implementing a queue data structure.
A queue data structure is a variation of a linked list that
inserts value at the back of the list, and removes from the front
using a FIFO setup.
*/

#include <stdio.h>
#include <stdlib.h>

/* Struct for our Nodes throughout the Queue */
typedef struct Node
{
    int data;
    struct Node * next;
}Node;

/* Struct to store the head and tail pointers */
typedef struct queue {
    Node * head;
    Node * tail;
}queue;

/* Helper function to initialize the queue to 0 at the start */
queue * buildQueue()
{
    queue * q = calloc(1, sizeof(Node));
    q->head = NULL, q->tail = NULL;
    return q;
}

/* Helper function to allocate and create a new node when enqueueing */
Node * buildNode(int val)
{
    Node * temp = calloc(1, sizeof(Node));
    temp->data = val;
    temp->next = NULL;
    return temp;
}

/*
Enqueue function. In a queue data structure, you need to insert values at the
back of the queue. In order to do this, we create a temp node using the passed
value, then use that temp node to add to the queue. If the queue is empty, 
we simply set both the tail and the head to the new temp node. Otherwise,
we set the next pointer in the current tail to point to the new node instead
then set the new node as the new tail
*/

void enQ(queue * myQueue, int val)
{
    Node * temp = buildNode(val);
    if (myQueue->tail == NULL)
    {
        myQueue->head = temp;
        myQueue->tail = temp;
        return;
    }
    myQueue->tail->next = temp;
    myQueue->tail = temp;
}

/* 
Dequeue function. In a queue data structure, we remove values from the front of the list
using a FIFO setup. To accomplish this, we create a temp node that stores the current head
then set the current head to the next spot in the list, and free the temp to clear it from
the memory.
*/

void deQ(queue * myQueue)
{
    if (myQueue->head == NULL)
    {
        return;
    }
    Node * temp = myQueue->head;
    myQueue->head = myQueue->head->next;
    if(myQueue->head == NULL)
        myQueue->tail = NULL;
    
    free(temp);
}

/* 
Simple helper function print the queue
*/

void printQueue(queue * myQueue)
{
    if (myQueue->head == NULL)
    {
        printf("Queue is empty\n");
        return;
    }
    else
    {
        Node * temp = myQueue->head;
        while (temp->next != NULL)
        {
            printf("%d <- ", temp->data);
            temp = temp->next;
        }
        printf("%d <- NULL\n", temp->data);
    }
}

/* Driver main to demonstrate the functions of a Queue */
int main()
{
    queue * myQueue = buildQueue();
    enQ(myQueue, 9);
    /* 9 <- NULL */
    enQ(myQueue, 6);
    /* 9 <- 6 <- NULL */
    enQ(myQueue, 7);
    /* 9 <- 6 <- 7 <- NULL */
    enQ(myQueue, 8);
    /* 9 <- 6 <- 7 <- 8 <- NULL */
    enQ(myQueue, 4);
    /* 9 <- 6 <- 7 <- 8 <- 4 <- NULL */
    enQ(myQueue, 2);
    /* 9 <- 6 <- 7 <- 8 <- 4 <- 2 <- NULL */
    enQ(myQueue, 10);
    /* 9 <- 6 <- 7 <- 8 <- 4 <- 2 <- 10 <- NULL */
    printQueue(myQueue);

    deQ(myQueue);
    /* 6 <- 7 <- 8 <- 4 <- 2 <- 10 <- NULL */
    deQ(myQueue);
    /* 7 <- 8 <- 4 <- 2 <- 10 <- NULL */
    deQ(myQueue);
    /* 8 <- 4 <- 2 <- 10 <- NULL */
    deQ(myQueue);
    /* 4 <- 2 <- 10 <- NULL */
    deQ(myQueue);
    /* 2 <- 10 <- NULL */
    deQ(myQueue);
    /* 10 <- NULL */
    deQ(myQueue);
    /* EMPTY */
    printQueue(myQueue);
    
}