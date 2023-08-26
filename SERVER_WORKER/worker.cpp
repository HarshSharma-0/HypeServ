#include "server.hpp"
#include "parse_config.hpp"

void *CLIENT_WORKER(void *args){
WORKER_THREAD_ARGS* ARGS = new WORKER_THREAD_ARGS();
std::memcpy( ARGS ,args, sizeof(WORKER_THREAD_ARGS));
ARGS->worker_id = pthread_self();


delete ARGS;
return nullptr;
}
