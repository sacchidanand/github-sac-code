#include<stdio.h>
#include<stdlib.h>

struct node
{
  int data;
  struct node *left;
  struct node *right;
};
typedef struct node node;

/*Depth : Number of edges in path from root to Node
Depth of Root : 0
*/
void depthOfTree(node *root, int *depth, int data, int *status)
{
  if(root == NULL)
  {
    return;
  }
  else
  {
    if(root->data == data)
    { 
      *status = 1;
    }
    else if(data <= root->data)
    {
      depthOfTree(root->left, depth, data, status); 
      if(*status)
        (*depth)++;
    }
    else
    {
      depthOfTree(root->right, depth, data, status);
      if(*status)
        (*depth)++;
    }
  }
  return ;
}

/* Height: Length of the Longest path from that Node to leaf*/ 
int heightOfTree(node *root)
{
  int hLeft=0,hRight=0;
  if(root == NULL)
  {
    return -1;
  }
  else
  {
    hRight = 1 + heightOfTree(root->left);
    hLeft  = 1 + heightOfTree(root->right);

    if(hLeft > hRight)
    {
      return hLeft;
    }
    else
    {
      return hRight;
    }
  }
}


node* getNewNode(int data)
{
  node *inputNode =(node*)malloc(sizeof(node));
  inputNode->data = data;
  inputNode->left = NULL;
  inputNode->right = NULL;
  //printf("%d\n",inputNode->data);
  return inputNode;
}

node* insert(node *root,int data)
{
  if(root == NULL){
    root = getNewNode(data);
  }
  else if(root!=NULL){ 
    if(root->data >= data){
      root->left = insert(root->left,data);
    }
    else if(root->data < data){
      root->right = insert(root->right,data);
    }
  }
  return root;
}

void recursivePrint(node *root)
{
  if(root == NULL)
  {
    return;
  }

  recursivePrint(root->left);
  printf("%d ",root->data);
  recursivePrint(root->right);
  return ;
}

int main()
{
  node *root=NULL;
  int d = 0, s=0;

  int *status = &s;
  int *depth = &d;


  root = insert(root,12);
  root = insert(root,28);
  root = insert(root,127);
  root = insert(root,135);
  root = insert(root,182);
  printf("\n\nRecursive Normal Print \n"); 
  recursivePrint(root);

  printf("\n\nHeight of Node=%d : %d", 135, heightOfTree(root->right->right->right));
  printf("\n\nHeight of Node=%d : %d", 28,  heightOfTree(root->right));

  depthOfTree(root, depth, 135, status);
  printf("\n\nDepth of Node=%d : %d, status = %d", 135, *depth, *status);
  *status = *depth = 0;

  depthOfTree(root, depth, 182, status);
  printf("\n\nDepth of Node=%d : %d, status = %d", 182, *depth, *status);
  *status = *depth = 0;
  
  printf("\n\n It works ! \n ");
  return 0;
}
