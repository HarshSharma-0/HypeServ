#include "config.hpp"
#include <fstream>
#include <iostream>
#include <VT100.hpp>
#include <string>
#include <cstdlib>

int setup_config_path(){
std::fstream Bashfile;
const char* bash_rc_path = getenv("BASH");
const char* config ="IN_SERVER";
std::string BASH_RC ="";
std::string config_value = "";
std::string bashrc_input = "";
std::cout<<VT100_COLOR_GREEN<<"Set your configration path or just enter the env variable pointing to that path include"<<VT100_COLOR_YELLOW<<"($)"<<VT100_COLOR_GREEN<<" also before env variable name example ($my_variable)";
std::cin>>config_value;
if (setenv(config,config_value.c_str(),true) != -1) {
        std::cout << "Environment variable set successfully.\n";
       

    } else {
        std::cout << "Failed to set environment variable.\n";
        return -1;
    }
if(bash_rc_path != nullptr){
BASH_RC=bash_rc_path;
Bashfile.open(BASH_RC,std::ios::out|std::ios::app);
if(Bashfile.is_open()){
 Bashfile<<"export IN_SERVER="<<config_value;
 Bashfile.close();
 std::cout << "bashrc set successfully.\n";
}
else{
std::cout<<VT100_COLOR_RED<<"bashrc error"<<std::endl;
return -1;
}
}
else{
std::cout<<VT100_COLOR_RESET<<"exiting"<<std::endl;
return -1;
}

return 0;
}
