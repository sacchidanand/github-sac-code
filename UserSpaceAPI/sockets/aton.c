#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
/*convert Human readable IP - address into binary dotted notations.*/
int main(int argc, char*argv[]){

  struct in_addr addr;
  char dst_addr[17];
  if(argc!=2){
    fprintf(stderr,"%s <dotted-address>\n",argv[1]);
    exit(EXIT_FAILURE);
  }

  if(inet_aton(argv[1],&addr)==0){
    perror("inet_aton");
    exit(EXIT_FAILURE);
  }

  printf("inet_ntoa() %s\n\n", inet_ntoa(addr));
  
  inet_ntop(AF_INET, &addr.s_addr, dst_addr, INET_ADDRSTRLEN);
  printf("inet_ntop() %s\n\n", dst_addr);
  
  printf("binary address %x\n\n", addr.s_addr);
  exit(EXIT_SUCCESS);
}


