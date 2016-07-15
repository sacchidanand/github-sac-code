#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
//#include<netdb.h>
#define MAXBUFFERSIZE 100
#define PORT 7777
#define NUMBEROFCONNECTION 4

int main(int argc, char *argv[])
{

  int serverSocketNumber=0, newClientSocketNumber=0;  

  struct sockaddr_in serverSocketAddress, clientSocketAddress;
  struct sockaddr_storage serverStorage;
  
  socklen_t addrSize;

  char buffer[MAXBUFFERSIZE];

  /*  Create the socket 3 args
   *  Domain , type, protocol (def=0; e.g. TCP for type=SOCK_STREAM)
   */
  serverSocketNumber = socket(PF_INET, SOCK_STREAM, 0);
  printf("\n socket() created ! (PF_INET, SOCK_STREAM, 0-TCP) ");
  //sleep(3);

  /* Configure settings of the Server Address Structure 
   *  IP + PORT 
   *  sin_family, sin_addr.s_addr, sin_port, sin_zero
   */  

  /* Address Family = Internet */  
  serverSocketAddress.sin_family = AF_INET;

  /* Set Server IP Address */
  //Method-1
  //serverSocketAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  //Method-2
  serverSocketAddress.sin_addr.s_addr = INADDR_ANY;

  /* Port number using htons : byte order
     host to network byte order data transfer
     hton*
     short  = htons
     long   = htonl */
  serverSocketAddress.sin_port = htons(PORT);

  /* Set all bits of the padding field to 0 */
  memset(serverSocketAddress.sin_zero, '\0', sizeof serverSocketAddress.sin_zero);

  /* locally  Bind the Server-Socket-Address struct to Socket(int) 
   * serverSocketNumber(int) is IMPORTANT for communicating data
   */
  if(0 > bind(serverSocketNumber, (struct sockaddr *)&serverSocketAddress, sizeof(serverSocketAddress)))
    printf("\n Error in binding socket <-> sockaddr, \n no socket created");
  else
    printf("\n bind() serverSocketNumber=%d binded to serverSocketAddress !",serverSocketNumber);
  //sleep(3);
  
  /* listen(on Server-Socket-Number, #connections ) 
   * 2 max connection request queued 
   * 2 clients can be queued
   * 3rd client will be dropped from serving request*/
  if(0 == listen(serverSocketNumber, NUMBEROFCONNECTION))
    printf("\n listen()... Server Socket is waiting/Blocking \n ");
  else
    printf("\n Something gone wrong, error happend in listen(socket, connections) call \n might be 3rd connection is not allowed to connect");

  //sleep(3);

  /* Accept call() will keep list of clients sockets 
   * creates new sockets for incoming connections
   */
  /*Method-1
  addrSize = sizeof serverStorage;
  newClientSocketNumber = accept(serverSocketNumber, (struct sockaddr*)&serverStorage, &addrSize);
  printf("\n accept() connection & stores clientSocketNumber = %d", newClientSocketNumber);
  sleep(3);
  */

  //method-2
  //To view client address & port
  size_t size = sizeof(struct sockaddr_in);
  newClientSocketNumber = accept(serverSocketNumber, (struct sockaddr *)&clientSocketAddress, &size); 
  
  printf("\nServer got connection from client IP = %s", inet_ntoa(clientSocketAddress.sin_addr));
  printf("\n Port= %d", ntohs(clientSocketAddress.sin_port));

  strcpy(buffer, "Hello message from server to client !");
  printf("\n send() sending buffer from server to client ");
  send(newClientSocketNumber, buffer, strlen(buffer), 0);
  //sleep(3);

  printf("\n Server successfully sends out the data to client\n\n Server exiting ...\n\n");

  return 0;
}

