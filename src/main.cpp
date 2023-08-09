#include <server.hpp>
#include <iostream>
#include <cstdlib>
#include <VT100.hpp>
#include <config.hpp>

int main() {
    char *config_path= getenv("IN_SERVER");
    std::string IN_PATH = "";
    int path_setup {0};

     if (config_path != NULL) {
       IN_PATH = config_path;
       std::cout<<VT100_COLOR_GREEN<<"PATH set to "<<IN_PATH<<VT100_COLOR_RESET<<std::endl;
         setup_config_path(true);
    }
    else{
       std::cout<<VT100_COLOR_RED<< "Please setup IN_SERVER variable path"<<VT100_COLOR_RESET<<std::endl;
       std::cout<<VT100_COLOR_YELLOW<<"setup path if yes press 1 and enter else press 0 to exit ---------- "<<VT100_COLOR_RESET;
       std::cin>>path_setup;
 }
if(path_setup==1){
 setup_config_path(false);
}
else

/*
  std::cout << "***************** SERVER SETUP *********************"
            << std::endl;
  std::cout << "\033[1;
  33mDesired number of worker node \033[1;32m"
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
*/
   //server_start();

return 0;
}
