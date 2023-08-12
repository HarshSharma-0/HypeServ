#include "config.hpp"
#include "parse_config.hpp"

#define in_server_file "/.IN-config.in";
std::string SERVER_CONFIG_DATA = "";  //holder of user input path or env to  configration file path

int setup_config_path(bool parse){

std::fstream Bashfile;//common stream to access all files
const char* config ="IN_SERVER"; // IN_SERVER config file env
const char* IN_CONFIG_PATH {0};
int WRITEHALT {0};

if(parse == true){
      IN_CONFIG_PATH = getenv("IN_SERVER"); //extracting IN_SERVER file path
         if(IN_CONFIG_PATH != nullptr){
              SERVER_CONFIG_DATA = IN_CONFIG_PATH; //copying to strinh IN_SERVER file
              SERVER_CONFIG_DATA += in_server_file; //adding file name 
              Bashfile.open(SERVER_CONFIG_DATA, std::ios::in);
              if(Bashfile.is_open()){
                parse_config_file(Bashfile);
              }
                else{
                     std::cout<<VT100_COLOR_RED<<"IN-config.in file opening error"<<VT100_COLOR_RESET<<std::endl; 
                     std::cout<<VT100_COLOR_BLUE<<"create config file now enter 1 else 0            "<<VT100_COLOR_RESET;
                     std::cin >> WRITEHALT;
                       if(WRITEHALT == 1){
                      Bashfile.open(SERVER_CONFIG_DATA , std::ios::out);
                      if(Bashfile.is_open()){
                          write_config_file(Bashfile);
                          Bashfile.close();
                          std::cout<<VT100_COLOR_GREEN<<"IN_config.in file writing sucess"<<std::endl;
         }
            else{
          std::cout<<VT100_COLOR_RED<<"in_config writing error using your path"<<VT100_COLOR_RESET<<std::endl;
          return -1;

          }

 } else{ return -1;}
            }
     }
      else{
     std::cout<<VT100_COLOR_RED<<"config path loading error or config path not set"<<VT100_COLOR_RESET<<std::endl;
     std::cout<<VT100_COLOR_BLUE<<"please set IN_SERVER env to .IN-config.in file path"<<VT100_COLOR_RESET<<std::endl;
     return -1;

  }

}else{
const char* bash_rc_path = getenv("BASH"); // BASH  env extraction

std::cout<<VT100_COLOR_GREEN<<"enter path or env for IN-config file"<<VT100_COLOR_YELLOW<<"[ env like ($my_variable) ] ---------- ";
std::cin>>SERVER_CONFIG_DATA;

if(SERVER_CONFIG_DATA[0] == '$'){ //checking for if the input is enviroment variable
SERVER_CONFIG_DATA.erase(0,1); //removing '$' sign
IN_CONFIG_PATH = getenv(SERVER_CONFIG_DATA.c_str()); //getting config file storage location
}

//code to set env to PATH

if (setenv(config,SERVER_CONFIG_DATA.c_str(),true) != -1) { //setting env of config file path

        std::cout<<VT100_COLOR_GREEN<< "Environment variable set successfully.\n";

      }
else {
        std::cout<<VT100_COLOR_RED<< "Failed to set environment variable.\n"<<VT100_COLOR_RESET<<std::endl;
        return -1;
      }



if(bash_rc_path != nullptr){ //checking of bashrc env if it not null to proceed safely

SERVER_CONFIG_DATA=bash_rc_path; //copying .bashrc path to strinh BASH_RC
SERVER_CONFIG_DATA += "/.bashrc";
Bashfile.open(SERVER_CONFIG_DATA,std::ios::out|std::ios::app);  //opening .bashrc file 

           if(Bashfile.is_open()){ //checking of file is opened or not
                Bashfile<<"\nexport IN_SERVER=$"<<SERVER_CONFIG_DATA;
                Bashfile.close();
                std::cout<<VT100_COLOR_GREEN<< "bashrc set successfully.\n"<<VT100_COLOR_RESET;
               }
              else  { // else statement for file opening
                  std::cout<<VT100_COLOR_RED<<"bashrc error"<<VT100_COLOR_RESET<<std::endl;
                  return -1;
                 }
SERVER_CONFIG_DATA.clear();
}
else{
std::cout<<VT100_COLOR_RED<<"BASHRC ($BASH) env error please reconfigure the path"<<SERVER_CONFIG_DATA<<VT100_COLOR_RESET<<std::endl;
return -1;
}


//code to write configration of server to IN_CONFIG.in
if(IN_CONFIG_PATH != nullptr){

SERVER_CONFIG_DATA=IN_CONFIG_PATH; //re-using BASH_RC variable for IN-config file path
SERVER_CONFIG_DATA += in_server_file;

Bashfile.open(SERVER_CONFIG_DATA , std::ios::out); // to open IN-config path
       if(Bashfile.is_open()){
              write_config_file(Bashfile);
              Bashfile.close();
              std::cout<<VT100_COLOR_GREEN<<"IN_config.in file writing sucess"<<std::endl;
              std::cout<<VT100_COLOR_GREEN<<"IN_config.in file path"<<SERVER_CONFIG_DATA<<std::endl;
         }
      else{
          std::cout<<VT100_COLOR_RED<<"in_config writing error using $(your_variable)"<<VT100_COLOR_RESET<<std::endl;
          return -1;
          }
}
else if(IN_CONFIG_PATH == nullptr)
{


SERVER_CONFIG_DATA += in_server_file;
Bashfile.open(SERVER_CONFIG_DATA , std::ios::out);

          if(Bashfile.is_open()){
              write_config_file(Bashfile);
              Bashfile.close();
              std::cout<<VT100_COLOR_GREEN<<"IN_config.in file writing sucess"<<std::endl;
         }
            else{
          std::cout<<VT100_COLOR_RED<<"in_config writing error using your path"<<VT100_COLOR_RESET<<std::endl;
          return -1;

          }

}else{
std::cout<<VT100_COLOR_RED<<"IN-CONFIG.IN writing error "<<std::endl;
}
}
std::cout<<VT100_COLOR_RESET;
return 1;
}
