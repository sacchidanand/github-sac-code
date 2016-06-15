#include<stdio.h>
#include<stdlib.h>

#define UNINIT -200
#define MAX_VERTICES 3

struct adjList;
typedef struct adjList adjList;

/* Queue used for frontier storage */
struct queue{
  adjList *adjNode;
  struct queue *next;
}*head, *tail;
typedef struct queue queue;

/* Adjecancy list used for representing Graph */
struct adjList{
  int data, level;
  struct adjList *next, *parent;
}*adj[10];
typedef struct adjList adjList;

void initAdjList();
queue* createQNode(adjList *newQNode);
adjList* createNewAdjListNode(int data);
void printAdjList();
void printQueue();
void insertNodeInGraph();

/* Allocate memory on a heap for a Queue-node */
queue* createQNode(adjList *newNode)
{
  queue *newQNode = (queue *) malloc(sizeof(queue));
  newQNode->adjNode = newNode;
  newQNode->next = NULL;
  return newQNode;
}

/* Allocate memory for AdjList Nodes */
adjList* createNewAdjListNode(int data){

  adjList *newAdj = (adjList*)malloc(sizeof(adjList));
  newAdj->data = data;
  newAdj->parent = NULL;
  newAdj->level = UNINIT;    
  newAdj->next = NULL;
  return newAdj; 
}

/*
void reInitializeAdjList(){
  int i= 0;
  adjList *temp = NULL;
  for(i=0; i<MAX_VERTICES; i++){
    adj[i]->parent = NULL;
    adj[i]->level = UNINIT;    
    adj[i]->next = NULL;

    temp = adj[i]->next;
    while(temp !=NULL){
      temp->parent = NULL;
      temp->level = UNINIT;
      temp = temp->next;
    }
  }
}
*/

/* Initialize the Adjecancy list */
void initAdjList(){
  int i =0, inputData = UNINIT;
  for(i=0; i < MAX_VERTICES; i++){
    printf("\n Enter data for new vertice: ");
    scanf("%d",&inputData);
    adj[i] = createNewAdjListNode(inputData);
  }
  return;
}

void insertNewNeighborinAdjList(adjList *tempAdjNode,int verticeIndex){
  adjList *temp = adj[verticeIndex];
  if(temp !=NULL){
    while(temp->next != NULL){
      temp = temp->next;
    }
    temp->next = tempAdjNode;
  }
  else{
    printf("\n\n Adjcancy list is Empty, No neighbour present for Vertice = %d\n", verticeIndex);
  }
}

void insertNodeInGraph(){
  int i =0, verticeIndex = UNINIT, totalNewNeighbour = UNINIT, newNeighbourIndex = UNINIT; 
  adjList *tempAdjNode = NULL;

  printf("\n Please Enter the index of the vertice for which you want to create neighbours : ");
  scanf("%d", &verticeIndex);

  printf("\nHow Many new neighbours you want to create for Vertice=%d ? \n", adj[verticeIndex]->data);
  scanf("%d", &totalNewNeighbour);

  for(i=0; i<totalNewNeighbour; i++){
    printf("Please enter new neighbour index for Vertice=%d :", adj[verticeIndex]->data);
    scanf("%d", &newNeighbourIndex);

    tempAdjNode = createNewAdjListNode(adj[newNeighbourIndex]->data);
    insertNewNeighborinAdjList(tempAdjNode, verticeIndex);
  }
  printf("\nAdded total=%d new neighbour for Vertice =%d \n", totalNewNeighbour, adj[verticeIndex]->data);
}

void enQueue(adjList *newNode){
  queue *newQNode = (queue *) malloc(sizeof(queue));
  newQNode->adjNode = newNode;
  newQNode->next = NULL;

  if(tail!=NULL){
    tail->next = newQNode;
    tail = newQNode;	
  }
  else{
    tail = head = newQNode;
  }
}

queue *deQueue(){
  queue *temp = NULL;
  if(head == tail){
    temp = head;
    head = tail = NULL;
  }
  else if(head != NULL){
    temp = head;
    head = head->next;
  }  
  return temp;
}

void printAdjList(){  
  adjList *tempAdjList;
  int i=0;
  printf("\nPrinting Adjecancy List\n----------------------");
  for(i=0; i<MAX_VERTICES; i++){
    printf("\n AdjList[%d] : ", adj[i]->data);
    tempAdjList = adj[i];
    tempAdjList = tempAdjList->next;

    while(tempAdjList != NULL){
      //if(tempAdjList->parent!= NULL)
      //printf("parent = %d, ",tempAdjList->parent->data);
      //printf("[%d, %d] -> ",tempAdjList->data,tempAdjList->level);
      //
      printf("[%d]->",tempAdjList->data);
      tempAdjList = tempAdjList->next;
    }
    printf("\\");
  }
}

void printQueue(){
  int i=0;
  queue *tempQueue = head;
  printf("\nPrinting Queue \n---------------------\n");
  while(tempQueue != NULL){
    printf("[%d]->", tempQueue->adjNode->data);
    tempQueue= tempQueue->next;
  }
  printf("\\");

}

int findIndex(adjList *temp){
  int index = UNINIT, i=0;  
  for(i=0;i<MAX_VERTICES; i++){
    if(temp->data == adj[i]->data)
      index = i;     
  }
  if(index == UNINIT)
    printf("Cant find the index for %d", temp->data);
  //else
  //printf("Next Frontier Index = %d", index);
  return index;
}

void bfs(){
  int sourceIndex = UNINIT, nextFrontierIndex = UNINIT;
  head = tail = NULL;
  //reInitializeAdjList();  
  printf("\n\tPlease enter the Source Index: ");
  scanf("%d", &sourceIndex);

  adj[sourceIndex]->level = 0;
  adj[sourceIndex]->parent = NULL;
  enQueue(adj[sourceIndex]);
  queue *frontier = head;
  //printQueue(); 	
  while(frontier != NULL){
    adjList *tempAdj = frontier->adjNode->next;
    //printf("\n In BFS");	

    /*if(tempAdj !=NULL){
      printf("[tempAdj: %d %d", tempAdj->data, tempAdj->level);
      if(tempAdj->parent!=NULL)
      printf(" parent =%d ], ", tempAdj->parent->data);
      }*/

    while(tempAdj != NULL){        
      nextFrontierIndex = findIndex(tempAdj);
      if(adj[nextFrontierIndex]->level == UNINIT && adj[nextFrontierIndex]->parent == NULL){
        adj[nextFrontierIndex]->parent = adj[findIndex(frontier->adjNode)]->parent;
        adj[nextFrontierIndex]->level = adj[findIndex(frontier->adjNode)]->level + 1;
        enQueue(adj[nextFrontierIndex]);
      }
      tempAdj = tempAdj->next;
    }// inner while

    frontier = frontier->next;
  }//outer while
}



int main(void){
  int choice=0;
  head = tail = NULL;
  printf("\n\t--------------------------------------");
  printf("\n\t\tWelcome to BFS Program\n");
  printf("\t--------------------------------------\n");

  initAdjList();
  while(1){
    printf("\n***********************************************************************");
    printf("\n\n\t1: Print AdjList\n\t2: Print Queue \n\t3. Insert Node in graph\n\t4. Run BFS Algorithm\n\t9:Exit\n\nPlease Enter Choice:");
    scanf("%d",&choice);
    switch(choice){
      case 1: printAdjList();
              break;
      case 2: printQueue();
              break;
      case 3: insertNodeInGraph();
              break;
      case 4: bfs();
              break;
      case 9: exit(0);      
      default: printf("\n Please Enter correct Choice :\n\t");
    }
  }
  return 0;
}


