#include "server.hpp"
#include "parse_config.hpp"

void *CLIENT_WORKER(void *args){
WORKER_THREAD_ARGS* ARGS = new WORKER_THREAD_ARGS();
std::memcpy( ARGS ,args, sizeof(WORKER_THREAD_ARGS));
ARGS->worker_id = pthread_self();
for(int I = 0 ; I < ARGS -> MAX_CLIENT ; I++){ std::cout<<" "<<ARGS->CFD_DATA[I]<<" "<<ARGS->IN_ACTIVE_CFD[I]<<" ";}
std::cout<<std::endl;


delete ARGS;
return nullptr;
}
