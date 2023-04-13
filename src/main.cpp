// code for server
#include "server.hpp"
#include <iostream>
//bool LOCAL_HOST {false};
//int DESIRED_PORT {0};
//char MOUNT_PATH[500];
//int DESIRED_AUDIENCE {0};
//int NETWORK_IP {0};

int main() {
  // fstream confile;
  // lconfile.open("/share/.AN-CODE");
  std::cout << "***************** SERVER SETUP *********************"
            << std::endl;
  std::cout << "\033[1;33mDesired number of worker node \033[1;32m"
            << "       ";
  std::cin >> WORKER_NUMBER;
  std::cout << "\033[0m"
            << "\033[1;33mDesired audience perworker   \033[1;32m"
            << "        ";
  std::cin >> DESIRED_AUDIENCE;
  std::cout << "\033[1;33mlocalhost (1/0)(default 0)"
            << "           ";
  std::cin >> LOCAL_HOST;
  std::cin.clear();
  std::cout << "\x1b[Alaunch localhost server         "
            << "     ";
  (LOCAL_HOST == 1) ? std::cout << "\033[1;32mTRUE" << std::endl
                    : std::cout << "\033[1;31mFALSE" << std::endl;
  std::cout << "\033[1;33mDesired Port (default 80)    \033[1;32m"
            << "        ";
  std::cin >> DESIRED_PORT;
  std::cout << "\033[1;33mPath to be mounted          \033[1;32m"
            << "         ";
  std::cin >> MOUNT_PATH;
  std::cout << "\033[1;33mselect network              \033[1;32m "
            << "        ";
  std::cin >> NETWORK_IP;
  std::cout << "\033[0m****************************************************"<< std::endl;
  // ip_address();
   server_start();
}
