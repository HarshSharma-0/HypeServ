#include "server.hpp"
#include "parse_config.hpp"

void *CLIENT_WORKER(void *args){
WORKER_THREAD_ARGS* ARGS = new WORKER_THREAD_ARGS;
std::memcpy( ARGS ,args, sizeof(WORKER_THREAD_ARGS));
ARGS->worker_id = pthread_self();
for(int i=0;i<ARGS->MAX_CLIENT;i++){std::cout<<" "<<ARGS->CFD_DATA[i]<<" ";}
std::cout<<std::endl;


delete ARGS;
return nullptr;
}
