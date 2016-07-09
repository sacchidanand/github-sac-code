#include<stdio.h>
#include<stdlib.h>

struct node
{
  int data;
  struct node *left;
  struct node *right;
};
typedef struct node node;
static int i=1;

node* getNewNode(int data)
{
  node *inputNode =(node*)malloc(sizeof(node));
  inputNode->data = data;
  inputNode->left = NULL;
  inputNode->right = NULL;

  printf("getNode=%d \n",inputNode->data);
  return inputNode;
}

void insert(node **root,int data)
{
  if(*root == NULL){
    *root = getNewNode(data);
  }
  else if(*root!=NULL){ 
    if((*root)->data >= data){
      insert(&((*root)->left),data);
    }
    else if((*root)->data < data){
      insert(&((*root)->right),data);
    }
  }
}

void recursivePrint(node **root)
{
  if(*root == NULL)
  {
    return;
  }

  recursivePrint(&((*root)->left));
  printf(" %d ,",(*root)->data);
  recursivePrint(&((*root)->right));
  return ;
}

int main()
{
  node *root=NULL;
  insert(&root,127);
  insert(&root,182);
  insert(&root,12);
  insert(&root,135);
  insert(&root,28);
  printf("\n\nRecursive Normal Print \n"); 
  recursivePrint(&root);
  printf("\n\n It works ! \n ");
  return 0;
}
