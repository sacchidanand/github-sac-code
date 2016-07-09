#include<stdio.h>
#include<stdlib.h>

#define UNINIT -200
#define MAX_VERTICES 3
#define TRUE 1
#define FALSE 0

static int time=0;

/* Adjecancy list used for representing Graph */
struct adjList{
  int data, level, parent, index, start, finish;
  struct adjList *next;
}*adj[10];
typedef struct adjList adjList;

/* Queue used for frontier storage */
struct queue{
  adjList *adjNode;
  struct queue *next;
}*head, *tail;
typedef struct queue queue;

/* Prototype */
void createVertices();
queue* createQNode(adjList *newQNode);
adjList* createNewAdjListNode(int data, int index);
void printAdjList();
void printQueue();
void insertNodeInGraph();
queue *deQueue();

/* Allocate memory on a heap for a Queue-node */
queue* createQNode(adjList *newNode)
{
  queue *newQNode = (queue *) malloc(sizeof(queue));
  newQNode->adjNode = newNode;
  newQNode->next = NULL;
  return newQNode;
}

/* Allocate memory for AdjList Nodes */
adjList* createNewAdjListNode(int data, int index){
  adjList *newAdj = (adjList*)malloc(sizeof(adjList));
  newAdj->data = data;
  newAdj->parent = UNINIT;    
  newAdj->index = index;
  newAdj->level = UNINIT;
  newAdj->start = UNINIT;
  newAdj->finish = UNINIT;
  newAdj->next = NULL;
  return newAdj; 
}

/* Reset state of Vertices in Adjecancy List */
void resetVertices(){
  int i =0, inputData = UNINIT;
  //printf("\nResetting Vertice State in Graph for New BFS/DFS Execution.");
  for(i=0; i < MAX_VERTICES; i++){
    adj[i]->parent = UNINIT;
    adj[i]->level = UNINIT;
    adj[i]->start = UNINIT;
    adj[i]->finish = UNINIT;
  }
  return;
}

/* Delete vertices adjecancy list */
void deleteAdjList(adjList *vertice){
  adjList *temp = NULL;
  temp = vertice;  
  while(vertice !=NULL){
    vertice = vertice->next;
    //printf("\n freed adjList# %d ",temp->data);
    free(temp); 
    temp = vertice;  
  }
}

/* Delete vertices in Graph */
void deleteVertices(){
  int i =0;
  for(i=0; i<MAX_VERTICES; i++)
    free(adj[i]);
}

/* Delete whole Graph before existing */
void deleteGraph(){
  int i =0;
  for(i =0; i<MAX_VERTICES; i++)
    deleteAdjList(adj[i]->next);
  deleteVertices();
}

/*Resetting Queue and freeing up memory */
void resetQueue(){
  queue *tempQ = NULL; 
  while((tempQ = deQueue()) != NULL){
    //printf("\nFreed up the space # %d", tempQ->adjNode->data);
    free(tempQ);
  }
  printQueue();
}

/* Create vertices in Adjecancy List */
void createVertices(){
  int i =0, inputData = UNINIT;
  for(i=0; i < MAX_VERTICES; i++){
    printf("\n Enter data for new vertice: ");
    scanf("%d",&inputData);
    adj[i] = createNewAdjListNode(inputData, i);
  }
  return;
}

/* Insert new neighbour in adjList */
void insertNewNeighborinAdjList(adjList *tempAdjNode,int verticeIndex){
  adjList *temp = adj[verticeIndex];

  if(temp !=NULL){
    while(temp->next != NULL)
      temp = temp->next;
    temp->next = tempAdjNode;
  }
  else
    printf("\n\nAdjcancy list is Empty, no neighbour present for vertice # %d\n", verticeIndex);
}

/* Insert Node in Graph */
void insertNodeInGraph(){
  int i =0, verticeIndex = UNINIT, totalNewNeighbour = UNINIT, newNeighbourIndex = UNINIT; 
  adjList *tempAdjNode = NULL;

  printf("\n Enter Index of vertice # ");
  scanf("%d", &verticeIndex);
  printf("\n How many new neighbours you want to create # ");
  scanf("%d", &totalNewNeighbour);

  for(i=0; i<totalNewNeighbour; i++){
    printf("\n Enter neighbour index # ");
    scanf("%d", &newNeighbourIndex);
    tempAdjNode = createNewAdjListNode(adj[newNeighbourIndex]->data, newNeighbourIndex);
    insertNewNeighborinAdjList(tempAdjNode, verticeIndex);
  }

  printf("\nAdded total=%d new neighbour for Vertice =%d \n", totalNewNeighbour, adj[verticeIndex]->data);
}

/* EnQue node */
void enQueue(adjList *newNode){
  queue *newQNode = createQNode(newNode);

  if(tail!=NULL){
    tail->next = newQNode;
    tail = newQNode;	
  }
  else{
    tail = head = newQNode;
  }
}

/* DeQueue node */
queue *deQueue(){
  queue *temp = NULL;
  temp = head;

  if(head == tail){
    head = tail = NULL;
  }
  else if(head != NULL){
    head = head->next;
  }  
  return temp;
}

/* Print AdjList */
void printAdjList(){  
  adjList *tempAdjList;
  int i=0;
  printf("\nPrinting Adjecancy List\n----------------------");

  for(i=0; i<MAX_VERTICES; i++){
    printf("\n AdjList[%d-%dp-%di-%dl-%dst-%dft] : ", adj[i]->data, adj[i]->parent, \
        adj[i]->index, adj[i]->level, adj[i]->start, adj[i]->finish); 
    tempAdjList = adj[i];
    tempAdjList = tempAdjList->next;

    while(tempAdjList != NULL){
      printf("[%d-%dp-%di-%dl-%dst-%dft]->", tempAdjList->data, tempAdjList->parent,  \
          tempAdjList->index, tempAdjList->level, tempAdjList->start, tempAdjList->finish);
      tempAdjList = tempAdjList->next;
    }
    printf("\\");
  }/*End for*/
}

/* Print Queue */
void printQueue(){
  int i=0;
  queue *tempQueue = head;
  printf("\nPrinting Queue \n---------------------\n");

  while(tempQueue != NULL){
    printf("[%d-%dp-%di-%dl]->", tempQueue->adjNode->data, tempQueue->adjNode->parent,  \
        tempQueue->adjNode->index, tempQueue->adjNode->level);
    tempQueue= tempQueue->next;
  }
  printf("\\");
}

/*Run Breadth First Search Algo on Graph */
void bfs(){
  int sourceIndex = UNINIT, nextFrontierIndex = UNINIT;
  head = tail = NULL;

  printf("\n\t Please enter the Source Index: ");
  scanf("%d", &sourceIndex);

  adj[sourceIndex]->level = 0;
  adj[sourceIndex]->parent = UNINIT;
  enQueue(adj[sourceIndex]);
  queue *frontier = head;
  printf("\t******** Running BFS ********");

  while(frontier != NULL) {
    adjList *tempAdj = frontier->adjNode->next;

    while(tempAdj != NULL){
      nextFrontierIndex = tempAdj->index;

      if(adj[nextFrontierIndex]->level == UNINIT && adj[nextFrontierIndex]->parent == UNINIT){
        adj[nextFrontierIndex]->parent = frontier->adjNode->index;
        adj[nextFrontierIndex]->level = adj[frontier->adjNode->index]->level + 1;
        enQueue(adj[nextFrontierIndex]);
      }

      tempAdj = tempAdj->next;
    }//inner while

    frontier = frontier->next;
  }//outer while
}

/* DFS_VISIT*/
void dfs_visit(adjList *s){
  adjList *v = NULL;
  
  if(s!=NULL){
    adj[s->index]->start = time++;
    v = adj[s->index]->next;

    while(v!=NULL){
      if(adj[v->index]->parent==UNINIT){
        adj[v->index]->parent = s->index;
        dfs_visit(v);
      }
      v = v->next;
    }// while end  

    adj[s->index]->finish = time++;
  }
}

/* Depth First Search */
void dfs(){
  int i =0;
  adj[0]->parent = 999;
  dfs_visit(adj[0]);

  for(i=0; i< MAX_VERTICES; i++){
    if(adj[i]->parent == UNINIT)
      dfs_visit(adj[i]);
  }
}

/* main */
int main(void){
  int choice=0, bfsExecutedOnce = FALSE, dfsExectedOnce = FALSE;
  head = tail = NULL;
  printf("\n\t--------------------------------------");
  printf("\n\t\tWelcome to BFS Program\n");
  printf("\t--------------------------------------\n");

  createVertices();
  while(1){
    printf("\n***********************************************************************");
    printf("\n    \
        \n\t1: Print AdjList    \
        \n\t2: Print Queue   \
        \n\t3: Insert Node in graph   \
        \n\t4: Run BFS - Breadth First Search Algorithm    \
        \n\t5: Run DFS - Depth First Search Algorithm   \
        \n\t9: Exit    \
        \n\nPlease Enter Choice # ");
    scanf("%d",&choice);
    switch(choice){
      case 1: printAdjList();
              break;
      case 2: printQueue();
              break;
      case 3: insertNodeInGraph();
              break;
      case 4: if(bfsExecutedOnce == TRUE){
                resetVertices();
                resetQueue();
              }
              else
                bfsExecutedOnce = TRUE;
              bfs();
              break;
      case 5: dfs();
              break;
      case 9: resetQueue();
              deleteGraph();
              printf("\n***********************************************************************");
              printf("\n\n\tProgram exiting.\n\tThanks for using BFS/DFS ! \n");
              printf("\n***********************************************************************\n\n");
              exit(0);
      default: printf("\n Please Enter correct Choice :\n\t");
    }
  }
  return 0;
}


