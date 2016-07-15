/*
 * AVL Tree Implementation in c
 * 
 * References:
 * https://en.wikipedia.org/wiki/AVL_tree
 *
 * MIT DSA 6006
 * https://www.youtube.com/watch?v=FNeL18KsWPc
 * 
 * Author : Sacchidanand Bhavari
 * Email : sacchidanand.b@gmail.com 
 */

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

/* main function : AVL Tree */
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

/* Create a new Node */
node* getNewNode(int data)
{
  node *p;
  p = (node *)malloc(sizeof(node));
  p->data = data;
  p->left = NULL;
  p->right = NULL;
  return p;
}

/* Insert a new node in AVL Tree */
node* insert(node *x, int data)
{

  if(x == NULL){
    x = getNewNode(data);
  }
  else if(data < x->data)
  { 
    // insert new node into left subtree
    x->left = insert(x->left, data);
    
    // Check for Balance factor after inserting new node into left subtree
    if(BF(x) == 2)
    {  
      // Doubly left heavy node 
      // LL:Left-Left formation
      if(x->left->data > data){
        x = LL(x);
      }
      //LR:Left-Right Heavy formation
      else{
        x = LR(x);
      }
    }
  }
  else if(data > x->data)
  {
    x->right = insert(x->right, data);

    if(BF(x) == -2) 
    {
      if(x->right->data < data)
        x = RR(x);
      else
        x = RL(x);
    }
  }

  /* Update the height of all the node x,
   * which comes in path from Root->Newly added node inclusing root itself */
  x->ht = height(x);
  return x;
}

/* Delete a node from AVL Tree */
node* delete(node* x, int data)
{
  node* temp =NULL;

  if(x==NULL)
    return NULL;
  else if(data < x->data)
  {
    x->left = delete(x->left, data);
    
    //check Balance Factor after deleting left subtree node
    if(BF(x)==-2)
    {
      if(BF(x->right)<=0)
        x=RR(x);
      else
        x=RL(x);
    }
  }
  else if(x->data < data) // right
  {
    x->right = delete(x->right, data);

    if(BF(x)==2)
    {
      if(BF(x->left)>=0)
        x=LL(x);
      else
        x=LR(x);
    }
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
      {
        if(BF(x->left)>=0)
          x = LL(x);
        else
          x = LR(x);
      }
    }
  }
  if(x!=NULL)  
    x->ht = height(x);
  return x;
}

/* height of a node*/
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

/* balance_factor of a node */
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

/* Right-Rotate Operation for AVL Tree*/
node* rightRotate(node *y){
  node *x;
  x= y->left;
  y->left = x->right;
  x->right = y;

  //Update the height of Node x & y
  x->ht=height(x);
  y->ht=height(y);
  return x;
}


/* Left-Rotate Operation for AVL Tree*/
node* leftRotate(node *x){
  node *y;
  y = x->right;
  x->right=y->left;
  y->left=x;

  //Update the height of Node x & y
  x->ht=height(x);
  y->ht=height(y);
  return y;
}

/* Left-Left Heavy Rotation */
node* LL(node*x){
  x = rightRotate(x);
  return x;
}

/* Right-Right Heavy Rotation */
node* RR(node*x){
  x = leftRotate(x);
  return x;
}

/* Left-Right Heavy Rotation */
node* LR(node *x){
  x->left = leftRotate(x->left);
  x = rightRotate(x);
  return x;
}

/* Right-Left Heavy Rotation */
node* RL(node *x){
  x->right = rightRotate(x->right);
  x = leftRotate(x);
  return x;
}

/* L-D-R Print Tree data in In-Order Traversal */
void inOrder(node *root)
{
  if(root != NULL)
  {
    inOrder(root->left);
    printf(" %d:BF(%d):ht(%d), ",root->data, BF(root),root->ht);
    inOrder(root->right);
  }
}

/* D-L-R : Print Tree data in Pre-Order Traversal */
void preOrder(node *root)
{
  if(root!=NULL)
  {
    printf(" %d:BF(%d):ht(%d), ",root->data, BF(root),root->ht);
    preOrder(root->left);
    preOrder(root->right);
  }
}

/* Find node pointer */
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
  }//while-end
}

/* Find node containing MIN value is subtree rooted at p */
node* findMin(node *p)
{
  if(p==NULL)
    return NULL;

  while(p->left != NULL)
    p = p->left;

  return p;  
}

/* Find node containing MAX value is subtree rooted at p */
node* findMax(node *p)
{
  if(p==NULL)
    return NULL;

  while(p->right != NULL)
    p = p->right;

  return p;  
}

/* Get successor for node containing data */
node* getSuccessor(node * root, int data)
{
  // Store the current with pointer for node containing data
  node *current = find(root, data);

  node *ancestor = NULL, *successor = NULL;

  if(current == NULL)
    return NULL;

  if(current->right != NULL){
    return findMin(current->right);
  }
  else
  {
    ancestor = root;
    successor = NULL;

    while(ancestor != current)
    {
      if(data < ancestor->data)
      {
        successor = ancestor;
        ancestor = ancestor->left;
      }
      else{
        ancestor = ancestor->right;
      }
    }//while-end

  }//else-end

  return successor;
}

/* Get pre-decessor for node containing data */
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
