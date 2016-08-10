/*
 * Select
 1. Select_Loop uses select system call to sleep until 
    a. Condition occurs on file descriptor (when data is available for reading)
    b. Timout occurs
    c. Signal received (when child dies)

 2. Checking the return value of select find out which FD is changed and execute corresponding function. 
 3. Event_Loop
     Often, for ease of use, the Select_Loop is implemented as an event loop, perhaps using callback functions; 
     the situation lends itself particularly well to event-driven programming.
 */   

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<poll.h>

int main()
{

  int fd;
  char buf[11];
  int ret, sret;

  //stdin
  fd = 0;

  fd_set readfds;
  struct timeval timeout;

  while(1)
  {
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    sret = select(8, &readfds, NULL, NULL, &timeout);

    if(sret == 0)
    {
      printf("sret=%d\n",sret);
      printf("\ttimeout");

    }
    else
    {
      printf("sret=%d\n",sret);
      memset((void*)buf, 0, 10);
      ret = read(fd, (void*)buf, 10);
      printf("ret=%d\n",ret);

      if(ret!=-1)
      {
        /*buf[10]='\0';*/
        printf("buf=%s\n",buf);
      }
    }//else-end
  } //while-end

  return 0;
}

