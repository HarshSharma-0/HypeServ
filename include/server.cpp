#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <iostream>
#include "server.hpp"

int WORKER_NUMBER{0};
bool LOCAL_HOST{false};
int DESIRED_PORT{0};
char MOUNT_PATH[500];
int DESIRED_AUDIENCE{0};
int NETWORK_IP{0};

void server_start() {

  struct sockaddr_in socket_qe, cli_addr;
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    std::cout << "error createing socket  " << strerror(errno) << std::endl;
  };
  socket_qe.sin_family = AF_INET;
  socket_qe.sin_port = htons(DESIRED_PORT);
  socket_qe.sin_addr.s_addr = INADDR_ANY;
  socklen_t socket_len = sizeof(socket_qe);

  if (bind(server_fd, (struct sockaddr *)&socket_qe, socket_len) < 0) {
    std::cout << "\nerror binding\n";
  };

  if (listen(server_fd, 3) < 0) {
    std::cout << "error listening" << std::endl;
  }
  socklen_t clilen = sizeof(cli_addr);
  int cfd = accept(server_fd, (struct sockaddr *)&socket_qe, &socket_len);
  
  if (shutdown(server_fd, SHUT_RDWR) < 0) {
    std::cout << "error shutdown" << std::endl;
    shutdown(server_fd, SHUT_RDWR);
  }
}
