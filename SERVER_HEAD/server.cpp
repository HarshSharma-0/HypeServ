#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "config.hpp"
#include "server.hpp"
#include "VT100.hpp"


SERVER_CONFIG SERVER_CONFIG_t;
bool parse_true = false;
int **WORKER_CLIENT_FD = nullptr;

WORKER_THREAD_ARGS* args = new WORKER_THREAD_ARGS;
void server_start() {
    bool server_shutdown = false;
    int client_fd {0};
    pthread_t *Thread_ID = new pthread_t[SERVER_CONFIG_t.WORKER.desiredWorkerNo];


    args-> MOUNT_PATH = SERVER_CONFIG_t.WORKER.mountPathWorker;
    args-> MAX_CLIENT = SERVER_CONFIG_t.WORKER.connectionPerWorker;

    WORKER_CLIENT_FD = new int*[SERVER_CONFIG_t.WORKER.desiredWorkerNo];

    if( WORKER_CLIENT_FD == nullptr) { return; }
    for (int i = 0; i < SERVER_CONFIG_t.WORKER.connectionPerWorker; i++) {
        WORKER_CLIENT_FD[i] = new int[SERVER_CONFIG_t.WORKER.connectionPerWorker];
        if(WORKER_CLIENT_FD[i] == nullptr){ return; }
    }

   //thread pool creation
   for(int J = 0 ; J < SERVER_CONFIG_t.WORKER.desiredWorkerNo ; J++){
         args-> MOUNT_PATH = SERVER_CONFIG_t.WORKER.mountPathWorker;
         args-> MAX_CLIENT = SERVER_CONFIG_t.WORKER.connectionPerWorker;
         args->CFD_DATA = &WORKER_CLIENT_FD [J][J];
         if(pthread_create(&Thread_ID [J], nullptr , CLIENT_WORKER , (void*)args) != 0){ std::cout<<strerror(errno)<<std::endl; return; }



    }

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
    std::cout << "\nerror binding\n" <<  ntohs(SERVER_SOCKET.sin_port) << strerror(errno);
    return;
  };

  if (listen(server_fd, 3) < 0) {
    std::cout << "error listening" << std::endl; return;
  }
  std::cout << "SERVER startted on IP: " << inet_ntoa(SERVER_SOCKET.sin_addr)<< ":" << ntohs(SERVER_SOCKET.sin_port) << std::endl;

  socklen_t clilen = sizeof(CLIENT_SOCKET);

// *********************************************************************************************************************
    while( server_shutdown != true ){

          client_fd = accept(server_fd, (struct sockaddr *)&CLIENT_SOCKET, &clilen);

         if (client_fd == -1) {

              perror("Error accepting connection");
               return;

                  }
           server_shutdown = true;
        }
// *********************************************************************************************************************
    std::cout << "New connection received from: " << inet_ntoa(CLIENT_SOCKET.sin_addr)
              << " Port: " << ntohs(CLIENT_SOCKET.sin_port) << std::endl;

    if (shutdown(client_fd, SHUT_RDWR) < 0) {
        std::cout << "Error shutting down client socket" << std::endl;
    }
  if (shutdown(server_fd, SHUT_RDWR) < 0) {
    std::cout << "error shutdown" << std::endl; return;
  }
    std::cout<<"shutdown complete";
for (int delete_u = 0 ; delete_u < SERVER_CONFIG_t.WORKER.desiredWorkerNo ; delete_u ++){
  delete [] WORKER_CLIENT_FD [delete_u];
 }
  delete [] WORKER_CLIENT_FD;
  delete [] Thread_ID;
  delete args;
return;
}
