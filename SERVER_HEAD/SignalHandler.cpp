#include "server.hpp"
#include "config.hpp"
void SIGNAL_SIGINT_HANDLER(int signum){
server_shutdown = true;
std::cout<<VT100_COLOR_RED<<"Going for nominal exit for signal ctrl+c"<<VT100_COLOR_RESET<<std::endl;
INTERRUPT_WORKER_CNT = 0;
INTERRUPT_ACTIVE = 1;
return ;
}
