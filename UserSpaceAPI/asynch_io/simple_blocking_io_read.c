#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<poll.h>
#include<unistd.h>

int main()
{

  int fd;
  char buf[11];
  int ret;

  //stdin
  fd = 0;

  while(1)
  {
    memset((void*)buf, 0, 10);
    ret = read(fd, (void*)buf, 10);
    printf("ret=%d\n",ret);

    if(ret!=-1)
    {
      buf[10]='\0';
      printf("buf=%s\n",buf);
    }


  }

}

