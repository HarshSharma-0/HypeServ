#ifndef SERVER
#define SERVER

#include <pthread.h>
#include <unistd.h>
#include <csignal>
#include <atomic>

struct SERVER_CONFIG {
    char* serverName = nullptr;
    int portNumber {0};
    char* ipAddress = nullptr;
    char* mountPath = nullptr;
    bool isLocalHost {0};
    bool protocolHttps {0};
    char* proxy = nullptr;
    char* internalDnsResolver = nullptr;
struct WORKER {
    int desiredWorkerNo {0};
    int connectionPerWorker {0};
    char* mountPathWorker = nullptr;
}WORKER;
};
struct WORKER_THREAD_ARGS{
  int MAX_CLIENT  {0};
  char *MOUNT_PATH  = nullptr;
  int *CFD_DATA  = nullptr ;
  int *IN_ACTIVE_CFD = nullptr;
  pthread_t worker_id ;
  int worker_index = NULL ;
};
extern void SIGNAL_SIGINT_HANDLER(int signum);
extern SERVER_CONFIG SERVER_CONFIG_t;
extern void server_start();
extern bool parse_true;
extern void *CLIENT_WORKER(void *args);
extern bool server_shutdown;
extern std::atomic<std::int_fast32_t> INTERRUPT_WORKER_CNT;
extern std::atomic<std::int_fast8_t> INTERRUPT_ACTIVE;
#endif
