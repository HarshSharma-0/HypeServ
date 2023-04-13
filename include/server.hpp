#ifndef SERVER
#define SERVER

extern int WORKER_NUMBER;
extern bool LOCAL_HOST;
extern int DESIRED_PORT;
extern char MOUNT_PATH[500];
extern int DESIRED_AUDIENCE;
extern int NETWORK_IP;

void server_start();

#endif
