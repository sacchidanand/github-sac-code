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

node* K_iterativeReverse(node *head, int k)
{
  int i=0, headFlag = 0;
  node *curr = NULL, *prev=NULL, *succ = NULL;
  node *scurr = NULL, *sprev=NULL;

  curr = head;
  if(curr == NULL)
    return head;
  prev = NULL;
  succ = curr->next;
  sprev = prev; 

  while(curr!=NULL)
  {
    i=0;
    scurr= curr;

    while((curr!=NULL) && (i<k))
    {
      i++;
      //printf("\nCurr = %d, i=%d, k=%d",curr->data,i,k);

      curr->next = prev;
      prev = curr;
      curr = succ;
      if(curr != NULL)
        succ = curr->next;
    }//while-inner-end

    //printf("\ni=%d, k=%d",i,k);
    if(headFlag == 0)
    {
      head = prev;
      headFlag=1;
    }
    else
    {
      if(sprev!=NULL)
        sprev->next = prev;
    }

    scurr->next = curr;
    prev = sprev = scurr;

    if(curr == NULL)
      break;

  }//while-outer-end

  return head;
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
  int k=4;
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

  //K-Iterative Reverse of Linked List
  printf("\n\n Iterative Linked List Reverse !");
  printf("\n Calling iterativeReverse()\n");
  head = K_iterativeReverse(head, k);

  printf("\n--------------------------------------------------------");
  printf("\nIterative Print: "); 
  iterativePrint(head);
  printf("\n--------------------------------------------------------\n");

  return 0;
}
