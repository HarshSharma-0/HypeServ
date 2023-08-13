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
        ServerStart = setup_config_path(true,IN_PATH);
    }
    else{
       std::cout<<VT100_COLOR_RED<< "Please setup IN_SERVER variable path"<<VT100_COLOR_RESET<<std::endl;
       std::cout<<VT100_COLOR_YELLOW<<"setup path if yes press 1 and enter else press 0 to exit ---------- "<<VT100_COLOR_RESET;
       std::cin>>path_setup;
 }
if(path_setup==1){
 ServerStart = setup_config_path(false,IN_PATH);
}
if(ServerStart == 1 && parse_true == true){
server_start();
}else{
std::cout<<VT100_COLOR_RED<<"Server bootup failed due to parsing error"<<VT100_COLOR_RESET<<std::endl;

}
    std::cout<<"\n";
    if (__cplusplus == 202101L) std::cout << "C++23";
    else if (__cplusplus == 202002L) std::cout << "C++20";
    else if (__cplusplus == 201703L) std::cout << "C++17";
    else if (__cplusplus == 201402L) std::cout << "C++14";
    else if (__cplusplus == 201103L) std::cout << "C++11";
    else if (__cplusplus == 199711L) std::cout << "C++98";
    else std::cout << "pre-standard C++." << __cplusplus;
    std::cout << "\n";


return 0;
}
