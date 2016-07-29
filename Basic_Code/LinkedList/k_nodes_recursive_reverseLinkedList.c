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

node* K_recursiveReverse(node *head, int k)
{
  node* current = head;
  node* next = NULL;
  node* prev = NULL;
  int count = 0;   

  /*reverse first k nodes of the linked list */
  while (current != NULL && count < k)
  {
    next  = current->next;
    current->next = prev;
    prev = current;
    current = next;
    count++;
  }

  /* next is now a pointer to (k+1)th node 
   * Recursively call for the list starting from current.
   * And make rest of the list as next of first node */
  if (next !=  NULL)
    head->next = K_recursiveReverse(next, k); 

  /* prev is new head of the input list */
  return prev;
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
  int k=3;
  node *head=NULL, *temp=NULL;  

  head = insert(head,1);
  head = insert(head,2);
  head = insert(head,3);
  head = insert(head,4);
  head = insert(head,5);
  head = insert(head,6);
  /*
     head = insert(head,12);
     head = insert(head,28);
     head = insert(head,127);
     head = insert(head,135);
     head = insert(head,182);
     */
  printf("\n--------------------------------------------------------");
  printf("\nIterative Print: "); 
  iterativePrint(head);
  printf("\n--------------------------------------------------------");

  temp= head;

  //K-recursive Reverse of Linked List
  printf("\n\n k_nodeRecursive Linked List Reverse !");
  head = K_recursiveReverse(head, k);

  printf("\n--------------------------------------------------------");
  printf("\nIterative Print: "); 
  iterativePrint(head);
  printf("\n--------------------------------------------------------\n");

  return 0;
}
