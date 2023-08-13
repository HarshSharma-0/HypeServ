#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include "config.hpp"
#include "server.hpp"
#include "VT100.hpp"


SERVER_CONFIG SERVER_CONFIG_t;
bool parse_true = false;

void server_start() {

  struct sockaddr_in SERVER_SOCKET, CLIENT_SOCKET;
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    std::cout << "error createing socket  " << strerror(errno) << std::endl; return;
  };
  SERVER_SOCKET.sin_family = AF_INET;
  SERVER_SOCKET.sin_port = htons(SERVER_CONFIG_t.portNumber);

  if (inet_pton(AF_INET, SERVER_CONFIG_t.ipAddress, &SERVER_SOCKET.sin_addr) == 1){ std::cout<<VT100_COLOR_GREEN<<"Network IP conversion sucess"<<VT100_COLOR_RESET<<std::endl; }
  else{ std::cout<<VT100_COLOR_RED<<"Error converting IP address to Network format (might be due to error in config file format[.IN-config.in in -IP-ADDRESS] or IP format) "<<strerror(errno)<<VT100_COLOR_RESET<<std::endl; return;};

  socklen_t socket_len = sizeof(SERVER_SOCKET);

  if (bind(server_fd, (struct sockaddr *)&SERVER_SOCKET, socket_len) < 0) {
    std::cout << "\nerror binding\n";
    return;
  };

  if (listen(server_fd, 3) < 0) {
    std::cout << "error listening" << std::endl; return;
  }
  std::cout << "SERVER startted on IP: " << inet_ntoa(SERVER_SOCKET.sin_addr)<<std::endl<< " Port: " << ntohs(SERVER_SOCKET.sin_port) << std::endl;

  socklen_t clilen = sizeof(CLIENT_SOCKET);
  int client_fd = accept(server_fd, (struct sockaddr *)&SERVER_SOCKET, &socket_len);
   if (client_fd == -1) {
        perror("Error accepting connection");
        return;
    }

    std::cout << "New connection received from: " << inet_ntoa(CLIENT_SOCKET.sin_addr)
              << " Port: " << ntohs(CLIENT_SOCKET.sin_port) << std::endl;

    if (shutdown(client_fd, SHUT_RDWR) < 0) {
        std::cout << "Error shutting down client socket" << std::endl;
    }
  if (shutdown(server_fd, SHUT_RDWR) < 0) {
    std::cout << "error shutdown" << std::endl; return;
  }
    std::cout<<"shutdown complete";
return;
}
