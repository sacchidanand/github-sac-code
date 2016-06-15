//2-11 7.00
//2-11 7.00
// Author : Sacchidanand bhavari
// sacchidanand.b@gmail.com

/*	
 * 	Changes Done in version 8.2
 * 	
 *  1. size 100 ->1000
 *  2. Calculation of time 
 * 	3. Taking input from command line argument
 *  4. Removing the Matrix storage and modifying the linked list storage.
 *  5. Changed the behaviour in which program will work.
 * 	6. Graph is represented as Adjecancy list.
 * 
 * */

/*	Version 9.2 
 *  1. vizGraphOutputPartA.dot, vizGraphOutputPartB.dot, inputPartB.adj corrected.
 * 	2. userInput file is added for user convenience.
 * 	3. 
 * 
 * */
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
#include <sys/time.h>
#include <unistd.h>
# include <string.h>


#define size 10000

struct node
{
	//int label,edge_wt;
	// Here we have to change int to char* type of label
	int edge_wt,colour,previousInDFS,discover_time,finish_time;
	int countBiconnectedVertex;
	char* label;
	struct node *next,*predessor;
};
// Semicolon is must

/*
	struct node *rightInList;
	char *nodeID;
	double value;
	int degreeOfNode;
*/

struct node *alist[10000];
struct node *trackList[10000+1];


//int matrix[size+1][size+1],x_co_ordinate,y_co_ordinate;

int rootList[size+1],rootIndex=0,i=1,k=1,totalSCC=0;
static int id=0,edge=0,time=0,currentRootId=1,sampleCount=1;
int transpose_matrix[size+1][size+1];
int priorityNodeList[size+1];



long long timeval_diff(struct timeval *difference,struct timeval *end_time,struct timeval *start_time)
{
  struct timeval temp_diff;

  if(difference==NULL)
  {
    difference=&temp_diff;
  }

  difference->tv_sec =end_time->tv_sec -start_time->tv_sec ;
  difference->tv_usec=end_time->tv_usec-start_time->tv_usec;

  /* Using while instead of if below makes the code slightly more robust. */

  while(difference->tv_usec<0)
  {
    difference->tv_usec+=1000000;
    difference->tv_sec -=1;
  }

  return 1000000LL*difference->tv_sec+
                   difference->tv_usec;

} /* timeval_diff() */

struct node* create_node(int l)
{
	struct node *k;
	k=(struct node *)malloc(sizeof(struct node));
	k->label=(char *)malloc(sizeof(char)*4);

	if(l==100)
	{
		//k->label=-500;
		sprintf(k->label,"%d",-500); 
		//itoa(-500, k->label, 10);	
	}
	else
	{
		//k->label=id++;	
		sprintf(k->label,"%d",id++);
		//itoa(id++,k->label,10);
	}
	k->edge_wt=0;
	k->next=NULL;
	k->predessor=NULL;
	k->colour=0;
	k->previousInDFS=0;
	k->countBiconnectedVertex=0;
	return (k);
}

void create_all_vertices(int n)
{
	int i=0,j=0;
	for(i=0;i<n;i++)
	{
		alist[i]=create_node(2);
	}
}

void reset_alist(int n)
{
	int i=0,j=0;
	for(i=0;i<n;i++)
	{
		alist[i]->next=NULL;
	}

}

// This function works for undirected graph
void insertEdgesInto_alist(int i,int j,int probability)
{
	struct node *p,*q;
	int k=0,randomWt=0,temp_num=0;
	int flag=0,entry1=0;
	k=rand()%100;
		
	
	if(k<probability && i!=j){
		edge++;
		do{
			randomWt=rand()%1000;
		}while(randomWt==0);


		// Making an entry of edge(i,j) into alist[i]
		p=alist[i];
		while(flag==0 && (p->next!=NULL)){		
			temp_num=atoi(p->next->label);
			if(temp_num!=j)				//if(p->next->label!=j)		
				p=p->next;
			else
				flag=1;	// edge (i,j) already exists
		}	
		/* if flag=0 means (i,j) does not exists, so add (i,j)*/
		if(flag==0 ){		
			//x_co_ordinate=i;
			//y_co_ordinate=atoi(alist[j]->label);
			//if (matrix[x_co_ordinate][y_co_ordinate]==0 && matrix[y_co_ordinate][x_co_ordinate]==0)
			if(p!=NULL){
				p->next=create_node(100);
				p->next->label=alist[j]->label;
				p->next->edge_wt=randomWt;
				entry1=1;
				//matrix[x_co_ordinate][y_co_ordinate]=randomWt;
			}
		}	
		/* 6-9-2011 (changed for directed graph)
		// Making an entry of edge(j,i) into alist[j]	
		if(entry1==1)
		{
			q=alist[j];
			while(q->next!=NULL)
				q=q->next;	
			q->next=create_node(100);
			q->next->label=alist[i]->label;
			q->next->edge_wt=randomWt;
		}*/
	}
}

void initializePriorityNodeList(int totalNoOfNodes)
{
	int i=1;
	for(i=1;i<totalNoOfNodes;i++)
		priorityNodeList[i]=i;
}

void computeTransposeAndStoreIt(int totalNoOfNodes)
{
	int i=0,j=0;
	struct node *p;
	FILE *fp;
	fp=fopen("transpose.adj","w");
	fprintf(fp,"%d %d",totalNoOfNodes-1,edge);

	for(i=0;i<totalNoOfNodes;i++){	
		p=alist[i];
		//printf("\n alist[%d] :: ",i);
		if(p!=NULL)
			p=p->next;
		while(p!=NULL){
			j=atoi(p->label);
			fprintf(fp,"\n%d %d %d",(j),(i),p->edge_wt);	
			//printf(" %s,%d | ",p->label,p->edge_wt);
			p=p->next;
		}
	}
		//printf("\n\n");
		/*
		for(i=1;i<totalNoOfNodes;i++)
		{
			for(j=1;j<totalNoOfNodes;j++)
			{
				if(matrix[i][j]!=0)
					fprintf(fp,"\n%d %d",(i-1),(j-1));
			}
			//fprintf(fp,"\n");
		} */
	fclose(fp);	
}

void rootListInitialize(int totalNoOfNodes)
{
	int i=0;
	// initialize the rootlist upto total no of Nodes
	for(i=0;i<totalNoOfNodes;i++){
		rootList[i]=0;
	}

	//for remaining nodes
	for(i=totalNoOfNodes+1;i<100;i++){
		rootList[i]=-1;
	}
}

void dfs_visit(int u,int tempW,int totalNoOfNodes)
{
	struct node *tempNode, *temp, *p, *start;
	int tempNodeNumber=0,i=1, tempWeight=0;

		alist[u]->colour=2;	// gray=2
		time++;
		alist[u]->discover_time = time;
		temp = alist[u]->next;

		while(temp!=NULL){
			tempNodeNumber = atoi(temp->label);
			tempWeight = temp->edge_wt;
			if(alist[tempNodeNumber]->colour==1){//white=1
				alist[tempNodeNumber]->previousInDFS = u;
				dfs_visit(tempNodeNumber,tempWeight,totalNoOfNodes);
			}
			temp = temp->next;
		}

		alist[u]->finish_time = ++time;
		alist[u]->colour=3;	//black=3

		// Adding node 'u'  entry into the link-list of nodes (who belong to same tree) 
		// to track back DFS
/*
		if(trackList[currentRootId] != NULL)
		{
			tempNode = trackList[currentRootId]->next;
			trackList[currentRootId]->next = create_node(100);
			// we have to add weight also to identify exact edge
			//trackList[currentRootId]->edge_wt =  


			itoa(u, trackList[currentRootId]->next->label, 10);

			trackList[currentRootId]->next->next = tempNode;	
		}
*/
		start = trackList[currentRootId];
		if(start != NULL){
			p = create_node(100);
			p->edge_wt=tempW;
			//itoa(u,p->label,10);
			sprintf(p->label,"%d",u);
			p->next = start->next;
			start->next = p;
		}	
	//}
}

void dfs(int totalNoOfNodes)
{		
	int i = 1, u = 1;	
	// initialize track array to total_no_of_nodes
	rootListInitialize(totalNoOfNodes);

	// Initialize all nodes of alist
	for(i=1; i<totalNoOfNodes; i++){
		alist[i]->colour = 1;
		alist[i]->predessor=NULL;
		alist[i]->previousInDFS=0;
	}

	time=0;
	for(i=1; i<totalNoOfNodes; i++){
		u = priorityNodeList[i];	// To define the traversal order of DFS 
		if(alist[u]->colour==1){	//	white=1
			currentRootId=u;
			rootList[currentRootId] = 1; // Set the flag of rootList[currentRootId] to indicate root presence
			trackList[currentRootId] = create_node(100);
			//itoa(currentRootId, trackList[currentRootId]->label, 10);
			sprintf(trackList[currentRootId]->label,"%d",currentRootId);
			dfs_visit(u,alist[u]->edge_wt,totalNoOfNodes);
		}
	}
}

void minimal_connected(int total_vertex)
{
	int m=0,no=0;
	insertEdgesInto_alist(1,2,100);	
	for(m=3;m<total_vertex;m++){	
		no=(rand()+1)%m;
		if(no==0)
			no++;
		insertEdgesInto_alist(m,no,100);	
	}
}	

void create_all_edges(int total_vertex,int probability)
{
	int i=0,j=0;
	// creation of random edges
	for(i=1;i<total_vertex;i++){
		for(j=1;j<total_vertex;j++){
			// This will insert edges into graph and correspomding entry in alist
			if(i!=j)		
				insertEdgesInto_alist(i,j,probability);
			//if(edge==459)
				//return;
		}
	}// end of Outer for loop
}

void display_alist(int n1)
{
	int i=0,j=0;
	struct node *p;
	for(i=0;i<n1;i++){	
		p=alist[i];
		printf("\n alist[%d] :: ",i);
		if(p!=NULL)
			p=p->next;

		while(p!=NULL){				
			printf(" %s,%d | ",p->label,p->edge_wt);
			p=p->next;
		}
	}
		printf("\n\n");
}


/* old dfs visit
void dfs_visit(int u,int tempW,int totalNoOfNodes)
{
	struct node *tempNode, *temp, *p, *start;
	int tempNodeNumber=0,i=1, tempWeight=0;

	alist[u]->colour=2;	// gray=2
	time++;
	alist[u]->discover_time = time;
	
			
		temp = alist[u]->next;
		while(temp!=NULL)
		{
			tempNodeNumber = atoi(temp->label);
			tempWeight = temp->edge_wt;
			if(alist[tempNodeNumber]->colour==1)	//white=1
			{
				alist[tempNodeNumber]->previousInDFS = u;
				dfs_visit(tempNodeNumber,tempWeight,totalNoOfNodes);
			}
			temp = temp->next;
		}

		alist[u]->finish_time = time++;
		alist[u]->colour=3;	//black=3

		// Adding node 'u'  entry into the link-list of nodes (who belong to same tree) 
		// to track back DFS
/ *
		if(trackList[currentRootId] != NULL)
		{
			tempNode = trackList[currentRootId]->next;
			trackList[currentRootId]->next = create_node(100);
			// we have to add weight also to identify exact edge
			//trackList[currentRootId]->edge_wt =  


			itoa(u, trackList[currentRootId]->next->label, 10);

			trackList[currentRootId]->next->next = tempNode;	
		}
* /
		
		
		start = trackList[currentRootId];
		if(start != NULL)
		{
			p = create_node(100);
			p->edge_wt=tempW;
			//itoa(u,p->label,10);
			sprintf(p->label,"%d",u);
			p->next = start->next;
			start->next = p;
		}	
	//}
}
*/

/* old dfs
void dfs(int totalNoOfNodes)
{
	int i = 1, u = 1;	
		
	// initialize track array to total_no_of_nodes
	rootListInitialize(totalNoOfNodes);
 	
	// Initialize all nodes of alist
	for(i=1; i<totalNoOfNodes; i++)
	{
		alist[i]->colour = 1;
		alist[i]->predessor=NULL;
		alist[i]->previousInDFS=0;
	}
	time=0;

	for(u=1; u<totalNoOfNodes; u++)
	{
		if(alist[u]->colour==1)	//	white=1
		{
			currentRootId=u;
			// Set the flag of rootList[currentRootId] to indicate root presence
			rootList[currentRootId] = 1;

			trackList[currentRootId] = create_node(100);
			//itoa(currentRootId, trackList[currentRootId]->label, 10);
			sprintf(trackList[currentRootId]->label,"%d",currentRootId);
			dfs_visit(u,alist[u]->edge_wt,totalNoOfNodes);
		}
	}

}
*/

void sortPriorityNodeList_usingFinishTime(int totalNoOfNodes)
{
	struct node *tempArray[totalNoOfNodes];
	struct node *tempNode;
	
	// Copy the label and finish time in tempArray
	for(i=1;i<totalNoOfNodes;i++){
		tempArray[i]=create_node(100);
		// strcpy(dest,src);
		strcpy(tempArray[i]->label,alist[i]->label);
		tempArray[i]->finish_time = alist[i]->finish_time;
	}

	// Sorting tempArray using bubble sort
	for(k=1;k<totalNoOfNodes;k++){
		for(i=1;i<totalNoOfNodes-1;i++){
			if(tempArray[i]->finish_time < tempArray[i+1]->finish_time){
					//swap(tempArray[i],tempArray[i+1])
					tempNode=tempArray[i];
					tempArray[i]=tempArray[i+1];
					tempArray[i+1]=tempNode;
			}
		}
	}
	//recently removed-1
	//printf("\n\n =====================================================Displaying tempArray \n\n");
	for(i=1;i<totalNoOfNodes;i++){
		//recently removed-1
		//printf("\n tempArray[%s] = %d",tempArray[i]->label,tempArray[i]->finish_time);
	}
	
	for(i=1;i<totalNoOfNodes;i++){
		priorityNodeList[i] = atoi(tempArray[i]->label);
	}
}

//needed after the transpose function
void modified_insertEdgesInto_alist_transpose(int i,int j,int randomWt)
{
	struct node *p,*q;
	int k=0,temp_num=0;
	int flag=0,entry1=0;

		// Making an entry of edge(i,j) into alist[i]
		p=alist[i];
		while(flag==0 && (p->next!=NULL)){		
			temp_num=atoi(p->next->label);
			if(temp_num!=j)	//if(p->next->label!=j)		
				p=p->next;
			else
				flag=1;	// edge (i,j) already exists
		}	
		if(flag==0){		/* if flag=0 means (i,j) does not exists, so add (i,j)*/
			//x_co_ordinate=i;
			//y_co_ordinate=atoi(alist[j]->label);

			//if (transpose_matrix[x_co_ordinate][y_co_ordinate]!=0 || transpose_matrix[y_co_ordinate][x_co_ordinate]!=0){
			if(p!=NULL){
				p->next=create_node(100);
				p->next->label=alist[j]->label;
				p->next->edge_wt=randomWt;
				entry1=1;
				//transpose_matrix[x_co_ordinate][y_co_ordinate]=randomWt;
				edge++;
			}
		}	
}

void userInput_create_all_edges(int total_vertex)
{
//	int i=1,j=1;
	int i=0,j=0,readValueFromTransposeMatrix=0,a=0,b=0,tempNoOfNodes=0,tempEdges=0;
	struct node *p;
	FILE *fp;
	fp=fopen("userInput.adj","r");
	fscanf(fp,"%d %d",&tempNoOfNodes,&tempEdges);
	fscanf(fp,"\n");
	// creatio	n of random edges
	for(i=0;i<tempEdges;i++){
		//for(j=1;j<total_vertex;j++){// This will insert edges into graph and corresponding entry in alist
			//if(i!=j && matrix[i][j]!=0)		
			//if(transpose_matrix[i][j]!=0)		// Self loop allowed
			//while(fp!=NULL){
				fscanf(fp,"%d %d %d",&(a),&(b),&readValueFromTransposeMatrix);
				if(readValueFromTransposeMatrix!=0)
					modified_insertEdgesInto_alist_transpose(a,b,readValueFromTransposeMatrix);
				fscanf(fp,"\n");	
			//}		
		//}
	}// end of for loop
	fclose(fp);
}

void modified_create_all_edges_transpose(int total_vertex)
{
//	int i=1,j=1;
	int i=0,j=0,readValueFromTransposeMatrix=0,a=0,b=0,tempNoOfNodes=0,tempEdges=0;
	struct node *p;
	FILE *fp;
	fp=fopen("transpose.adj","r");
	fscanf(fp,"%d %d",&tempNoOfNodes,&tempEdges);
	fscanf(fp,"\n");
	// creatio	n of random edges
	for(i=0;i<tempEdges;i++){
		//for(j=1;j<total_vertex;j++){// This will insert edges into graph and corresponding entry in alist
			//if(i!=j && matrix[i][j]!=0)		
			//if(transpose_matrix[i][j]!=0)		// Self loop allowed
			//while(fp!=NULL){
				fscanf(fp,"%d %d %d",&(a),&(b),&readValueFromTransposeMatrix);
				if(readValueFromTransposeMatrix!=0)
					modified_insertEdgesInto_alist_transpose(a,b,readValueFromTransposeMatrix);
				fscanf(fp,"\n");	
			//}		
		//}
	}// end of for loop
	fclose(fp);
}

void display_priorityNodeList(int totalNoOfNodes)
{
	printf("\n\n Displaying priorityNodeList \n\n");
	for(i=1;i<totalNoOfNodes;i++){
		printf("\n priorityNodeList[%d] = %d",i,priorityNodeList[i]);
	}
}

void displayDFS(int totalNoOfNodes)
{
	int i=0;
	struct node *tempNode;

	//recently removed-1
	//printf("\n\n Displaying the DFS list \n");
	for(i=0; i<totalNoOfNodes; i++)
	{
		//recently removed-1
		//printf("\n\n  TrackList [%d] ## ",i);
		if(rootList[i]==1){
			tempNode = trackList[i];	
			//printf("%s ## ",tempNode->label);
			tempNode = tempNode->next;
	
				while(tempNode!=NULL){
					//recently removed-1
					//printf(" %s,%d :",tempNode->label,tempNode->edge_wt);
					tempNode = tempNode->next;
					trackList[i]->countBiconnectedVertex++;
				}
		}
	}
}

/* old displayDFS
void displayDFS(int totalNoOfNodes)
{
	int i=0;
	struct node *tempNode;

	printf("\n\n Displaying the DFS list \n\n");
	for(i=0; i<totalNoOfNodes; i++)
	{
		printf("\n\n  TrackList [%d] ## ",i);
		if(rootList[i]==1)
		{

			tempNode = trackList[i];	
			//printf("%s ## ",tempNode->label);
			tempNode = tempNode->next;
			while(tempNode!=NULL)
			{
				printf(" %s,%d :",tempNode->label,tempNode->edge_wt);
				tempNode = tempNode->next;
			}

		}
	}

}
*/


/* old dispay_Matrix
void dispay_Matrix(int totalNoOfNodes)
{
	int i=1,j=1;
	for(i=1;i<totalNoOfNodes;i++)
	{
		for(j=1;j<totalNoOfNodes;j++)
			//printf("\t %d",matrix[i][j]);
		printf("\n");
	}
}
*/

void displayFinishTime(int totalNoOfNodes)
{
	int i=1;
	printf("\n\n \t Finish time of all nodes \n\n ");
	printf("\n\t Start time \t Finish time \n");
	for(i=1;i<totalNoOfNodes;i++)
		printf("\n alist[%d]: %d \t\t %d",i,alist[i]->discover_time,alist[i]->finish_time);
}

/* old store_matrix
void store_Matrix(int totalNoOfNodes)
{
	int i=1,j=1;
	FILE *fp;
	fp=fopen("matrix_output.adj","w");

		for(i=1;i<totalNoOfNodes;i++)
		{
			for(j=1;j<totalNoOfNodes;j++)
				//fprintf(fp,"\t %d",matrix[i][j]);
			fprintf(fp,"\n");
		}
	fclose(fp);	
}
*/

void storeVizGraphPartA(int totalNoOfNodes)
{
	/*	This function would do similar functionality as we defined for version 3.1	
	 * 	Storing the output in a file, so we can reuse the function defined for 3.1 
	 */
	int i=0,j=0;
	struct node *p;
	FILE *fp;

	fp=fopen("vizGraphOutputPartA.dot","w");
	fprintf(fp,"digraph G {\n ");

	for(i=1;i<totalNoOfNodes;i++){	
		p=alist[i];
		//printf("\n alist[%d] :: ",i);
		if(p!=NULL)
			p=p->next;
		
		while(p!=NULL){
			j=atoi(p->label);
			//fprintf(fp,"\n%d %d",(j),(i));
			// the i,j order is reversed because we are using transposed input.
			fprintf(fp,"%d -> %d; ",j,i);	
			//printf(" %s,%d | ",p->label,p->edge_wt);
			p=p->next;
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"}\n");
	fclose(fp);	
}

void storeVizGraphPartB(int totalNoOfNodes)
{
	/*	This function would do similar functionality as we defined for version 3.1	
	 * 	Storing the output in a file, so we can reuse the function defined for 3.1 
	 */
	int i=0,j=0;
	struct node *p;
	FILE *fp;

	fp=fopen("vizGraphOutputPartB.dot","w");
	fprintf(fp,"digraph G {\n");

	for(i=0;i<totalNoOfNodes;i++){	
		p=alist[i];
		//printf("\n alist[%d] :: ",i);
		if(p!=NULL)
			p=p->next;
		
		while(p!=NULL){
			j=atoi(p->label);
			//fprintf(fp,"\n%d %d",(j),(i));
			// the i,j order is reversed because we are using transposed input.
			fprintf(fp,"%d -> %d; ",(j-1),i-1);	
			//printf(" %s,%d | ",p->label,p->edge_wt);
			p=p->next;
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"}\n");
	fclose(fp);	
}

void storeInputForPartB(int totalNoOfNodes)
{
	int i=0,j=0;
	struct node *p;
	FILE *fp;
	fp=fopen("inputPartB.adj","w");
	fprintf(fp,"%d",totalNoOfNodes-1);

	for(i=0;i<totalNoOfNodes;i++){	
		p=alist[i];
		//printf("\n alist[%d] :: ",i);
		if(p!=NULL)
			p=p->next;
		while(p!=NULL){
			j=atoi(p->label);
			// the i,j order is reversed because we are using transposed input.
			fprintf(fp,"\n%d %d",(j-1),(i-1));	
			//printf(" %s,%d | ",p->label,p->edge_wt);
			p=p->next;
		}
	}
		//printf("\n\n");
		/*
		for(i=1;i<totalNoOfNodes;i++)
		{
			for(j=1;j<totalNoOfNodes;j++)
			{
				if(matrix[i][j]!=0)
					fprintf(fp,"\n%d %d",(i-1),(j-1));
			}
			//fprintf(fp,"\n");
		} */
	fclose(fp);	
}

int main(int argc, char *argv[]) // minimal Connected removed    
{
	
	int i=0,j=0,z=0;
	int total_vertex=0,total_edges=0;
	int probability=30;
	struct timeval earlier;
	struct timeval later;
	struct timeval interval;
	long long int tempDiff1;
	FILE *fpReadings;
	fpReadings=fopen("readings.txt","a");

	

	total_vertex=atoi(argv[1]);
	probability=atoi(argv[2]);
	printf("\nEnter the total no of vertices in the graph : %d",total_vertex);
	printf("\n Enter density (i.e. probability in percentage): %d ",probability);	
	
	/*
	printf("\nEnter the total no of vertices in the graph : ");
	scanf("%d",&total_vertex);
	printf("\n Enter density (i.e. probability in percentage) : ");
	scanf("%d",&probability);
	*/
	total_vertex++;

	//Initialising all vertices 
	create_all_vertices(total_vertex);

	// Initialize priorityNodeList
	initializePriorityNodeList(total_vertex);

	// minimal connected graph
	//minimal_connected(total_vertex);

	/*	You can choose Method1 or Method2, but not both at the same time
	 * 	Comment out the method as per your need	*/

	/*	Method1:- It contains Function-1 & Function-2 to create a graph according 
	 * 	to user specified input in "userInput.adj" file. */
	 /* Function-1: To reset the adjecancy list (alist re-initialize) */ 
	//reset_alist(total_vertex);
	/*  Function-2: Re-adjust the alist according to userInput.adj	 */
	//userInput_create_all_edges(total_vertex);
	
	/* Method2:- It will generate a random graph.	*/
	create_all_edges(total_vertex,probability);

	// displaying priorityNodeList list
	//recently removed-1
	//display_priorityNodeList(total_vertex);


	// display Nodes List
	//recently removed-1
	//display_alist(total_vertex);

	 if(gettimeofday(&earlier,NULL)){
		perror("first gettimeofday()");
		exit(1);
	  }

	// calling dfs function
	dfs(total_vertex);

	/* Computing the transpose of original matrix and storing it in transpose.adj
	 * Original	: Adjecancy list
	 * Tranposed: transpose.adj	*/
	computeTransposeAndStoreIt(total_vertex);
	
	// DFS list To Calculate time
	//displayDFS(total_vertex);

	// finishing time of nodes To Calculate time
	//displayFinishTime(total_vertex);

	// sorting vertex
	sortPriorityNodeList_usingFinishTime(total_vertex);
	
	// priorityNodeList list To Calculate time
	//display_priorityNodeList(total_vertex);

	/*---Changes during 5.1----------------------------------*/
	// alist re-initialize
	reset_alist(total_vertex);
	
	// Re-adjust the alist according to transpose matrix
	modified_create_all_edges_transpose(total_vertex);

	// Nodes List after transpose
	//display_alist(total_vertex);

	// dfs function for transpose matrix input
	dfs(total_vertex);

	 if(gettimeofday(&later,NULL)){
		perror("second gettimeofday()");
		exit(1);
	  }

	// DFS list for transpose matrix input
	//recently removed-1
	displayDFS(total_vertex);

	/* --------Changes during 6.1----------------------------------------------------*/
	// vizImage file (for Graphical Vizualization)
	//recently removed-1
	//storeVizGraphPartA(total_vertex);
	
	//For partB  vizImage file (for Graphical Vizualization)
	//recently removed-1
	//storeVizGraphPartB(total_vertex);
	
	// input for part B
	//recently removed-1
	//storeInputForPartB(total_vertex);
	
	// display the matrix array
	//dispay_Matrix(total_vertex);

	// Store matrix in file
	// store_Matrix(total_vertex);

	// Store another input for part B method(java)
	// storeInputForPartB(total_vertex);
	
	// Store input for part A in adjecancy matrix	
	//storePartA(total_vertex);
	
	// calling dfs function
	//dfs(total_vertex);

	// displaying DFS list
	//displayDFS(total_vertex);

	
	for(z=1;z<total_vertex;z++){
		if(rootList[z]==1 && trackList[z]->countBiconnectedVertex>=2){
			//recently removed-1
			//printf("\n root[%d]= %d, trackList[%d]->countBiconnectedVertex=%d ",z,rootList[z],z,trackList[z]->countBiconnectedVertex);//
			totalSCC++;
		}
	}

	tempDiff1= (timeval_diff(NULL,&later,&earlier));
	//recently removed-1
	//printf("\n Total vertex=%d \n Total edges=%d \n Density=%f",total_vertex-1,edge-1,( (float)(edge)/total_vertex/(total_vertex-1)*100 ));
	//printf("\n\n Difference is %lld milliseconds\n",(timeval_diff(NULL,&later,&earlier)));
	printf("\n\n temp=%lld , diff=%lld \n\n  totalSCC=%d \n\n",tempDiff1,(timeval_diff(NULL,&later,&earlier)),totalSCC);
	
	//fprintf(fpReadings," Node Edges Density Time ");

	
	fprintf(fpReadings,"%d %lld %d\n",total_vertex-1,tempDiff1/1000,totalSCC);
	fclose(fpReadings);
	return 0;
}

