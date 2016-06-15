#include<signal.h>
#include<stdio.h>

static char buffer[5];
void myctrlc(int sno);
void myterm(int sno);
void mysegfault(int sno);
void mycont(int sno);
void (*oldhandler)(int);
int main(int argc, char*argv[])
{
  char *k="sac";
  sigset_t mypendingset;
  //oldhandler = signal(SIGINT, myctrlc);
  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, myterm);
  signal(SIGCONT, myterm);
  signal(SIGSEGV, mysegfault);

  sigemptyset(&mypendingset);
  sigaddset(&mypendingset, SIGINT);
  sigaddset(&mypendingset, SIGTERM);

  while(1){
    sigprocmask(SIG_BLOCK, &mypendingset, 0); 
    fgets(buffer,5,stdin);
    printf("\nBuffer = %s", buffer);
    sigprocmask(SIG_UNBLOCK, &mypendingset, 0); 
    k[6] ='h';
  }
  return 0;
}

void mysegfault(int sno){
  printf("\nYou are in hell in infinite loop",sno);
  //abort();
  exit(0);
}
void myctrlc(int sno){
  static int count = 0;
  if(count>0){
    signal(sno, SIG_DFL);
    //signal(sno, oldhandler);
  }
  count++;
  printf("\nctrl+c sno=%d",sno);
}

void myterm(int sno){
  printf("\nTerm sno=%d",sno);
}

void mycont(int sno){
  printf("\nLast input was buffer=%s",buffer);
}

