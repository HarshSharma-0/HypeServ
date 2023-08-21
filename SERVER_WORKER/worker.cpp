#include "server.hpp"
#include "parse_config.hpp"

void *CLIENT_WORKER(void *args){
usleep(1000);
WORKER_THREAD_ARGS* ARGS = new WORKER_THREAD_ARGS;
std::memcpy( ARGS ,args, sizeof(WORKER_THREAD_ARGS));
std::cout<<ARGS->MAX_CLIENT<<std::endl;
std::cout<<ARGS->MOUNT_PATH<<std::endl;
ARGS->worker_id = pthread_self();
std::cout<<ARGS->worker_id<<std::endl;
delete ARGS;
return nullptr;
}
