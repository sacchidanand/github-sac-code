#include<stdio.h>
#include<stdlib.h>

struct node
{
  int data;
  struct node *next;
};
typedef struct node node;

node* getNewNode(int data)
{
  node *inputNode =(node*)malloc(sizeof(node));
  inputNode->data = data;
  inputNode->next = NULL;
  return inputNode;
}

node* insert(node *head, int data)
{
  node *temp;
  node *newNode = getNewNode(data);
  if(head == NULL)
  {
    head = newNode;
  }
  else if(head!=NULL)
  { 
    temp=head;
    while(temp->next!=NULL)
      temp=temp->next;

    temp->next = newNode;
  }

  return head;
}

void recursivePrint(node *head)
{
  if(head == NULL)
  {
    return;
  }

  recursivePrint(head->next);
  printf("%d ",head->data);
  return ;
}
  
node* reverseRecursive(node **head, node *curr)
{
  node *temp=NULL;
  if((curr!=NULL) && (curr->next==NULL))
  {
    *head = curr;
  }
  else if((curr!=NULL) && (curr->next!=NULL))
  {
    reverseRecursive(head, curr->next);
    temp = curr->next;
    temp->next = curr;
  }

  return;
}

void iterativePrint(node *head)
{
  node *temp = head;
  while(temp!=NULL)
  {
    printf("%d->",temp->data);
    temp=temp->next;
  }
  printf("NULL");
}

int main()
{

  node *head=NULL, *temp=NULL;

  head = insert(head,12);
  head = insert(head,28);
  head = insert(head,127);
  head = insert(head,135);
  head = insert(head,182);

  printf("\n--------------------------------------------------------");
  printf("\nIterative Print: "); 
  iterativePrint(head);
  printf("\n--------------------------------------------------------");

  //recursivePrint(head);

  temp= head;
  //Recursive Reverse of Linked List
  printf("\n\n Linked List Reverse using Recursion !");
  printf("\n Calling reverseRecursive()\n");
  reverseRecursive(&head, temp);
  temp->next = NULL;

  printf("\n--------------------------------------------------------");
  printf("\nIterative Print: "); 
  iterativePrint(head);
  printf("\n--------------------------------------------------------\n");

  return 0;
}
