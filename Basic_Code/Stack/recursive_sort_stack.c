/*   
 *   sort stack recursive()
 */
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

void push(node **top, int data)
{
  node *temp;
  node *newNode = getNewNode(data);

  if(*top!=NULL)
  { 
    newNode->next = *top;
  }

  *top = newNode;
}

int pop(node **top)
{
  int ret = -100;

  if(*top!=NULL)
  {
    ret = (*top)->data;
    node *remove = *top;
    *top = (*top)->next;
    free(remove);
  }

  return ret;
}

int isEmpty(node *top)
{
  if (top == NULL)
    return 1;
  return 0;
}

void sortInsert(node **top, int val)
{
  int t = 0;
  if(isEmpty(*top) || (val<(*top)->data))
  {
    push(top, val);
  }
  else
  {
    t = pop(top);
    sortInsert(top, val);

    push(top, t);
  }
}

void sortStack(node **top)
{
  node *temp = NULL;
  int k = 0 ;

  if(1 != isEmpty(*top))
  {
    k = pop(top);
    sortStack(top);
    sortInsert(top, k);
  }
}

node* iterativeReverse(node *top)
{
  node *curr = NULL, *prev=NULL, *succ = NULL;

  curr = top;
  if(curr ==NULL)
    return top;
  prev = NULL;
  succ = curr->next;


  while(curr->next!=NULL)
  {
    curr->next = prev;
    prev = curr;
    curr = succ;
    succ = succ->next;
  }
  curr->next = prev;

  top = curr;

  return top;
}


void iterativePrint(node *top)
{
  node *temp = top;
  while(temp!=NULL)
  {
    printf("%d->",temp->data);
    temp=temp->next;
  }
  printf("NULL");
}

int main()
{
  node *top=NULL;

  push(&top,28);
  push(&top,12);
  push(&top,182);
  push(&top,127);
  push(&top,135);
  /*
  push(&top,12);
  push(&top,28);
  push(&top,127);
  push(&top,135);
  push(&top,182);
  */
  printf("\n--------------------------------------------------------");
  printf("\nIterative Print: "); 
  iterativePrint(top);
  printf("\n--------------------------------------------------------");

  //Recursive sort stack
  printf("\n sort stack recursive()\n");
  sortStack(&top);

  printf("\n--------------------------------------------------------");
  printf("\nIterative Print: "); 
  iterativePrint(top);
  printf("\n--------------------------------------------------------\n");

  return 0;
}
