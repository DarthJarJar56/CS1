/*
Generic Doubly Linked List program created in order to practice
and further my understanding. 

A Doubly Linked List is a variation of the traditional Linked List that
allows us to store a pointer for the previous node alongside the next pointer.
This means that we can access both the previous and next nodes at any given node.

One real world application for a doubly linked list is a Music Playlist
(without looping, that would be a circular doubly list). Essentially, the idea
of being able to move forward and backward throughout the playlist is the core
of a Doubly Linked List. 

The goal of a Doubly Linked List is to insert and delete nodes in O(1) time.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node * next, * prev;
}Node;

typedef struct List {
    struct Node * head, * tail;
}List;


/* Helper functions to create nodes, nitialize the List, and display the List */
Node * buildNode(int val)
{
    Node * new = calloc(1, sizeof(Node));
    new->data = val;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

List * createList()
{
    List * list = calloc(1, sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void printList(List * LL, Node * head)
{
    Node * temp = LL->head;
    printf("NULL <--> ");

    while (temp != NULL)
    {
        printf("%d <--> ", temp->data);
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("NULL\n");
    }
}

/* LIST FUNCTIONS */

/*
Insert at the front of the Doubly Linked List. To do this
1) Create a new node given the passed value
2) If the current head is null, the new node is now the head
   and first element in the list, meaning its next and prev
   are both NULL
3) Set the new node's next to point to the current head
4) Set the new node's prev to point to NULL (it's the first element now)
5) Set the new node as the new head and return the head
*/
void insertAtFront (List * list, int val)
{
    Node * temp = buildNode(val);
    if (list->head == NULL && list->tail == NULL)
    {
        list->head = temp;
        list->tail = temp;
        return;
    }
    temp->next = list->head;
    list->head->prev = temp;
    list->head = temp;
}

/*
Insert at the end of the Doubly Linked List. TO do this
1) Create  anew node given the passed value
2) if the list is empty, the new node is both the head and the tail
   of the list
3) set the new node's prev pointer to point to the current tail
4) set the current tail's next pointer to point to the new node
5) set the new node as the new tail of the list
*/
void insertAtEnd(List * list, int val)
{
    Node * temp = buildNode(val);
    if (list->head == NULL && list->tail == NULL)
    {
        list->head = temp;
        list->tail = temp;
        return;
    }

    temp->prev = list->tail;
    list->tail->next = temp;
    list->tail = temp;
}

/*
Delete from the end of the list. To do this:
1) Create a temp node to store the current tail
2) set the node previous to the current tail to point to null
3) set the node previous to the current tail as the new tail
4) free the temp
*/
void deleteEnd(List * list)
{
    if (list->tail == NULL)
        return;
    
    Node * temp = list->tail;
    list->tail->prev->next = NULL;
    list->tail = list->tail->prev;
    free(temp);
}

/*
Delete from the front of the list. To do this:
1) Create a temp to store the current head
2) set the prev of the node after the head to point to NULL
3) set the node after the current head to be the new head
4) free the temp
*/
void deleteFront(List * list)
{
    if(list->head == NULL)
        return;
    
    Node * temp = list->head;
    list->head->next->prev = NULL;
    list->head = list->head->next;
    free(temp);
}


/*
Simple free function that starts from the head of the list
and traverses, freeing as we go, to destroy the whole list
*/
void freeList(List * list)
{
    Node * temp;
    while (list->head != NULL)
    {
        temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
    free(list);
    printf("List empty :)\n");
}

/* Driver main to demonstrate all the functions */
int main()
{
    Node * head = NULL;
    List * myDoubleLL = createList();

    /* Let's insert a couple values from the end of the list */
    insertAtEnd(myDoubleLL, 2);
    insertAtEnd(myDoubleLL, 4);
    insertAtEnd(myDoubleLL, 5);
    /* NULL <--> 2 <--> 4 <--> 5 <--> NULL */
    printList(myDoubleLL, head);

    /* Now, let's insert a couple values from the start of the list */
    insertAtFront(myDoubleLL, 10);
    insertAtFront(myDoubleLL, 14);
    insertAtFront(myDoubleLL, 12);
    /*NULL <--> 12 <--> 14 <--> 10 <--> 2 <--> 4 <--> 5 <--> NULL */
    printList(myDoubleLL, head);

    /* Now let's perform some deletions from the front and back */
    deleteEnd(myDoubleLL);
    /* NULL <--> 12 <--> 14 <--> 10 <--> 2 <--> 4 <--> NULL */
    printList(myDoubleLL, head);

    deleteFront(myDoubleLL);
    /* NULL <--> 14 <--> 10 <--> 2 <--> 4 <--> NULL */
    printList(myDoubleLL, head);

    freeList(myDoubleLL);
    return 0;
}