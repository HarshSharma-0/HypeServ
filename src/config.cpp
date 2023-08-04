#include "config.hpp"
#include <fstream>
#include <iostream>
#include <VT100.hpp>
#include <string>
#include <cstdlib>

int setup_config_path(){

std::fstream Bashfile; // stream to access .bashrc
std::fstream inconfig; //stream to access  IN-config

const char* bash_rc_path = getenv("BASH"); // BASH  env extraction
const char* config ="IN_SERVER"; // IN_SERVER config file env
const char* IN_CONFIG_PATH {0};
std::string BASH_RC =""; // holder of .bashrc path
std::string config_value = "";  //holder of user input path or env to  configration file path

std::cout<<VT100_COLOR_GREEN<<"enter path or env for IN-config file"<<VT100_COLOR_YELLOW<<"[ env like ($my_variable) ] ---------- ";
std::cin>>config_value;

if(config_value[0] == '$'){ //checking for if the input is enviroment variable
config_value.erase(0,1); //removing '$' sign 
IN_CONFIG_PATH = getenv(config_value.c_str()); //getting config file storage location 
}

if (setenv(config,config_value.c_str(),true) != -1) { //setting env of config file path

        std::cout<<VT100_COLOR_GREEN<< "Environment variable set successfully.\n";

      }
else {
        std::cout<<VT100_COLOR_RED<< "Failed to set environment variable.\n"<<VT100_COLOR_RESET;
        return -1;
      }

if(bash_rc_path != nullptr){ //checking of bashrc env if it null to proceed safely

BASH_RC=bash_rc_path; //copying .bashrc path to strinh BASH_RC
BASH_RC += "/.bashrc";
Bashfile.open(BASH_RC,std::ios::out|std::ios::app);  //opening .bashrc file 

           if(Bashfile.is_open()){ //checking of file is opened or not
                Bashfile<<"\nexport IN_SERVER=$"<<config_value;
                Bashfile.close();
                std::cout<<VT100_COLOR_GREEN<< "bashrc set successfully.\n"<<VT100_COLOR_RESET;
               }
              else  { // else statement for file opening
                  std::cout<<VT100_COLOR_RED<<"bashrc error"<<VT100_COLOR_RESET<<std::endl;
                  return -1;
                 }
BASH_RC.clear();
}
else{
std::cout<<VT100_COLOR_RED<<"BASHRC ($BASH) env error please reconfigure the path"<<BASH_RC<<VT100_COLOR_RESET<<std::endl;
return -1;
}


//code to write configration of server to IN_CONFIG.in
if(IN_CONFIG_PATH != nullptr){

BASH_RC=IN_CONFIG_PATH; //re-using BASH_RC variable for IN-config file path
BASH_RC += "/.IN-config.in";
inconfig.open(BASH_RC , std::ios::out); // to open IN-config path
       if(inconfig.is_open()){
              inconfig<<"heloo"<<std::endl;
              inconfig.close();
              std::cout<<VT100_COLOR_GREEN<<"IN_config.in file writing sucess"<<std::endl;
              std::cout<<VT100_COLOR_GREEN<<"IN_config.in file path"<<BASH_RC<<std::endl;
         }
      else{
          std::cout<<VT100_COLOR_RED<<"in_config writing error using $(your_variable)"<<VT100_COLOR_RESET<<std::endl;
          return -1;
          }
}
else if(IN_CONFIG_PATH == nullptr)
{
config_value += "/.IN-CONFIG.in";
inconfig.open(config_value , std::ios::out);

          if(inconfig.is_open()){
              inconfig<<"heloo"<<std::endl;
              inconfig.close();
              std::cout<<VT100_COLOR_GREEN<<"IN_config.in file writing sucess"<<std::endl;
         }
            else{
          std::cout<<VT100_COLOR_RED<<"in_config writing error using your path"<<VT100_COLOR_RESET<<std::endl;
          return -1;
           
          }

}else{
std::cout<<VT100_COLOR_RED<<"IN-CONFIG.IN writing error "<<std::endl;
}
std::cout<<VT100_COLOR_RESET;
return 0;
}
