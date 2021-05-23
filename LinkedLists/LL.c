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

Node * insert (Node * head, int val)
{
    Node * temp = buildNode(val);
    temp->data = val;
    temp->next = head;
    head = temp;
    printf("Added %d to the list!\n", temp->data);
    return temp;
}

void printList(Node * head)
{
    Node * temp = head;
    while (temp != NULL)
    {
        printf("%d ---> ", temp->data);
        temp = temp->next;
    }
}
int main()
{
    Node * head = NULL;
    head = insert(head, 9);
    head = insert(head, 8);
    head = insert(head, 7);
    head = insert(head, 6);
    head = insert(head, 5);
    head = insert(head, 4);
    head = insert(head, 3);

    printList(head);

}