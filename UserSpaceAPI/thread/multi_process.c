#include<unistd.h>
#include<stdio.h>


void dataformatter()
{
    while(1)
    {
      printf("\n In dataformatter task"); 
    }

}

void loggertask()
{
    while(1)
    {
      printf("\n In logger task "); 
    }

}

int main(){
  int idx, idy;
  
  //fork 1st child
  idx = fork(); 
  if(0 == idx)
  {
    //fork 2nd child
    idy = fork();
    if(0 == idy)
    {
      dataformatter(0);
    }
    else
    {
      loggertask(0); 
    }
  }//outer-if
  else
  {
    while(1)
    {
      printf("\n In Main task "); 
    }
  }
   
  return 0;
}
