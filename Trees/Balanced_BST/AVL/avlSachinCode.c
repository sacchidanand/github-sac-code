#include<stdio.h>
#include<stdlib.h>

struct node{
  int data;
  int ht;
  struct node *left;
  struct node *right;
};
typedef struct node node;

node* insert(node *x, int data);
node* delete(node *x, int data);
void preOrder(node *root);
void inOrder(node *root);
node* leftRotate(node *x);
node* rightRotate(node *y);
node* LL(node*x);
node* RR(node*x);
node* RL(node*x);
node* LR(node*x);
int height(node *x);
int BF(node *x);
node* findMin(node *p);
node* findMax(node *p);
node* getPredecessor(node * root, int data);
node* getSuccessor(node * root, int data);
node* find(node* root, int data);

int main()
{
  node *root=NULL, *ans=NULL;
  int x,n,i,op;
  do
  {
    printf("\n1)Create:");
    printf("\n2)Insert:");
    printf("\n3)Delete:");
    printf("\n4)Print:");
    printf("\n5)Successor:");
    printf("\n6)Predecessor:");
    printf("\n7)Quit:");
    printf("\n\nEnter Your Choice:");
    scanf("%d",&op);
    switch(op)
    {
      case 1:  printf("\nEnter no. of elements:");
               scanf("%d",&n);
               printf("\nEnter tree data:");
               root=NULL;
               for(i=0;i<n;i++)
               {
                 scanf("%d",&x);
                 root=insert(root,x);
               }
               break;
      case 2:  printf("\nEnter a data:");
               scanf("%d",&x);
               root=insert(root,x);
               break;
      case 3:  printf("\nEnter a data:");
               scanf("%d",&x);
               root=delete(root,x);
               break;
      case 4:  printf("\nPreorder sequence:\n");
               preOrder(root);
               printf("\n\nInorder sequence:\n");
               inOrder(root);
               printf("\n");
               break;
      case 5:  printf("\nSuccessor Search\nEnter a data:");
               scanf("%d",&x);
               ans = getSuccessor(root,x);
               if(ans != NULL)
                 printf("\nSuccessor(%d) : %d\n",x,ans->data);
               else
                 printf("Successor does not exist");    
               break;
      case 6:  printf("\nPredecessor Search\nEnter a data:");
               scanf("%d",&x);
               ans = getPredecessor(root,x);
               if(ans != NULL)
                 printf("\nPredecessor(%d) : %d\n",x,ans->data);
               else
                 printf("Predecessor does not exist");    
               break;
    }
  }while(op!=7);
  return 0;
}

node* getNewNode(int data)
{
  node *p;
  p = (node *)malloc(sizeof(node));
  p->data = data;
  p->left = NULL;
  p->right = NULL;
  return p;
}

node * insert(node *x, int data)
{
  if(x == NULL)
    x = getNewNode(data);
  else if(data < x->data)
  {
    x->left = insert(x->left, data);
    if(BF(x) == 2)
      if(x->left->data > data)
        x = LL(x);
      else
        x = LR(x);
  }
  else if(data > x->data)
  {
    x->right = insert(x->right, data);
    if(BF(x) == -2)
      if(x->right->data < data)
        x = RR(x);
      else
        x = RL(x);
  }

  x->ht = height(x);
  return x;
}

node* delete(node* x, int data)
{
  node* temp =NULL;
  if(x==NULL)
    return NULL;
  else if(data < x->data)
  {
    x->left = delete(x->left, data);
    if(BF(x)==-2)
      if(BF(x->right)<=0)
        x=RR(x);
      else
        x=RL(x);
  }
  else if(x->data < data) // right
  {
    x->right = delete(x->right, data);
    if(BF(x)==2)
      if(BF(x->left)>=0)
        x=LL(x);
      else
        x=LR(x);
  }
  else if(x->data == data)
  { 
    //case-1 : no child
    if((x->left == NULL) && (x->right == NULL))
    {  
      temp = x;
      x = NULL;
      free(temp);
    }
    //case-2 : one child
    else if(x->left == NULL)
    {
      temp = x;
      x = x->right;
      free(temp); 
    }
    else if(x->right == NULL)
    {
      temp = x;
      x = x->left;
      free(temp);
    }
    //case-3 : both child
    else if(x->right != NULL && x->left != NULL)
    {
      temp = findMin(x->right);
      x->data = temp->data;
      x->right = delete(x->right, temp->data);

      //check BF
      if(BF(x)==2)
        if(BF(x->left)>=0)
          x = LL(x);
        else
          x = LR(x);
    }
  }
  if(x!=NULL)  
    x->ht = height(x);
  return x;
}



int height(node *x)
{
  int hl, hr;

  if(x == NULL)
    return 0;

  if(x->left == NULL)
    hl = 0;
  else
    hl = 1 + x->left->ht;

  if(x->right == NULL)
    hr = 0;
  else
    hr = 1 + x->right->ht;

  if(hl>hr)
    return hl;

  return hr;
}

int BF(node *x)
{
  int hl, hr;

  if(x == NULL)
    return 0;

  if(x->left == NULL)
    hl = 0;
  else
    hl = 1 + x->left->ht;

  if(x->right == NULL)
    hr = 0;
  else
    hr = 1 + x->right->ht;

  return (hl-hr);
}

node* rightRotate(node *y){
  node *x;
  x= y->left;
  y->left = x->right;
  x->right = y;

  x->ht=height(x);
  y->ht=height(y);
  return x;
}

node* leftRotate(node *x){
  node *y;
  y = x->right;
  x->right=y->left;
  y->left=x;

  x->ht=height(x);
  y->ht=height(y);
  return y;
}


node* LL(node*x){
  x = rightRotate(x);
  return x;
}

node* RR(node*x){
  x = leftRotate(x);
  return x;
}

node* LR(node *x){
  x->left = leftRotate(x->left);
  x = rightRotate(x);
  return x;
}

node* RL(node *x){
  x->right = rightRotate(x->right);
  x = leftRotate(x);
  return x;
}

void inOrder(node *root)
{
  if(root != NULL)
  {
    inOrder(root->left);
    printf(" %d:BF(%d):ht(%d), ",root->data, BF(root),root->ht);
    inOrder(root->right);
  }
}

void preOrder(node *root)
{
  if(root!=NULL)
  {
    printf(" %d:BF(%d):ht(%d), ",root->data, BF(root),root->ht);
    preOrder(root->left);
    preOrder(root->right);
  }
}

node* find(node* root, int data)
{
  if(root == NULL)
    return NULL;

  node* p = root;
  while(p != NULL)
  {
    if(data < p->data)
      p = p->left;
    else if(data > p->data)
      p = p->right;
    else if(data == p->data)
      return p;
    else
    {
      printf("\n Error : Data not found in tree \n");
      return NULL;
    }
  }
}

node* findMin(node *p)
{
  if(p==NULL)
    return NULL;

  while(p->left != NULL)
    p = p->left;

  return p;  
}

node* findMax(node *p)
{
  if(p==NULL)
    return NULL;

  while(p->right != NULL)
    p = p->right;

  return p;  
}

node* getSuccessor(node * root, int data)
{
  node *current = find(root, data);
  node *ancestor = NULL, *successor = NULL;
  if(current == NULL)
    return NULL;

  if(current->right !=NULL)
    return findMin(current->right);
  else
  {
    ancestor = root;
    successor = NULL;

    while(ancestor != current)
    {
      if(data < ancestor->data){
        successor = ancestor;
        ancestor = ancestor->left;
      }
      else
        ancestor = ancestor->right;
    }
  }
  return successor;
}

node* getPredecessor(node * root, int data)
{
  node *current = find(root, data), *ancestor = NULL, *predecessor = NULL;
  if(current == NULL)
    return NULL;

  if(current->left !=NULL)
    return findMax(current->left);
  else
  {
    ancestor = root;
    predecessor = NULL;

    while(ancestor != current)
    {
      if(data > ancestor->data){
        predecessor = ancestor;
        ancestor = ancestor->right;
      }
      else
        ancestor = ancestor->left;
    }
  }
  return predecessor;
}
