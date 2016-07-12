#include "header.h"
#include <stdbool.h>
#include <pthread.h>

void timer();
void reshape( GLsizei width, GLsizei height );
//void draw_circle();
void draw_circle(float h,float k);
void display(void);
void init();
void glutIdleFunc(void (*func)(void));
void keyPressed (unsigned char key, int x, int y); 
void keyUp (unsigned char key, int x, int y);
void keySpecialOperations(void);
void keySpecialUp (int key, int x, int y);
void keySpecial (int key, int x, int y);
void check_life1();

char name_of_window[20]="PING-PONG";
int xf1=0,yf1=0;
GLsizei g_width = 600;
GLsizei g_height = 600;
const float DEG2RAD = 3.14159/180;

float radius=4,x,y;
GLint circle_points = 500; 
double angle;
static int ball_angle=0;

float dx1=a1,xStep1=a1;
float dy1=b1,yStep1=b1;

//Key Operations
//bool *keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)  
bool keySpecialStates[246]; // Create an array of boolean values of length 256 (0-255)  

int flag1=0,start=0;
int ball_flag[12]={1,1,1,1,1,1,1,1,1,1,1,1 };

float p1[]={-15,-90,20,-95},p2[]={90,-15,95,20},p3[]={-15,90,20,95},p4[]={-90,-15,-95,20};
float xb1=25.000000,yb1=-45.000000;
float xb2=-25.000000,yb2=-13.000000;	// 1st ball
float xb3=50.000000,yb3=-5.000000;	// 2nd ball

int sockfd1,numbytes,i=0;
static int c=0,j=0;	
char buf[1000],packet_data[1000],ip_addr[20],array[26][10];
socklen_t addr_len;
struct sockaddr_in server_addr;
struct hostent *he;

pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;

int total_players=1,no_of_balls=1;
int player_id=11;
int no_of_literals=1;;

int player_life[4]={5,5,5,5},life_status[4]={1,1,1,1},dead_flag[4]={0,0,0,0};
int sig=0;
float y11=0.0;
int dead_player=0;

char l1[4],l2[4],l3[4],l4[4];

void calculate()
{

}

void fill_data_packet(char temp[1000])
{
  if(player_id==1) {
    sprintf(temp,"%d_%f_%f_%f_%f_%d",player_id,p1[0],p1[1],p1[2],p1[3],life_status[0]);
  } 
  else if(player_id==2) {
    sprintf(temp,"%d_%f_%f_%f_%f_%d",player_id,p2[0],p2[1],p2[2],p2[3],life_status[1]);
  }
  else if(player_id==3) {
    sprintf(temp,"%d_%f_%f_%f_%f_%d",player_id,p3[0],p3[1],p3[2],p3[3],life_status[2]);
  }
  else if(player_id==4) {
    sprintf(temp,"%d_%f_%f_%f_%f_%d",player_id,p4[0],p4[1],p4[2],p4[3],life_status[3]);
  }

  printf("\n\ntemp :%s \n ",temp);

}

int extract_data_packet (char temp[1000])
{ 
  char *pch,str1[1000];
  int i=0;
  strcpy(str1,temp);
  //printf("\n\n \t  str1=%s@@@ \n\n",str1);

  pch = strtok (str1,"_");

  i=0;
  //for(i=0;i<24;i++)

  while(pch!=NULL)	{
    strcpy(array[i],pch);	
    pch = strtok (NULL,"_");
    no_of_literals++;
    //printf("\n\n array[%d]=%s\n",i,array[i]);
    array[i][6]='\0';	 
    i++;	
  }
  return 0;

}

void end()
{
  char id[2];
  int kill_sig;

  if(life_status[player_id-1]==0) {	
    if((numbytes = recvfrom(sockfd1, id, 2, 0, (struct sockaddr *)&server_addr, &addr_len)) == -1) {
      perror("Server-recvfrom() error lol!");
      /*If something wrong, just exit lol...*/
      //exit(1);
    }
    else { 
      id[strlen(id)]='\0';
    }

    id[numbytes] = '\0';
    kill_sig=atoi(id);

    if(kill_sig==9) {
      printf("\n Player %d ... You lost the game\n",player_id);
      exit(1);
    }
  }//if-outer-end
}

void check_life1()
{
  if((yb1-7<=-90 && (xb1<p1[0] || xb1>p1[2])) && ball_flag[0]==1) {
    player_life[0]--;
    ball_flag[0]=0;			
  }	

  if(yb2-7<=-90 && (xb2<p1[0] || xb2>p1[2]) &&(ball_flag[1]==1)) {
    player_life[0]--;
    ball_flag[1]=0;
  }

  if(yb3-7<=-90 && (xb3<p1[0] || xb3>p1[2])  && ball_flag[2]==1) {
    player_life[0]--;
    ball_flag[2]=0;		
  }

  /*
  if(yb4-7<=-90 && (xb4<p1[0] || xb4>p1[2])  && ball_flag[3]==1  )
  {
    player_life[0]--;
    ball_flag[3]=0;
  }
  */	

  if(player_life[0]<=0)	{
    life_status[0]=0;
    //usleep(5000);
    end();			
  }

  if((yb1-7) > -90) 
    ball_flag[0]=1;

  if(yb2-7>-90)
    ball_flag[1]=1;	

  if(yb3-7>-90)
    ball_flag[2]=1;

  //if(yb4-7>-90)
  //	ball_flag[3]=1;

  //usleep(100);

}

void check_life2()
{
  if((xb1+7>=90 && (yb1<p2[1] || yb1>p2[3])) && ball_flag[3]==1) {
    player_life[1]--;
    ball_flag[3]=0;			
  }	

  if((xb2+7>=90 && (yb2<p2[1] || yb2>p2[3])) && ball_flag[4]==1) {
    player_life[1]--;
    ball_flag[4]=0;			
  }	


  if((xb3+7>=90 && (yb3<p2[1] || yb3>p2[3])) && ball_flag[5]==1) {
    player_life[1]--;
    ball_flag[5]=0;			
  }	

  /*
  if((xb4+7>=90 && (yb4<p2[1] || yb4>p2[3])) && ball_flag[3]==1)
  {
    player_life[1]--;
    ball_flag[3]=0;			
  }	
  */

  if(player_life[1]==0)	{
    life_status[1]=0;	
    //end();	
  }

  if((xb1+7) < 90)
    ball_flag[3]=1;

  if((xb2+7) < 90)
    ball_flag[4]=1;

  if((xb3+7) < 90)
    ball_flag[5]=1;

  /*
  if(xb4+7<90)
    ball_flag[3]=1;
  */

}

void check_life3()
{

  //////printf("\n\n \n xb2=%f,yb2=%f,p3[0]=%f,p3[2]=%f \n\n ",xb2,yb2,p3[0],p3[2]);

  if((yb1+7>=90 && (xb1<p3[0] || xb1>p3[2])) && ball_flag[6]==1) {
    player_life[2]--;
    ball_flag[6]=0;			
  }	

  if((yb2+7>=90 && (xb2<p3[0] || xb2>p3[2])) && ball_flag[7]==1) {
    player_life[2]--;
    ball_flag[7]=0;			
  }	

  if((yb3+7>=90 && (xb3<p3[0] || xb3>p3[2])) && ball_flag[8]==1) {
    player_life[2]--;
    ball_flag[8]=0;			
  }	

  /*
  if((yb4+7>=90 && (xb4<p3[0] || xb4>p3[2])) && ball_flag[3]==1) {
    player_life[2]--;
    ball_flag[3]=0;			
  }	
  */

  if(player_life[2]==0)	{
    life_status[2]=0;	
    //end();	
    //exit(0);
  }

  if(yb1+7<90)
    ball_flag[6]=1;

  if(yb2+7<90)
    ball_flag[7]=1;

  if(yb3+7<90)
    ball_flag[8]=1;

  //if(yb4+7<90)
  //	ball_flag[3]=1;

}

void check_life4()
{
  if((xb1-7<=-90 && (yb1<p4[0] || yb1>p4[2])) && ball_flag[9]==1) {
    player_life[3]--;
    ball_flag[9]=0;			
  }	

  if((xb2-7<=-90 && (yb2<p4[0] || yb2>p4[2])) && ball_flag[10]==1) {
    player_life[3]--;
    ball_flag[10]=0;			
  }	

  if((xb3-7<=-90 && (yb3<p4[0] || yb3>p4[2])) && ball_flag[11]==1) {
    player_life[3]--;
    ball_flag[11]=0;			
  }	

  /*
  if((xb4-7<=-90 && (yb4<p4[0] || yb4>p4[2])) && ball_flag[3]==1) {
    player_life[3]--;
    ball_flag[3]=0;			
  }	
  */

  if(player_life[3]==0)	{
    life_status[3]=0;
    //end();		
  }

  if(xb1-7>-90)
    ball_flag[9]=1;

  if(xb2-7>-90)
    ball_flag[10]=1;

  if(xb3-7>-90)
    ball_flag[11]=1;

}


void save_game_state_variables()
{
  //printf("\n\n \t save variable fun\n\n");

  no_of_balls=(int)atof(array[0]);
  no_of_balls-=50;
  total_players=(int)atof(array[1]);

  if(player_id!=1) {
    /* save the Paddles position */
    //printf("\n-------------------------------\n");
    for(c=2,j=0;c<6;c++,j++) {
      p1[j]=atof(array[c]);
      //printf("\np1[%d]=%f array[%d]=%s",j,p1[j],c,array[c]);
    }
  }	

  if(player_id!=2) {	
    //printf("\n-------------------------------\n");
    for(c=6,j=0;c<10;c++,j++) {
      p2[j]=atof(array[c]);
      //printf("\np2[%d]=%f array[%d]=%s",j,p2[j],c,array[c]);
    }
  }

  if(player_id!=3) {
    //printf("\n-------------------------------\n");
    for(c=10,j=0;c<14;c++,j++) {
      p3[j]=atof(array[c]);
      //printf("\np3[%d]=%f array[%d]=%s",j,p3[j],c,array[c]);
    }
  }

  if(player_id!=4) {	
    //printf("\n-------------------------------\n");
    for(c=14,j=0;c<18;c++,j++) {
      p4[j]=atof(array[c]);
      //printf("\np4[%d]=%f array[%d]=%s",j,p4[j],c,array[c]);
    }
    //printf("\n-------------------------------\n");
  }	

  c=18;

  // ** Save the Centre of circle **
  xb1=atof(array[18]);
  yb1=atof(array[19]);

  xb2=atof(array[20]);
  yb2=atof(array[21]);	

  xb3=atof(array[22]);
  yb3=atof(array[23]);

  y11=atof(array[24]);
  dead_player=(int)y11;

  if(dead_player==1 || dead_player==2 || dead_player==3 || dead_player==4)
    dead_flag[dead_player-1]=1;

  /* save the Centre of circle */
  //printf("\n\n\nxb1=%f yb1=%f \t xb2=%f yb2=%f \t xb3=%f yb3=%f\n\n",xb1,yb1,xb2,yb2,xb3,yb3);
  //printf("\n-------------------------------\n");
}

int client_function(char argv[20],char packet_data[1000])
{
  /* Send function for Sending Game state( PAddle + Ball Co-ordinates)  to server */
  if((numbytes = sendto(sockfd1, packet_data, strlen(packet_data), 0,
          (struct sockaddr *)&server_addr, sizeof(struct sockaddr))) == -1){
    // change1 
    perror("Client-sendto() error lol!");
    //exit(1);
  }
  else {
    //printf("Client-sendto() is OK...\n");
  }
  return 0;

}

int server_function(char packet_data[1000])
{
  if((numbytes = recvfrom(sockfd1, buf, MAXBUFLEN-1, 0, (struct sockaddr *)&server_addr, &addr_len)) == -1) {
    perror("Server-recvfrom() error lol!");
    /*If something wrong, just exit lol...*/
    //exit(1);
  }
  else if(numbytes==1) {
    if(buf[0]=='0' && dead_flag[0]==0)
      dead_flag[0]=1;
    if(buf[0]=='1' && dead_flag[1]==0)
      dead_flag[1]=1;
    if(buf[0]=='2' && dead_flag[2]==0)
      dead_flag[2]=1;
    if(buf[0]=='3' && dead_flag[3]==0)
      dead_flag[3]=1;

    /* if(buf[0]=='9')
       end(); */
  }
  else {
    buf[strlen(buf)]='\0';
  }

  buf[numbytes] = '\0';

  /* store dat into packet_data */
  strcpy(packet_data,buf); 
  return 0; 
}

void* send1(void *data)
{
  int count2=0;

  for(count2=0; ; count2++) {		
    //xb1+=5;
    //yb1+=5;
    //if(sig==1 && (flag1==1 || life_status[player_id-1]==1))

    if(flag1==1) {
      //	2 lines
      fill_data_packet(packet_data);
      client_function(ip_addr,packet_data);
      //flag1=0;
    }	

    //end();
    //usleep(10000);
  }//end-for
}

void *receive1(void *data)
{
  int count1=0;

  for(count1=0;;count1++) {		
    server_function(packet_data);
    extract_data_packet(packet_data);
    save_game_state_variables();
    display();
    //usleep(10000);	
  }
}

void control()
{
  pthread_t sender_thread,receiver_thread;

  pthread_create(&sender_thread,NULL,&send1,NULL);
  pthread_create(&receiver_thread,NULL,&receive1,NULL);

  //	pthread_join(sender_thread,NULL);
  //	pthread_join(receiver_thread,NULL);
}

void begin()
{
  char id[2];
  /* get the host info */
  if ((he = gethostbyname(ip_addr)) == NULL)
  {
    perror("Client-gethostbyname() error lol!");
    //exit(1);
  }
  else{
    //printf("Client-gethostname() is OK...\n");
  }

  /* obtaining the socket ID */
  if((sockfd1 = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {	
    perror("Client-socket() error lol!");
    //exit(1);
  }	
  else{
    //printf("Client-socket() sockfd1 is OK...\n");
  }

  /* host byte order */ 
  server_addr.sin_family = AF_INET;

  /* short, network byte order */
  //printf("Using port: 4950\n");
  server_addr.sin_port = htons(MYPORT);
  server_addr.sin_addr = *((struct in_addr *)he->h_addr);

  /* zero the rest of the struct */ 
  memset(&(server_addr.sin_zero), '\0', 8);

  // 2 lines
  fill_data_packet(packet_data);
  client_function(ip_addr,packet_data);

  if((numbytes = recvfrom(sockfd1, id, 2, 0, (struct sockaddr *)&server_addr, &addr_len)) == -1) {
    perror("Server-recvfrom() error lol!");
    /*If something wrong, just exit lol...*/
    //exit(1);
  }
  else {
    id[strlen(id)]='\0';
    //printf("Server-Waiting and listening...\n");
    //printf("Server-recvfrom() is OK...\n");
  }

  //printf("Server-Got packet from %s\n", inet_ntoa(server_addr.sin_addr));
  //printf("Server-Packet is %d bytes long\n", numbytes);
  id[numbytes] = '\0';
  player_id=atoi(id);
  //sprintf(name_of_window,"Player NO - %d",player_id);	
}

void init()
{
  // clearing window with a color
  glClearColor(.0f, .0f, .0f, 0.0f);		//to change window background color
  glClear(GL_COLOR_BUFFER_BIT);
  // and more…
}

void keySpecial (int key, int x, int y) 
{  
  keySpecialStates[key] = true; // Set the state of the current key to pressed  
}

void keySpecialUp (int key, int x, int y) 
{  
  keySpecialStates[key] = false; // Set the state of the current key to pressed  
} 

void keySpecialOperations(void) 
{  

  if(player_id==1) {

    // If the left arrow key has been pressed // Perform left arrow key operations
    if (keySpecialStates[GLUT_KEY_LEFT]) {
      if(p1[2]-35>-90) {	
        p1[0]-=paddle_delta1;
        p1[2]-=	paddle_delta1;
      }

      if(p1[2]-35<=-90) {
        p1[0]=-90;
        p1[2]=-55;
      }

      flag1=1;
      sig=1;
    }  
    // If the left arrow key has been pressed // Perform left arrow key operations  
    else if (keySpecialStates[GLUT_KEY_RIGHT]) {

      if(p1[0]+35<90) {	
        p1[0]+=paddle_delta1;
        p1[2]+=	paddle_delta1;
      }
      if(p1[0]+35>=90) {
        p1[0]=90;
        p1[2]=55;
      }		

      flag1=1;
      sig=1;
    }

  }//if-end-player_id_1

  /* Player-3 */
  else if(player_id==3) 
  {
    if (keySpecialStates[GLUT_KEY_LEFT]) { 
      // If the left arrow key has been pressed 
      // Perform left arrow key operations 

      if(p3[2]-35>-90) {	
        p3[0]-=paddle_delta1;
        p3[2]-=	paddle_delta1;
      }
      if(p3[2]-35<=-90) {
        p3[0]=-90;
        p3[2]=-55;
      }

      flag1=1;
      sig=1; 
    }  
    else if (keySpecialStates[GLUT_KEY_RIGHT]) { 
      // If the left arrow key has been pressed 
      // Perform left arrow key operations

      if(p3[0]+35<90) {	
        p3[0]+=paddle_delta1;
        p3[2]+=	paddle_delta1;
      }

      if(p3[0]+35>=90) {
        p3[0]=90;
        p3[2]=55;
      }		

      flag1=1;
      sig=1;
    }
  }//if-end-player_id_3

  /* Player-2 */
  else if(player_id==2)
  {
    if (keySpecialStates[GLUT_KEY_UP]) {
      // If the left arrow key has been pressed 
      // Perform left arrow key operations

      if(p2[1]+35<90) {
        p2[1]+=paddle_delta1;
        p2[3]+=paddle_delta1;
      }		 

      if(p2[1]+35>=90) {
        p2[1]=90;
        p2[3]=55;
      }

      flag1=1;
      sig=1; 
    } 
    else if (keySpecialStates[GLUT_KEY_DOWN]) {
      // If the left arrow key has been pressed 
      // Perform left arrow key operations  

      if(p2[1]-35>-90)	{
        p2[1]-=paddle_delta1;
        p2[3]-=paddle_delta1;
      }		 
      if(p2[1]-35<=-90) {
        p2[1]=-90;
        p2[3]=-55;
      }			

      flag1=1;
      sig=1;
    }
  }//if-end-player_id_2

  /* Player-4 */
  else if(player_id==4) 
  {
    if (keySpecialStates[GLUT_KEY_UP]) {
      // If the left arrow key has been pressed 
      // Perform left arrow key operations

      if(p4[1]+35<90) {
        p4[1]+=paddle_delta1;
        p4[3]+=paddle_delta1;
      }		 

      if(p4[1]+35>=90) {
        p4[1]=90;
        p4[3]=55;
      }

      flag1=1;
      sig=1;
    }
    else if (keySpecialStates[GLUT_KEY_DOWN]) {
      // If the left arrow key has been pressed 
      // Perform left arrow key operations

      if(p4[1]-35>-90)	{
        p4[1]-=paddle_delta1;
        p4[3]-=paddle_delta1;
      }

      if(p4[1]-35<=-90) {
        p4[1]=-90;
        p4[3]=-55;
      }			

      flag1=1;
      sig=1;
    }
  }//if-end-player_id_4

}//keySpecialOperations-end

/*
void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
}
*/

void reshape(GLsizei w, GLsizei h) {
  
    GLfloat aspectRatio;
    h=(!h?1:h);
    glViewport(0,0,w,h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    aspectRatio =(GLfloat)w / (GLfloat)h;
    
   
    if(w<=h) {
      g_height =100.0/aspectRatio;
        g_width=100.0;
        glOrtho(-100.0,100.0,-100/aspectRatio, 100.0/aspectRatio, 1.0,-1.0);
    }
    else  {
      glOrtho(-100.0*aspectRatio,100.0*aspectRatio,-100, 100.0, 1.0,-1.0);
        g_width = 100.0* aspectRatio;
        g_height =100.0;
    }
  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  glutPostRedisplay();
}


void draw_circle(float h,float k)
{
  // Drawing balls 
  int i=0;

  glBegin(GL_POLYGON); 
    glColor3f(1.0f,0.0f,.0f);
    //glTranslatef((GLfloat)xb1,(GLfloat)yb1,0.0);
    for (i = 0; i < circle_points; i++) 
    {    
      angle = 2*PI*i/circle_points; 
      glVertex2f(h+cos(angle)*radius,k+ sin(angle)*radius);
    } 
  
    glEnd();
    //printf("\n\nPlayer No :%d  inside draw Circle : xb1=%f \t yb1=%f",player_id,xb1,yb1);
    printf("\n P = %d",player_id);

  if(total_players==1 || total_players==2 || total_players==3 || total_players==4)
    check_life1();
  if(total_players==2 || total_players==3 || total_players==4)
    check_life2();

  if(total_players==3 || total_players==4)
    check_life3();

  if(total_players==4)
    check_life4();

  printf("\n \ndead Man : %d  total_players=%d \tlife_status[%d]=%d  %d %d %d \n \tdead_flag[0]=%d %d %d %d \n\n%d \t %d\t %d\t %d\t  ",dead_player,total_players,(player_id-1),life_status[0],life_status[1],life_status[2],life_status[3],dead_flag[0],dead_flag[1],dead_flag[2],dead_flag[3],player_life[0],player_life[1],player_life[2],player_life[3]);	

  //check_life1();
  //	//////printf("\n *********Player1 life = %d",player1_life);
}

void draw_border()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);	//Red Paddle

  // next code will draw a line at starting and ending coordinates specified by glVertex3f
  //line 3
  glBegin(GL_LINES);
  glVertex3f(-100.0f, 90.0f, 0.0f); // origin of the line
  glVertex3f(100.0f, 90.0f, 0.0f); // ending point of the line
  glEnd( );

  // line 1 
  glBegin(GL_LINES);
  glVertex3f(-100.0f, -90.0f, 0.0f); // origin of the line
  glVertex3f(100.0f, -90.0f, 0.0f); // ending point of the line
  glEnd( );

  // Line 2
  glBegin(GL_LINES);
  glVertex3f(90.0f, 100.0f, 0.0f); // origin of the line
  glVertex3f(90.0f, -100.0f, 0.0f); // ending point of the line
  glEnd( );

  // next code will draw a line at starting and ending coordinates specified by glVertex3f
  glBegin(GL_LINES);
  glVertex3f(-90.0f, 100.0f, 0.0f); // origin of the line
  glVertex3f(-90.0f, -100.0f, 0.0f); // ending point of the line
  glEnd( );
}


void draw_brick(int paddle_no)
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.8,0.1,0.1);

  //if(dead_flag[paddle_no-1]==1  && paddle_no==1)	
  if(paddle_no==1)	
    glRectf(-100.0,-100.0,100,-90);

  else if(paddle_no==2)	
    glRectf(90.0,-100.0,100,100);


  else if(paddle_no==3)	
    glRectf(-100.0,90.0,100,100);


  else if(paddle_no==4)	
    glRectf(-100.0,-100.0,-90.0,100);
}

void displayString(float x, float y, const char* string)
{
  //gfColor3f(0,0,0);//text color
  glRasterPos2f(x, y);
  glColor4f(1.0f, 0.0f, 1.0f, 0.5f);
  //for(int i=0;str[i]!='\0';i++)
  glutBitmapString(GLUT_BITMAP_HELVETICA_18 , (const unsigned char *)string);
}

void display(void)
{
  int c=0;

    //glPushMatrix();	
    //keyOperations();
    keySpecialOperations();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);	//Green Paddle


  //Drawing border
  draw_border();

  // Drawing paddles
  glRectf(p1[0],p1[1],p1[2],p1[3]);
  if(player_life[0]>0)
  {
    sprintf(l1,"%d",player_life[0]);
    displayString(p1[0]+17,-80,l1);
  }

  if(total_players>=2)
  {
    glRectf(p2[0],p2[1],p2[2],p2[3]);

    if(player_life[1]>0)
    {
      sprintf(l2,"%d",player_life[1]);
        displayString(80,p2[1]+17,l2);
    }

  }
  else 
    glRectf(90.0,-100.0,100,100);


  if(total_players>=3)
  {
    glRectf(p3[0],p3[1],p3[2],p3[3]);
      if(player_life[2]>0 && total_players>=3)
      {
        sprintf(l3,"%d",player_life[2]);
        displayString(p2[1]+17,80,l3);
      }
  }
  else
    glRectf(-100.0,90.0,100,100);


  if(total_players==4)
  {	
    glRectf(p4[0],p4[1],p4[2],p4[3]);
      if(player_life[3]>0 && total_players>=4)
      {
        sprintf(l4,"%d",player_life[3]);
        displayString(-80,p4[1]+17,l4);
      }	
  }
  else
    glRectf(-100.0,-100.0,-90.0,100);



  //drawing balls
  draw_circle(xb1,yb1);

  draw_circle(xb2,yb2);

  draw_circle(xb3,yb3);



  // drawing bricks

  if(dead_flag[0]==1)
  {
    //glColor3f(0.8,0.1,0.1);
    glRectf(-100.0,-100.0,100,-90);

    //draw_brick(1);
  }

  if(dead_flag[1]==1)
  {			
    //glColor3f(0.8,0.1,0.1);
    glRectf(90.0,-100.0,100,100);

    //draw_brick(2);


  }	
  if(dead_flag[2]==1)
  {	
    //glColor3f(0.8,0.1,0.1);
    glRectf(-100.0,90.0,100,100);
    //draw_brick(3);
  }
  if(dead_flag[3]==1)
  {			
    //glColor3f(0.8,0.1,0.1);
    glRectf(-100.0,-100.0,-90.0,100);
    //draw_brick(4);

  }

  // ** last changes at 1.04
  //timer();
  //check_life1();
  //glPopMatrix();

  
    /* swap buffers to display the frame */
    glutSwapBuffers();
  usleep(30000);

}

/* main Function  */
int main(int argc,char *argv[])
{
  glutInit(&argc, argv );
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize( g_width, g_height );
  glutInitWindowPosition( 300, 300 );
  glutCreateWindow("PING-PONG");

  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  //glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
  //glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events  

  glutSpecialFunc(keySpecial); // Tell GLUT to use the method "keySpecial" for special key presses  
  glutSpecialUpFunc(keySpecialUp); // Tell GLUT to use the method "keySpecialUp" for special up key events  

  glutIdleFunc(display);

  if(start==0) {
    // Dont touch this line otherwise connection time-out will appear
    strcpy(ip_addr, argv[1]);

    begin();
    control();

    start=1;		
  }


  usleep(100);
  glutMainLoop();

  // closing socket
  if (close(sockfd1) != 0)
    printf("Client-sockfd1 closing is failed!\n");
  else
    printf("Client-sockfd1 successfully closed!\n");

  return 0;
}

