/*
Problem Statement: 
Using a Stack data structure, implement a system to keep track of the current
MVP of an arcade, determined by who has the highest amount of tokens. 
Create a menu system to add, remove, and display players

Written on 03/22/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Main node struct
typedef struct Person
{
  int token;
  char *name;
  struct Person *next;
} Person;

/* Function prototypes */

/* Stack Operations */
Person *createPerson(Person *head, int token, char *name);
Person *deletePerson(Person *head);
char *printMVP(Person *head);

/* Node Functions */
Person *nodeAlloc();
void freeList(Person *head);

/* Main Function */
int main()
{
  Person *head = NULL; //initialize head node to NULL, stack is empty
  int choice, value;
  char *name = malloc(21 * sizeof(char));

  while (1)
  {
    scanf("%d", &choice);
    switch (choice)
    {
    case 0: //free up remaining stack and terminate the program
      freeList(head);
      free(name);
      return 0;

    case 1: //scan in a number and a name to pass to createPerson function
      scanf("%d %s", &value, name);
      head = createPerson(head, value, name);
      break;

    case 2: //set the head to the node below it by deletePersonping the current head in deletePerson function
      head = deletePerson(head);
      break;

    case 3: //print out the current top node, should be the current mvp
      printf("%s\n", printMVP(head));
    }
  }
}

/* Node functions */
Person *nodeAlloc()
{
  return malloc(sizeof(Person)); //allocate memory for a new node and return to the createPerson function
}

void freeList(Person *head)
{
  //basically an iterative call to deletePerson to go through all the remaining
  //nodes in the stack at the end of the program to free all of it
  while (head != NULL)
  {
    head = deletePerson(head); //call deletePerson to clear heads and move down the stack until nothing is left
  }
}

/* Stack Operation Function Declarations */
Person *createPerson(Person *head, int token, char *name)
{
  if (head != NULL) //anything but the very first createPerson or an empty stack
  {
    int lastToken = head->token; //use this variable to compare to the passed token
    if (token > lastToken)       //new MVP :o
    {
      Person *tmp = nodeAlloc();             //build a new node
      tmp->name = malloc(21 * sizeof(char)); //allocate memory for the name in the temp node
      strcpy(tmp->name, name);               //copy over the passed string to the temp node
      tmp->token = token;                    //assign passed token value to temp node
      tmp->next = head;                      //make temp node link to the previous head
      return tmp;
    }
    //Create a "placeholder" node that will represent the existence of a player that is less valuable
    //than the MVP, but still allows us easy access to printMVP the MVP at any time
    else if (token < lastToken)
    {
      Person *tmp = nodeAlloc();             //build a new node
      tmp->name = malloc(21 * sizeof(char)); //allocate memory for the name in the "placeholder" node
      strcpy(tmp->name, head->name);         //copy the current MVPs name to the new "placeholder" node
      tmp->token = head->token;              //copy the current MVPs token count to the new "placeholder" node
      tmp->next = head;                      //make new "placeholder" node link to the previous head
      return tmp;
    }
  }
  else if (head == NULL) //for the first createPerson
  {
    Person *tmp = nodeAlloc();             //create a new node
    tmp->name = malloc(21 * sizeof(char)); //allocate space for the name in the new node
    strcpy(tmp->name, name);               //copy the passed name to the new node
    tmp->token = token;                    //copy the passed token value to the new node
    tmp->next = head;                      //link the new node to the head (in this case, the head is NULL)
    return tmp;
  }
}

Person *deletePerson(Person *head)
{
  if (head == NULL) //the stack doesn't have anything to pop
  {
    return head;
  }

  //actual pop operation
  Person *tmp = head->next; //store the node that will become the new head
  free(head->name);          //free the name of the node that's being popped
  free(head);                //free node being popped, pop successful :)
  return tmp;
}

char *printMVP(Person *head)
{
  if (head != NULL) //Every case, except for before our first createPerson, which should be impossible
  {
    return head->name; //return the name string from the head node
  }
  return NULL; //just in case ;)
}
