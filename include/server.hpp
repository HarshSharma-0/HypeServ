#ifndef SERVER
#define SERVER

struct SERVER_CONFIG {
    char* serverName {0};
    int portNumber {0};
    char* ipAddress {0};
    char* mountPath {0};
    bool isLocalHost {0};
    bool protocolHttps {0};
    char* proxy {0};
    char* internalDnsResolver {0};
struct WORKER {
    int desiredWorkerNo {0};
    int connectionPerWorker {0};
    char* mountPathWorker {0};
}WORKER;
};
extern SERVER_CONFIG SERVER_CONFIG_t;
extern void server_start();

#endif
