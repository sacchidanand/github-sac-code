  
  struct epoll_event ev, events[MAX];
  epfd = epoll_create1(EPOLL_CLOEXEC);
    
  struct epoll_event ev;
  ev.events = EPOLLIN | EPOLLOUT | EPOLLET | EPOLLONESHOT;
  ev.data.fd = listen_sock;

  //int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
  (success) :: 0 == epoll_ctl( epfd,  EPOLL_CTL_ADD/MOD/DEL,  conn_sock, &ev)

  //ret = total changed FD
  nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);

  

  /*
   * pselect(2),  epoll_pwait()  allows an application to safely wait until either a file
    descriptor becomes ready or until a signal is caught
  */


