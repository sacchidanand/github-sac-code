
//10.20.14.11

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <unistd.h> // Header File for sleeping.
#include<time.h>
#include<signal.h>
#include <math.h>
//#include <vector>
#include<stdlib.h>
#include<stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define a1 .6870000
#define b1 .590000

#define a2 .8870000
#define b2 .490000


#define a3 .590000
#define b3 .680000


#define paddle_delta1 .800000
#define paddle_delta3 .800000

#define ROT_INC	0.1
#define PI 3.1415926535897 

#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>


/* the port users will be connecting to */
#define MYPORT 4345
#define MAXBUFLEN 500



void timer();
void reshape( GLsizei width, GLsizei height );
void draw_circle(float h,float k);
//void draw_circle();
void display(void);
void init();
void glutIdleFunc(void (*func)(void));
void keyPressed (unsigned char key, int x, int y); 
void keyUp (unsigned char key, int x, int y);

void keySpecialOperations(void);
void keySpecialUp (int key, int x, int y);
void keySpecial (int key, int x, int y);

void check_life1();


