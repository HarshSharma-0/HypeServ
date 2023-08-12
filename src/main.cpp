#include <iostream>
#include <cstdlib>
#include <VT100.hpp>
#include <config.hpp>
#include <server.hpp>

int main() {
    char *config_path= getenv("IN_SERVER");
    std::string IN_PATH = "";
    int path_setup {0};
    int ServerStart {0};
     if (config_path != NULL) {
       IN_PATH = config_path;
       std::cout<<VT100_COLOR_GREEN<<"PATH set to "<<IN_PATH<<VT100_COLOR_RESET<<std::endl;
        ServerStart = setup_config_path(true);
    }
    else{
       std::cout<<VT100_COLOR_RED<< "Please setup IN_SERVER variable path"<<VT100_COLOR_RESET<<std::endl;
       std::cout<<VT100_COLOR_YELLOW<<"setup path if yes press 1 and enter else press 0 to exit ---------- "<<VT100_COLOR_RESET;
       std::cin>>path_setup;
 }
if(path_setup==1){
 ServerStart = setup_config_path(false);
}
if(ServerStart == 1 && parse_true == true){
server_start();
}else{
std::cout<<VT100_COLOR_RED<<"Server bootup failed due to parsing error"<<VT100_COLOR_RESET<<std::endl;

}


return 0;
}
