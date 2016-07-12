#include "header.h"
#include "pthread.h"

int ball_flag[4]={1,1,1,1},player1_life[4]={3,3,3,3};
GLsizei g_width = 600;
GLsizei g_height = 600;
const float DEG2RAD = 3.14159/180;

float radius=4,x,y;
GLint circle_points = 1000;
double angle;
static int ball_angle=0;

int xf[5],yf[5];
float dx[5],xstep[5];
float dy[5],ystep[5];
char ch;

float p1[]={-15,-90,20,-95},p2[]={90,-15,95,20},p3[]={-15,90,20,95},p4[]={-90,-15,-95,20};
float xb2=25,yb2=-13;	// 1st ball
float xb3=50,yb3=-5;	// 2nd ball
float xb4=-5,yb4=-50;	// 3rd ball
char array[6][7],buf1[1000],buf2[1000],ip_addr[20],packet_data1[1000],packet_data2[1000];	
int i=0,sockfd2,numbytes;
static int c=0,j=0;
struct sockaddr_in my_addr;
struct sockaddr_in client_addr,client_addr1[4];
socklen_t addr_len;

float total_players=1,no_of_balls=1.0;

float m1=0.000000,m2=0.000000;

int player_id=1,life_status[4]={1,1,1,1},dead_flag[4]={0,0,0,0};

int active=0,no_of_literals=0;
float dead_player=7;


/* fill_data_packet() */
void fill_data_packet(char temp2[1000])
{
  sprintf(temp2,"%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f_%f",no_of_balls+50,total_players,p1[0],p1[1],p1[2],p1[3],p2[0],p2[1],p2[2],p2[3],p3[0],p3[1],p3[2],p3[3],p4[0],p4[1],p4[2],p4[3],xb2,yb2,xb3,yb3,xb4,yb4,dead_player);

}

/* initial_values() */
void initial_values()
{
  for(i=0;i<5;i++)
  {
    xf[i]=1;
    yf[i]=1;
    dx[i]=a1;
    dy[i]=b1;
    xstep[i]=a1;
    ystep[i]=b1;
  }
}

/*kill_it()*/
void kill_it(int pid)
{
  char ch[2];
  int kill_sig=9;

  sprintf(ch,"%d",kill_sig);

  // ** Send function for Sending Game state( PAddle + Ball Co-ordinates)  to server **
  if((numbytes = sendto(sockfd2, ch, strlen(ch), 0,(struct sockaddr *)&client_addr1[pid-1], sizeof(struct sockaddr))) == -1) 	{
    perror("Client-sendto() error lol!");
    //exit(1);
  }
  else {
    printf("Client-sendto() is OK...\n");
  }
}

/* save_game_state_variable() */
void save_game_state_variables()
{
  int val;
  //printf("\n\n \t save variable fun\n\n");

  m1=atof(array[0]);		
  player_id=(int)m1;	// 1 2 3 4 

  m2=atof(array[5]);
  life_status[player_id-1]=(int)m2;

  val==(int)m2;


  if(life_status[player_id-1]==0) {
    dead_player=player_id;	// 1 2  3 4 
  }	

  printf("\ndead+man :%f \n player-id=%d \t life_status[%d]=%d",dead_player,player_id,player_id-1,life_status[player_id-1]);

  for(c=1,j=0;c<5;c++,j++) {

    if(player_id==1) {
      p1[j]=atof(array[c]);
      //printf("\np1[%d]=%f array[%d]=%s",j,p1[j],c,array[c]);
    }

    if(player_id==2) {
      p2[j]=atof(array[c]);
    }

    if(player_id==3) {
      p3[j]=atof(array[c]); 
    }

    if(player_id==4) {
      p4[j]=atof(array[c]); 
    }

  }//for-end
} 

/* extract_data_packet() */
int extract_data_packet (char temp1[1000])
{ 
  char *pch,str1[1000];
  int i=0;
  strcpy(str1,temp1);
  printf("\n\n \t  str1=%s@@@ \n\n",str1);

  no_of_literals=0;
  pch = strtok (str1,"_");

  //for(i=0;i<6;i++)
  while(pch!=NULL)	{
    strcpy(array[i],pch);	
    no_of_literals++;
    pch = strtok (NULL,"_");
    //printf("\n\n array[%d]=%s\n",i,array[i]);

    array[i][6]='\0';	 
    i++;
  }

  return 0;
}

/* timer_2() */
void timer_2()
{
  xb2=xstep[2];
  yb2=ystep[2];

  // Handling Outer bound of Ball 1 for X-coordinate 
  if(xb2-4>-90 && xf[2]==1) {
    xf[2]=1; 
    dx[2]=-(a1);
  }
  else{ 
    xf[2]=0;
  }

  if(xb2+4<=90 && xf[2]==0){
    dx[2]=a1;
  }
  else{
    xf[2]=1;
  }

  //Resetting xb2 
  xstep[2]+=dx[2];	

  // Handling Outer bound of Ball 1 for Y-coordinate 
  if(yb2-4>-90 && yf[2]==1) {
    yf[2]=1;
    dy[2]=-(b1);
  }
  else{
    yf[2]=0;
  }

  if(yb2+4<=90 && yf[2]==0){
    dy[2]=b1;
  }
  else{
    yf[2]=1;
  }

  //Resetting xb2
  ystep[2]+=dy[2];

  // check_life1();
  // check_life2();
  // check_life3();
  // check_life4();
  // printf("\n\n %d \t %d\t %d\t %d\t  ",player1_life[0],player1_life[1],player1_life[2],player1_life[3]);	
}

/* timer_3() */ 
void timer_3()
{
  xb3=xstep[3];
  yb3=ystep[3];

  // Handling Outer bound of Ball 1 for X-coordinate 
  if(xb3-4>-90 && xf[3]==1) {
    xf[3]=1;
    dx[3]=-(a2);
  }
  else{
    xf[3]=0;
  }

  if(xb3+4<=90 && xf[3]==0){
    dx[3]=a2;
  }
  else{
    xf[3]=1;
  }

  //Resetting xb2 
  xstep[3]+=dx[3];

  // Handling Outer bound of Ball 1 for Y-coordinate 
  if(yb3-4>-90 && yf[3]==1) {
    yf[3]=1;
    dy[3]=-(b2);
  }
  else{
    yf[3]=0;
  }

  if(yb3+4<=90 && yf[3]==0){
    dy[3]=b2;
  }
  else{
    yf[3]=1;
  }

  //Resetting xb2
  ystep[3]+=dy[3];

  //check_life1();
  //check_life2();
  //check_life3();
  //check_life4();
  //printf("\n\n %d \t %d\t %d\t %d\t  ",player1_life[0],player1_life[1],player1_life[2],player1_life[3]);	
}

/* timer_4() */
void timer_4()
{
  xb4=xstep[4];
  yb4=ystep[4];

  // Handling Outer bound of Ball 1 for X-coordinate 
  if(xb4-4>-90 && xf[4]==1) {
    xf[4]=1; 
    dx[4]=-(a3);
  }
  else{ 
    xf[4]=0;
  }

  if(xb4+4<=90 && xf[4]==0){
    dx[4]=a3;
  }
  else{
    xf[4]=1;
  }

  //Resetting xb2 
  xstep[4]+=dx[4];	


  // Handling Outer bound of Ball 1 for Y-coordinate 
  if(yb4-4>-90 && yf[4]==1) {
    yf[4]=1;
    dy[4]=-(b3);
  }
  else{
    yf[4]=0;
  }

  if(yb4+4<=90 && yf[4]==0){
    dy[4]=b3;
  }
  else{
    yf[4]=1;
  }

  //Resetting xb2
  ystep[4]+=dy[4];

  //check_life1();
  //check_life2();
  //check_life3();
  //check_life4();
  //printf("\n\n %d \t %d\t %d\t %d\t  ",player1_life[0],player1_life[1],player1_life[2],player1_life[3]);	
}

/* assign_id() */
int assign_id()
{
  char ch[2];
  int k2=0;

  for(k2=0;k2<total_players;k2++) {	

    if((numbytes = recvfrom(sockfd2, buf1, MAXBUFLEN-1, 0, (struct sockaddr *)&client_addr, &addr_len)) == -1) {
      perror("Server-recvfrom() error lol!");
      /*If something wrong, just exit lol...*/
      //exit(1);
    }
    else {
      buf1[strlen(buf1)]='\0';
      //printf("Server-Waiting and listening...\n");
      //printf("Server-recvfrom() is OK...\n");
    }

    client_addr1[k2]=client_addr;	
    sprintf(ch,"%d",k2+1);

    /* Send function for Sending Game state( PAddle + Ball Co-ordinates)  to server */
    if((numbytes = sendto(sockfd2, ch, strlen(ch), 0,(struct sockaddr *)&client_addr1[k2], sizeof(struct sockaddr))) == -1) {
      perror("Client-sendto() error lol!");
      //exit(1);
    }
    else{
      printf("Client-sendto() is OK...\n");
    }
  }//for-end	

  return 0;
}

/* server_function() */
int server_function(char packet_data1[1000])
{

  if((numbytes = recvfrom(sockfd2, buf1, MAXBUFLEN-1, 0, (struct sockaddr *)&client_addr, &addr_len)) == -1) {
    perror("Server-recvfrom() error lol!");
    /*If something wrong, just exit lol...*/
    //exit(1);
  }
  else { 
    buf1[strlen(buf1)]='\0';
    //printf("Server-Waiting and listening...\n");
    //printf("Server-recvfrom() is OK...\n");
  }

  //printf("Server-Got packet from %s\n", inet_ntoa(client_addr.sin_addr));
  //printf("Server-Packet is %d bytes long\n", numbytes);
  buf1[numbytes] = '\0';
  //printf("Server-Packet contains \"%s\"\n", buf1);

  // ** store dat into packet_data **
  strcpy(packet_data1,buf1); 
  return numbytes;
}

/* declare_winner() */
void declare_winner()
{
  int i=0;

  for(i=0;i<total_players;i++) {

    if(life_status[i]==1) {
      printf("Winner : player-%d",i+1);
      exit(1);
    }
  }//for-end
}

/* client_function() */
int client_function(char argv[20],char packet_data2[1000])
{

  int k1=0,f1=0;

  for(k1=0;k1<total_players;k1++) {
    /* Send function for Sending Game state( PAddle + Ball Co-ordinates)  to server */
    if((numbytes = sendto(sockfd2, packet_data2, strlen(packet_data2), 0, 
            (struct sockaddr *)&client_addr1[k1], sizeof(struct sockaddr))) == -1){
      perror("Client-sendto() error lol!");
      //exit(1);
    }
    else {
      //printf("\n life_status[%d]=%d: \n",player_id,life_status[0]);
    }
    /*else if(life_status[k1]==0)
      { 

      for(f1=0;f1<total_players;f1++)
      {	
      if(f1!=k1)
      {				
      packet_data2[0]=(char)k1;
      packet_data2[1]='\0';
      sendto(sockfd2, packet_data2, strlen(packet_data2), 0,(struct sockaddr *)&client_addr1[f1], sizeof(struct sockaddr));
      printf("\n\nhello Pack_data=%s f1=%d k1=%d \n\n",packet_data2,f1,k1);
      }
      }

      active--;
      if(active==1)
      declare_winner();
    //dead_flag[k1]=1;
    }*/

  }//for-end

  return 0;
}

/* receive_1() */

void* receive_1(void *data)
{
  int count1=0,size1=0;
  for(count1=0; ; count1++) {		

    size1=server_function(packet_data1);

    if(size1<150) {
      extract_data_packet(packet_data1);
      if(no_of_literals>=6)
        save_game_state_variables();
    }

    printf("\n \ntotal_players_players=%f \tlife_status[%d]=%d  %d %d %d \n \tdead_flag[0]=%d %d %d %d \n\n  ", total_players, (player_id-1), life_status[0], life_status[1], life_status[2], life_status[3], dead_flag[0], dead_flag[1], dead_flag[2], dead_flag[3]);	
    usleep(10000);	
  }//for-end
}

/* send_1() */
void* send_1(void *data)
{
  int count2=0;

  for(count2=0;;count2++) {		
    //xb2+=10.0;
    //yb2+=10.0;

    timer_2();
    timer_3();
    timer_4();

    //	2 lines
    fill_data_packet(packet_data2);
    client_function(ip_addr,packet_data2);
    usleep(10000);	
  }//for-end

}

/* control() */
void control()
{
  pthread_t sender_thread,receiver_thread;

  pthread_create(&receiver_thread,NULL,&receive_1,NULL);
  pthread_create(&sender_thread,NULL,&send_1,NULL);

  //pthread_join(receiver_thread,NULL);
  //pthread_join(sender_thread,NULL);

}

/* begin() */
void begin()
{
  if((sockfd2 = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("Server-socket() sockfd2 error lol!");
    //exit(1);
  }
  else{
    //printf("Server-socket() sockfd2 is OK...\n");
  }

  /* host byte order */
  my_addr.sin_family = AF_INET;

  /* short, network byte order */
  my_addr.sin_port = htons(MYPORT);

  /* automatically fill with my IP */
  my_addr.sin_addr.s_addr = INADDR_ANY;

  /* zero the rest of the struct */
  memset(&(my_addr.sin_zero), '\0', 8);

  if(bind(sockfd2, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
    perror("Server-bind() error lol!");
    //exit(1);
  }
  else{
    //printf("Server-bind() is OK...\n");
  }

  addr_len= sizeof(struct sockaddr);
  assign_id();

  /* 3 lines */
  server_function(packet_data1);
  extract_data_packet(packet_data1);
  save_game_state_variables();

}

/* basic_input() */
void basic_input()
{
  printf("\n Enter 's' for SINGLE PC GAME \n or Enter 'n' for playing over the network.");
  scanf("%c",&ch);

  switch(ch) {
    case 's':	printf("\nEnter the no of players :");
              scanf("%f",&total_players);
              printf("\nEnter the no of balls:");
              scanf("%f",&no_of_balls);
              break;

    case 'n':	printf("\nEnter the no of players :");
              scanf("%f",&total_players);
              printf("\nEnter the no of balls:");
              scanf("%f",&no_of_balls);
              break;
  };

  active=total_players; 

}

/* main function() */
int main()
{

  initial_values();
  basic_input();

  begin();
  control();

  /* infinite loop */
  for( ; ; ) {
    usleep(10000);
  }

  if(close(sockfd2) != 0){
    printf("Server-sockfd2 closing failed!\n");
  }
  else{
    printf("Server-sockfd2 successfully closed!\n");
  }

  return 0;
}

