#include "server.hpp"
#include "parse_config.hpp"

void *CLIENT_WORKER(void *args){
bool worker_shutdown = false;
WORKER_THREAD_ARGS* ARGS = new WORKER_THREAD_ARGS();
std::memcpy( ARGS ,args, sizeof(WORKER_THREAD_ARGS));
ARGS->worker_id = pthread_self();
while(worker_shutdown != true){
//all worker code
if(INTERRUPT_ACTIVE == 1){break;}
}


delete ARGS;
INTERRUPT_WORKER_CNT++;
return nullptr;
}
