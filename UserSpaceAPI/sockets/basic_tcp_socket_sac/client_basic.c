#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define MAXBUFFERSIZE 100
#define PORT 7777

int main(int argc, char *argv[])
{
  int clientSocketNumber = 0, bytesReceived=0;
  char buffer[MAXBUFFERSIZE] ;
 
  struct sockaddr_in serverSocketAddress;
  socklen_t addr_size;

  //method-2
  struct hostent *host;
  host = gethostbyname("127.0.0.1");

  clientSocketNumber = socket(PF_INET, SOCK_STREAM, 0);
  printf("\n socket() created ! clientSocketNumber=%d (PF_INET, SOCK_STREAM, 0-TCP)",clientSocketNumber);
  sleep(3);
  
  serverSocketAddress.sin_family = AF_INET;
  serverSocketAddress.sin_port = htons(PORT);
 
  //method-1
  //serverSocketAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

  //method-2  
  serverSocketAddress.sin_addr = *((struct in_addr*)host->h_addr);

  memset(serverSocketAddress.sin_zero, '\0', sizeof(serverSocketAddress.sin_zero));

  addr_size = sizeof serverSocketAddress;
  connect(clientSocketNumber, (struct sockaddr *)&serverSocketAddress, addr_size);
  printf("\n connect(): try connecting to serverSocketAddress \n\t\t Pass clientSocketNumber");
  sleep(3);

  printf("\n recv(): receive buffer data from server ");
  bytesReceived = recv(clientSocketNumber, buffer, MAXBUFFERSIZE, 0);
  buffer[bytesReceived] = '\0';
  sleep(3);

  printf("\n\n Buffer/data received from server \n Buffer=%s ", buffer);
  printf("\n\n Client exiting ...\n\n");

  return 0;
}


