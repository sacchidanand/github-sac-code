#include<stdio.h>
#include<stdlib.h>
#include<sys/epoll.h>


#define MAX_EVENTS 10
struct epoll_event ev;
struct epoll_event events[MAX_EVENTS];
int listen_sock, conn_sock, nfds, epollfd;

/* Set up listening socket, 'listen_sock' (socket(),
 *               bind(), listen()) */

epollfd = epoll_create(10);
if (epollfd == -1) {
  perror("epoll_create");
  exit(EXIT_FAILURE);
}

// ev.events = EPOLLIN | EPOLLOUT | EPOLLET | EPOLLONESHOT;
ev.events = EPOLLIN;
ev.data.fd = listen_sock;

//int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
// (success) :: 0 == epoll_ctl( epfd,  EPOLL_CTL_ADD/MOD/DEL,  conn_sock, &ev)
if( epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1 ) 
{
  perror("epoll_ctl: listen_sock");
  exit(EXIT_FAILURE);
}

//infinite loop
for (;;) 
{

  //ret = total changed FD
  nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
  /*
   * pselect(2),  epoll_pwait()  allows an application to safely wait until either a file
   descriptor becomes ready or until a signal is caught
   */
  if (nfds == -1) {
    perror("epoll_pwait");
    exit(EXIT_FAILURE);
  }

  for (n = 0; n < nfds; ++n) 
  {
    if (events[n].data.fd == listen_sock) 
    {
      //if we found the listening server socket
      //accept the connection
      //add this new client sock into above epfd
      conn_sock = accept(listen_sock, (struct sockaddr *) &local, &addrlen);
      if (conn_sock == -1) 
      {
        perror("accept");
        exit(EXIT_FAILURE);
      }

      //set non blocking
      setnonblocking(conn_sock);
      ev.events = EPOLLIN | EPOLLET;
      ev.data.fd = conn_sock;
      if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) 
      {
        perror("epoll_ctl: conn_sock");
        exit(EXIT_FAILURE);
      }
    } 
    else 
    {
      do_use_fd(events[n].data.fd);
    }
  }//end-for
}

