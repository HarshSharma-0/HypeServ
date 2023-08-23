#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include "config.hpp"
#include "server.hpp"
#include "VT100.hpp"


SERVER_CONFIG SERVER_CONFIG_t;
bool parse_true = false;
int **WORKER_CLIENT_FD = nullptr;
bool server_shutdown = false;
WORKER_THREAD_ARGS* args = new WORKER_THREAD_ARGS ();

void server_start() {

    signal(SIGINT, SIGNAL_SIGINT_HANDLER);

    struct sockaddr_in SERVER_SOCKET, CLIENT_SOCKET;
    socklen_t clilen = sizeof(CLIENT_SOCKET);
    socklen_t socket_len = sizeof(SERVER_SOCKET);
    SERVER_SOCKET.sin_family = AF_INET;
    SERVER_SOCKET.sin_port = htons(SERVER_CONFIG_t.portNumber);

    int NON_BLOCKING_FLAG = 0 ;
    int client_fd {0};
    pthread_t *Thread_ID = new pthread_t[SERVER_CONFIG_t.WORKER.desiredWorkerNo];
    int *SERVER_LOAD = new int[SERVER_CONFIG_t.WORKER.desiredWorkerNo];


    args-> MOUNT_PATH = SERVER_CONFIG_t.WORKER.mountPathWorker;
    args-> MAX_CLIENT = SERVER_CONFIG_t.WORKER.connectionPerWorker;
    args-> IN_ACTIVE_CFD = new int[SERVER_CONFIG_t.WORKER.connectionPerWorker]();
    std::fill_n (args->IN_ACTIVE_CFD,SERVER_CONFIG_t.WORKER.connectionPerWorker, -1 );

    WORKER_CLIENT_FD = new int*[SERVER_CONFIG_t.WORKER.desiredWorkerNo]();

    if( WORKER_CLIENT_FD == nullptr) { return; }
    for (int i = 0; i < SERVER_CONFIG_t.WORKER.desiredWorkerNo ; i++) {
        WORKER_CLIENT_FD[i] = new int[SERVER_CONFIG_t.WORKER.connectionPerWorker]();
        if(WORKER_CLIENT_FD[i] == nullptr){ return; }

    }

   for(int J = 0 ; J < SERVER_CONFIG_t.WORKER.desiredWorkerNo ; J++){
         args-> MOUNT_PATH = SERVER_CONFIG_t.WORKER.mountPathWorker;
         args-> MAX_CLIENT = SERVER_CONFIG_t.WORKER.connectionPerWorker;
         args-> CFD_DATA = &WORKER_CLIENT_FD [J][0];
         if(pthread_create(&Thread_ID [J], nullptr , CLIENT_WORKER , (void*)args) != 0){ std::cout<<strerror(errno)<<std::endl; return; }
         sleep(1);
   }

  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    std::cout << "error createing socket  " << strerror(errno) << std::endl; return;
  };


  NON_BLOCKING_FLAG = fcntl(server_fd, F_GETFL, 0);
  fcntl(server_fd, F_SETFL, NON_BLOCKING_FLAG | O_NONBLOCK);


  if (inet_pton(AF_INET, SERVER_CONFIG_t.ipAddress, &SERVER_SOCKET.sin_addr) == 1){ std::cout<<VT100_COLOR_GREEN<<"Network IP conversion sucess"<<VT100_COLOR_RESET<<std::endl; }
  else{ std::cout<<VT100_COLOR_RED<<"Error converting IP address to Network format (might be due to error in config file format[.IN-config.in in -IP-ADDRESS] or IP format) "<<strerror(errno)<<VT100_COLOR_RESET<<std::endl; return;};


  if (bind(server_fd, (struct sockaddr *)&SERVER_SOCKET, socket_len) < 0) {
    std::cout << "\nerror binding\n" <<  ntohs(SERVER_SOCKET.sin_port) << strerror(errno);
    return;
  };

  if (listen(server_fd, 3) < 0) {
    std::cout << "error listening" << std::endl; return;
  }
  std::cout << "SERVER startted on IP: " << inet_ntoa(SERVER_SOCKET.sin_addr)<< ":" << ntohs(SERVER_SOCKET.sin_port) << std::endl;


    while ( server_shutdown != true ){
         client_fd = accept(server_fd, (struct sockaddr *)&CLIENT_SOCKET, &clilen);
         if (client_fd == -1) {
             if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // No connection available, continue loop
                continue;
            } else {
                // Handle other errors (e.g., log and exit)
                perror("accept");
                server_shutdown = true;
            }
                server_shutdown = true;
            }
                std::cout << "New connection received from: " << inet_ntoa(CLIENT_SOCKET.sin_addr)<< " Port: " << ntohs(CLIENT_SOCKET.sin_port) << std::endl;
                close(client_fd);

        }



    if (shutdown(client_fd, SHUT_RDWR) < 0) {
        std::cout << "Error shutting down client socket" << std::endl;
    }
      if (shutdown(server_fd, SHUT_RDWR) < 0) {
    std::cout << "error shutdown" << std::endl; return;
   }
    std::cout<<VT100_COLOR_GREEN<<"shutdown complete"<<VT100_COLOR_RESET<<std::endl;
    for (int delete_u = 0 ; delete_u < SERVER_CONFIG_t.WORKER.desiredWorkerNo ; delete_u++ ){
       delete [] WORKER_CLIENT_FD [delete_u];
  }
  delete [] WORKER_CLIENT_FD;
  delete [] Thread_ID;
  delete args;
return;
}


