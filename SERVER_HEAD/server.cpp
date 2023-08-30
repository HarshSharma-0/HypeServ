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
 int **WORKER_CLOSEDFD_INDEX = nullptr;
 bool server_shutdown = false;
 WORKER_THREAD_ARGS* args = nullptr;
 pthread_t *Thread_ID = nullptr;

 std::atomic<std::int_fast32_t> INTERRUPT_WORKER_CNT = 0;
 std::atomic<std::int_fast8_t> INTERRUPT_ACTIVE = 0;

 int close_and_cleanup(int &server_FD);
 int listen_connection(int &server_fd , int &client_fd , socklen_t &clilen , struct sockaddr_in *CLIENT_SOCKET);
 int create_matFD_thread();
 int create_server_FD(int &server_fd , struct sockaddr_in *SERVER_SOCKET , socklen_t &socket_len);

 void server_start() {

     struct sockaddr_in SERVER_SOCKET, CLIENT_SOCKET;

     int server_fd {0};
     int client_fd {0};

     signal(SIGINT, SIGNAL_SIGINT_HANDLER);
     args = new WORKER_THREAD_ARGS ();
     Thread_ID = new pthread_t[SERVER_CONFIG_t.WORKER.desiredWorkerNo];

     socklen_t clilen = sizeof(CLIENT_SOCKET);
     socklen_t socket_len = sizeof(SERVER_SOCKET);
     int *SERVER_LOAD = new int[SERVER_CONFIG_t.WORKER.desiredWorkerNo]();

     args-> MOUNT_PATH = SERVER_CONFIG_t.WORKER.mountPathWorker;
     args-> MAX_CLIENT = SERVER_CONFIG_t.WORKER.connectionPerWorker;
     WORKER_CLIENT_FD = new int*[SERVER_CONFIG_t.WORKER.desiredWorkerNo]();
     WORKER_CLOSEDFD_INDEX = new int*[SERVER_CONFIG_t.WORKER.desiredWorkerNo]();

     if ( create_server_FD( server_fd , &SERVER_SOCKET , socket_len ) != 0 ){ return; }

     if ( create_matFD_thread() != 0 ){ return; }

     listen_connection( server_fd , client_fd , clilen , &CLIENT_SOCKET );
     close_and_cleanup(server_fd);
   return;
 }



int create_server_FD(int &server_fd , struct sockaddr_in *SERVER_SOCKET , socklen_t &socket_len){
     server_fd = socket(AF_INET, SOCK_STREAM, 0);
     int NON_BLOCKING_FLAG = 0 ;
     SERVER_SOCKET->sin_family = AF_INET;
     SERVER_SOCKET->sin_port = htons(SERVER_CONFIG_t.portNumber);

    if (server_fd < 0) {
     std::cout << "error createing socket  " << strerror(errno) << std::endl; return 1;
    };

   NON_BLOCKING_FLAG = fcntl(server_fd, F_GETFL, 0);
   fcntl(server_fd, F_SETFL, NON_BLOCKING_FLAG | O_NONBLOCK);


   if (inet_pton(AF_INET,SERVER_CONFIG_t.ipAddress, &SERVER_SOCKET->sin_addr) == 1){ std::cout<<VT100_COLOR_GREEN<<"Network IP conversion sucess"<<VT100_COLOR_RESET<<std::endl; }
   else{ std::cout<<VT100_COLOR_RED<<"Error converting IP address to Network format (might be due to error in config file format[.IN-config.in in -IP-ADDRESS] or IP format) "<<strerror(errno)<<VT100_COLOR_RESET<<std::endl; return 1;};


   if (bind(server_fd, (struct sockaddr *)SERVER_SOCKET, socket_len) < 0) {
     std::cout << "\nerror binding\n" <<  ntohs(SERVER_SOCKET->sin_port) << strerror(errno);
     return 1;
   };

   if (listen(server_fd, 3) < 0) {
     std::cout << "error listening" << std::endl; return 1;
   }
   std::cout<<VT100_COLOR_MAGENTA<< "\nSERVER started on IP: " <<VT100_COLOR_CYAN<< inet_ntoa(SERVER_SOCKET->sin_addr)<< ":" << ntohs(SERVER_SOCKET->sin_port) <<VT100_COLOR_RESET<< std::endl;

return 0;

}





int create_matFD_thread(){

  if( WORKER_CLIENT_FD == nullptr ) { return 1; }
     for (int i = 0; i < SERVER_CONFIG_t.WORKER.desiredWorkerNo ; i++) {
         WORKER_CLIENT_FD[i] = new int[SERVER_CONFIG_t.WORKER.connectionPerWorker];
         std::fill_n (WORKER_CLIENT_FD[i],SERVER_CONFIG_t.WORKER.connectionPerWorker, -1 );
         if(WORKER_CLIENT_FD[i] == nullptr){ return 1; }

     }

    for(int J = 0 ; J < SERVER_CONFIG_t.WORKER.desiredWorkerNo ; J++){
          args-> MOUNT_PATH = SERVER_CONFIG_t.WORKER.mountPathWorker;
          args-> MAX_CLIENT = SERVER_CONFIG_t.WORKER.connectionPerWorker;
          args-> CFD_DATA = &WORKER_CLIENT_FD [J][0];
          args-> IN_ACTIVE_CFD = new int[SERVER_CONFIG_t.WORKER.connectionPerWorker]();
          WORKER_CLOSEDFD_INDEX [J] = args->IN_ACTIVE_CFD;
          std::fill_n (args->IN_ACTIVE_CFD,SERVER_CONFIG_t.WORKER.connectionPerWorker, -1 );
          args->worker_index = J ;
          if(pthread_create(&Thread_ID [J], nullptr , CLIENT_WORKER , (void*)args) != 0 ){
          std::cout<<strerror(errno)<<std::endl; return 1;
          }
         usleep(1000);


   }


return 0;

}

int listen_connection(int &server_fd , int &client_fd , socklen_t &clilen , struct sockaddr_in *CLIENT_SOCKET ){

   while ( server_shutdown != true ){
          client_fd = accept(server_fd,(struct sockaddr *)CLIENT_SOCKET, &clilen);
          if (client_fd == -1) {
              if (errno == EAGAIN || errno == EWOULDBLOCK) {

                 continue;
             } else {
                 perror("accept");
                 server_shutdown = true;
             }
                 server_shutdown = true;
             }

                 std::cout << "New connection received from: " << inet_ntoa(CLIENT_SOCKET->sin_addr)<< " Port: " << ntohs(CLIENT_SOCKET->sin_port) << std::endl;


         }

return 0;

}



int close_and_cleanup(int &server_FD){

for(int O = 0 ; O < SERVER_CONFIG_t.WORKER.desiredWorkerNo; O++){
       for(int C = 0 ; C < SERVER_CONFIG_t.WORKER.connectionPerWorker ; C++){
             if( WORKER_CLIENT_FD [O][C] != -1 ){ close (WORKER_CLIENT_FD [O][C] );} else{ continue; }
         }
      }
    if (shutdown(server_FD, SHUT_RDWR) < 0) {
     std::cout << "error shutdown" << std::endl;
    }
     std::cout<<VT100_COLOR_GREEN<<"\nSHUTDOWN COMPLETE"<<VT100_COLOR_RESET<<std::endl;
     for (int delete_u = 0 ; delete_u < SERVER_CONFIG_t.WORKER.desiredWorkerNo ; delete_u++ ){
        delete [] WORKER_CLIENT_FD [delete_u];
   }
   while(INTERRUPT_WORKER_CNT != SERVER_CONFIG_t.WORKER.desiredWorkerNo){
continue ;
    }
  std::cout<<VT100_COLOR_GREEN<<"\nALL WORKER ARE DOWN EXIT STATUS POSITIVE"<<VT100_COLOR_RESET<<std::endl;
   delete [] WORKER_CLIENT_FD;
   delete [] Thread_ID;
   delete args;

return 0;

}

