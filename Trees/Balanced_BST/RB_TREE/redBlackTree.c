/*
 * Red-Black Tree Implementation in c
 * 
 * References:
 * https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
 * https://www.youtube.com/watch?v=CTvfzU_uNKE
 * 
 * Author : Sacchidanand Bhavari
 * Email : sacchidanand.b@gmail.com 
 *
 * In addition to the requirements imposed on a binary search tree the following must be satisfied by a red–black tree:
 *
 * 1. A node is either red or black.
 * 2. The root is black. This rule is sometimes omitted. 
 *    Since the root can always be changed from red to black, but not necessarily vice versa, 
 *    this rule has little effect on analysis.
 * 3. All leaves (NIL) are black.
 * 4. If a node is red, then both its children are black.
 * 5. Every path from a given node to any of its descendant NIL nodes contains the same number of black nodes. 
 *    
 * Black-height of RB Tree: 
 * The number of black nodes from the root to a node is the node's black depth; 
 * the uniform number of black nodes in all paths from root to the leaves 
 * is called the black-height of the red–black tree.
 *
 */

#include<stdlib.h>
#include<stdio.h>
#define TRUE 1
#define FALSE 0

enum color{
  RED, BLACK
};

typedef enum color color;

struct node{
  int data;
  color color; 
  struct node *left, *parent, *right;
};
typedef struct node node;

node* getNewNode(int data);
node* uncle(node *x);
node* grandParent(node *x);

node* insert(node *x, int data);
node* bst_insert(node* x, node **new, int data);
node* insert_case1(node *root, node **n);
node* insert_case2(node *root, node **n);
node* insert_case3(node *root, node **n);
node* insert_case4(node *root, node **n);
node* insert_case5(node *root, node **n);

void preOrder(node *root);
void inOrder(node *root);
node* rotate_right(node *p);
node* rotate_left(node *p);
node* findMin(node *p);
node* findMax(node *p);
node* getPredecessor(node * root, int data);
node* getSuccessor(node * root, int data);
node* find(node* root, int data);
int isRed(node *s);
int isBlack(node *s);
int is_leaf(node *n);
node* sibling(node *n);
void replace_node(node **n, node **child);
void findDeleteNode(node *root, node **new, int data);

node* delete(node *root, int data);
node* delete_one_child(node *root, node **n);
node* delete_case1(node *root, node **n);
node* delete_case2(node *root, node **n);
node* delete_case3(node *root, node **n);
node* delete_case4(node *root, node **n);
node* delete_case5(node *root, node **n);
node* delete_case6(node *root, node **n);

/* main function : RB Tree */
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
               root = delete(root,x);
               break;
      case 4:  printf("\n0:RED 1:BLACK");
               printf("\nPreorder sequence:\n");
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

/* node is leaf ? */
int is_leaf(node *n)
{
  if(n != NULL && n->right == NULL && n->left == NULL) 
    return TRUE;
  else
    return FALSE;
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

/* return the sibling node */
struct node *sibling(struct node *n)
{
  if ((n == NULL) || (n->parent == NULL))
    return NULL; // no parent means no sibling
  if (n == n->parent->left)
    return n->parent->right;
  else
    return n->parent->left;
}

/* Color of node 's' is BLACK ? */
int isBlack(node *s) {
  return (((s!= NULL) && (s->color == BLACK)) || (s == NULL));
}

/* Color of node 's' is BLACK ? */
int isRed(node *s) {
  return ((s!= NULL) && (s->color == RED));
}

/* RB TREE delete a node: entry point */
node* delete(node *root, int data)
{
  node *temp =NULL, *n = NULL;

  //Find the node to be deleted 'n'
  n = find(root, data);

  if(n==NULL){
    printf("\n\tWrong Input !");
    return root;
  }

  //case-1 : no child
  if((n->left == NULL) && (n->right == NULL))
  {
    if(n->color == RED)
    {
      // Just delete RED node
    }
    else if(n->color == BLACK)
      root = delete_case1(root, &n);

    if(n->parent->left == n)
      n->parent->left = NULL;
    else
      n->parent->right = NULL;

    temp = n;
    n = NULL;
    free(temp);
  }
  //case-3 : both child
  else if(n->left != NULL && n->right != NULL)
  {
    temp = findMin(n->right);
    n->data = temp->data;
    n->right = delete(n->right, temp->data);
  }
  //case-2 : one child
  else if(n->left != NULL || n->right != NULL)
  {
    root = delete_one_child(root, &n);
  }
  return root;
}

//A, B, C : RED have 1 Black node
node* delete_one_child(node *root, node **n)
{
  /* Precondition: n has at most one non-null child.
   * RED    - n
   * BLACK  - Child
   * 
   *   n      R
   *   |     /   
   * child  B  
   */
  node *child = is_leaf((*n)->right) ? (*n)->right : (*n)->left;
  node *temp = NULL;

  //replace_node(n, child);
  //where the function replace_node substitutes child into n's place in the tree
  child->parent = (*n)->parent;
  if((*n)->parent != NULL)
  {
    if((*n)->parent->left == (*n))
      (*n)->parent->left = child;
    else
      (*n)->parent->right = child;
  }

  if((*n)->color == BLACK)
  {
    if(child->color == RED){
      child->color = BLACK;
    }
    else
      //Double Black Case
      root = delete_case1(root, &child);
  }

  //free n
  temp = *n;
  *n = NULL;
  free(temp);

  return root;
}

// Case-1: Root Black
node* delete_case1(node *root, node **n)
{
  if((*n)->parent != NULL)
    root = delete_case2(root, n);
  return root;
}

// Case-2: Sibling RED, all black
node* delete_case2(node *root, node **n)
{
  struct node *s = sibling((*n));
  node *g = grandParent(*n), *temp_root = NULL;
  //twoChildFlag is used for case where delete(10) is called 
  //that will call delete(root = 40, 20) 
  //here we need to handle root change approprietly.
  int twoChildFlag = FALSE;

  if((*n)->parent == root)
    twoChildFlag = TRUE;

  if(s->color == RED)
  {
    (*n)->parent->color = RED;
    s->color = BLACK;
    if((*n) == (*n)->parent->left)
    {
      //rotate always rotate new node at old position of 'n' in tree
      (*n)->parent->parent = temp_root = rotate_left((*n)->parent);
    }
    else
    {
      (*n)->parent->parent = temp_root = rotate_right((*n)->parent);
    }
  }

  //Check for new root
  if(temp_root != NULL && temp_root->parent == NULL)
    root = temp_root;
  else if(twoChildFlag == TRUE)
    root = temp_root;

  root = delete_case3(root, n);
  return root;
}

// Case-3: All Black
node* delete_case3(node *root, node **n)
{
  node *s = sibling(*n);

  if (((*n)->parent->color == BLACK) &&
      isBlack(s) && 
      isBlack(s->left) && 
      isBlack(s->right))
  {
    s->color = RED;
    root = delete_case1(root, &((*n)->parent));
  } 
  else
    root = delete_case4(root, n);
  return root;
}

// Case-4 : Parent=RED & all black.
node* delete_case4(node *root, node **n)
{
  node *s = sibling((*n));

  if (((*n)->parent->color == RED) &&
      isBlack(s) && 
      isBlack(s->left) &&
      isBlack(s->right)) 
  {
    s->color = RED;
    (*n)->parent->color = BLACK;
  } 
  else
    root = delete_case5(root, n);
  return root;
}

//Case-5: Zig-Zag LR(n) & RL(n)
node* delete_case5(node *root, node **n)
{
  node *s = sibling(*n);

  if(isBlack(s)){ 
    /* this if statement is trivial,
     * due to case 2 (even though case 2 changed the sibling to a sibling's child,
     * the sibling's child can't be red, since no red parent can have a red child). 
     * the following statements just force the red to be on the left of the left of the parent,
     * or right of the right, so case six will rotate correctly. */
    if(((*n) == (*n)->parent->left) &&
        (isBlack(s->right)) &&
        (isRed(s->left))) 
    { 
      /* this last test is trivial too due to cases 2-4. */
      s->color = RED;
      s->left->color = BLACK;
      s = rotate_right(s);
    } 
    else if (((*n) == (*n)->parent->right) &&
        (isBlack(s->left)) &&
        (isRed(s->right))) 
    {
      /* this last test is trivial too due to cases 2-4. */
      s->color = RED;
      s->right->color = BLACK;
      s = rotate_left(s);
    }
  }
  root = delete_case6(root, n);
  return root;
}

//Case-6 : Zig-Zig LL(n) & RR(n)
node* delete_case6(node *root, node **n)
{
  struct node *s = sibling(*n), *temp_root = NULL;

  s->color = (*n)->parent->color;
  (*n)->parent->color = BLACK;

  if ((*n) == (*n)->parent->left) {
    s->right->color = BLACK;
    temp_root = rotate_left((*n)->parent);
  } else {
    s->left->color = BLACK;
    temp_root = rotate_right((*n)->parent);
  }

  //Check for new root
  if(temp_root != NULL && temp_root->parent == NULL)
    root = temp_root;
  return root; 
}

/* GrandParent of node-x  */
node* grandParent(node *x)
{
  if(x !=NULL && x->parent !=NULL)
    return x->parent->parent;
  else 
    return NULL;
}

/* Uncle of node-x  */
node* uncle(node *x)
{
  node *g = grandParent(x);

  if(x!= NULL && g != NULL)
  {
    if(x->parent == g->left)
      return g->right;
    else
      return g->left;
  }
  else
    return NULL;
}

/* Create a new Node */
node* getNewNode(int data)
{
  node *p;
  p = (node *)malloc(sizeof(node));
  p->data = data;
  p->left = NULL;
  p->right = NULL;
  p->parent = NULL;
  p->color = RED;
  return p;
}

/* Insert a new node in RB Tree */
node* insert(node *root, int data)
{
  node *new = NULL;

  //BST insert 
  root = bst_insert(root, &new, data);

  //check for RB TREE Properties
  if(new != NULL)
  {
    root = insert_case1(root, &new);
    root->color = BLACK;
  }
  else
    printf("\n\tPlease enter correct data\n");
  return root;
}

/* BST Insert */
node* bst_insert(node *root, node **new, int data)
{
  node *newNode = NULL;

  if(root == NULL) {
    newNode = getNewNode(data);
    root = newNode;
    *new = newNode;
  }
  else if(data < root->data){
    root->left = bst_insert(root->left, new, data);
    root->left->parent = root;
  }
  else if(root->data < data){
    root->right = bst_insert(root->right, new, data);
    root->right->parent = root;
  }

  return root;
}

//case-1: If root is null, make root->color = BLACK
node* insert_case1(node *root, node **n)
{
  if(*n != NULL && (*n)->parent == NULL)
  {
    (*n)->color = BLACK;
    return *n;
  }
  else
  { 
    root = insert_case2(root, n); 
    return root;
  }
}

//case2: if parent = BLACK, then leave as it is. 
node* insert_case2(node *root,node **n)
{
  if(*n!=NULL && (*n)->parent != NULL && (*n)->parent->color == BLACK)
    return root;
  else
    root = insert_case3(root, n);
  return root;
}

//case-3: parent == RED & uncle == RED
node* insert_case3(node *root, node **n)
{
  node *g = grandParent(*n);
  node *u = uncle(*n);

  if(*n!= NULL && (*n)->parent->color == RED)
  { 
    if(u != NULL && u->color == RED)
    {
      (*n)->parent->color = BLACK;
      u->color = BLACK;
      g->color = RED;
      root = insert_case1(root, &g);
    }
    else
    {
      root = insert_case4(root, n);
    }
  }
  return root;
}

//case-4:
// Zig-Zag & uncle is BLACK
// if Parent is Left Child of GrandPaent & new node is Right child of Parent, then Rotate
// Similarly perform the same for right child of grandparent.
node* insert_case4(node *root, node **n)
{
  node *g = grandParent(*n);
  node *u = uncle(*n);

  if(u!= NULL && u->color == BLACK)
  {
    //Left -> Right
    if((*n == (*n)->parent->right) && (g!= NULL) && (g->left == (*n)->parent))
    {
      *n = rotate_left((*n)->parent);
      *n = (*n)->left;
    }
    // Right - > Left
    else if((*n == (*n)->parent->left) && (g!=NULL) && (g->right == (*n)->parent))
    {
      *n = rotate_right((*n)->parent);
      *n = (*n)->right;
    }
  }

  root = insert_case5(root, n);
  return root;
}

//case-5: LL or RR case where p = RED, N = RED
node* insert_case5(node *root, node **n)
{
  node *g = NULL, *temp_root = NULL;
  if(*n!= NULL)
  {
    g = grandParent(*n);

    if(g!=NULL)
      g->color = RED;

    (*n)->parent->color = BLACK;

    if((*n)->parent->left == (*n)){
      temp_root = *n = rotate_right(g);
    }
    else{
      temp_root = *n = rotate_left(g);
    }
  }

  if(temp_root != NULL && temp_root->parent == NULL)
    root = temp_root;

  return root;
}

/* Left-Rotate Operation for RB Tree*/
node* rotate_left(node *p)
{
  node *g, *n,*saved_left_n, *saved_p;
  g = n = saved_left_n = saved_p = NULL;

  if(p!= NULL)
  {
    g = p->parent;
    n = p->right;

    saved_p = p;
    saved_left_n = n->left;

    if(g != NULL)
      if(g->left == saved_p)
        g->left = n;
      else if(g->right == saved_p)
        g->right = n;

    n->left = saved_p;
    saved_p->right = saved_left_n;

    if(saved_left_n != NULL)
      saved_left_n->parent = saved_p;

    saved_p->parent = n;
    n->parent = g;

    return n;
  }
}

/* Right-Rotate Operation for RB-TREE */
node* rotate_right(node *p)
{
  node *g, *n, *saved_right_n, *saved_p;
  g = n = saved_right_n = saved_p = NULL;

  if(p!= NULL)
  {
    g = p->parent;
    n = p->left;

    saved_p = p;
    saved_right_n = n->right;

    if(g != NULL)
      if(g->left == saved_p)
        g->left = n;
      else if(g->right == saved_p)
        g->right = n;

    n->right = saved_p;
    saved_p->left = saved_right_n;

    if(saved_right_n != NULL)
      saved_right_n->parent = saved_p;

    saved_p->parent = n;
    n->parent = g;

    return n;
  }
}

/* L-D-R Print Tree data in In-Order Traversal */
void inOrder(node *root)
{
  if(root != NULL)
  {
    inOrder(root->left);
    printf(" %d:color(%d) ",root->data,root->color);
    inOrder(root->right);
  }
}

/* D-L-R : Print Tree data in Pre-Order Traversal */
void preOrder(node *root)
{
  if(root!=NULL)
  {
    printf(" %d:color(%d) ",root->data,root->color);
    preOrder(root->left);
    preOrder(root->right);
  }
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
