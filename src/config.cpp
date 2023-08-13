#include "config.hpp"
#include "parse_config.hpp"

#define in_server_file "/.IN-config.in";

std::string UNIVERSAL_DATA_STRING = "";  //holder of user input path or env to  configration file path

int setup_config_path(bool parse){

std::fstream Bashfile;//common stream to access all files
const char* config ="IN_SERVER"; // IN_SERVER config file env
const char* IN_CONFIG_PATH {0};
int WRITEHALT {0};

if(parse == true){
      IN_CONFIG_PATH = getenv("IN_SERVER"); //extracting IN_SERVER file path
         if(IN_CONFIG_PATH ){
              UNIVERSAL_DATA_STRING = IN_CONFIG_PATH; //copying to strinh IN_SERVER file
              UNIVERSAL_DATA_STRING += in_server_file; //adding file name 
              Bashfile.open(UNIVERSAL_DATA_STRING, std::ios::in);
              if(Bashfile.is_open()){
                parse_config_file(Bashfile);
              }
                else{
                     std::cout<<VT100_COLOR_RED<<"IN-config.in file opening error"<<VT100_COLOR_RESET<<std::endl; 
                     std::cout<<VT100_COLOR_BLUE<<"create config file now enter 1 else 0            "<<VT100_COLOR_RESET;
                     std::cin >> WRITEHALT;
                      if(WRITEHALT == 1){
                      Bashfile.open(UNIVERSAL_DATA_STRING , std::ios::out);
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

}
else {


const char* bash_rc_path = getenv("BASH"); // BASH  env extraction

std::cout<<VT100_COLOR_GREEN<<"enter path or env for IN-config file"<<VT100_COLOR_YELLOW<<"[ env like ($my_variable) ] ---------- ";
std::cin>>UNIVERSAL_DATA_STRING;

if(UNIVERSAL_DATA_STRING[0] == '$'){ //checking for if the input is enviroment variable
UNIVERSAL_DATA_STRING.erase(0,1); //removing '$' sign
IN_CONFIG_PATH = getenv(UNIVERSAL_DATA_STRING.c_str()); //getting config file storage location
}

//code to set env to PATH

if (setenv(config,UNIVERSAL_DATA_STRING.c_str(),true) != -1) { //setting env of config file path

        std::cout<<VT100_COLOR_GREEN<< "Environment variable set successfully.\n";

      }
else {
        std::cout<<VT100_COLOR_RED<< "Failed to set environment variable.\n"<<VT100_COLOR_RESET<<std::endl;
        return -1;
      }



if(bash_rc_path){ //checking of bashrc env if it not null to proceed safely

UNIVERSAL_DATA_STRING = bash_rc_path; //copying .bashrc path to strinh BASH_RC
UNIVERSAL_DATA_STRING += "/.bashrc";
Bashfile.open(UNIVERSAL_DATA_STRING,std::ios::out|std::ios::app);  //opening .bashrc file 

           if(Bashfile.is_open()){ //checking of file is opened or not
                Bashfile<<"\nexport IN_SERVER=$"<<UNIVERSAL_DATA_STRING;
                Bashfile.close();
                std::cout<<VT100_COLOR_GREEN<< "bashrc set successfully.\n"<<VT100_COLOR_RESET;
               }
              else  { // else statement for file opening
                  std::cout<<VT100_COLOR_RED<<"bashrc error"<<VT100_COLOR_RESET<<std::endl;
                  return -1;
                 }
UNIVERSAL_DATA_STRING.clear();
}
else{
std::cout<<VT100_COLOR_RED<<"BASHRC ($BASH) env error please reconfigure the path"<<UNIVERSAL_DATA_STRING<<VT100_COLOR_RESET<<std::endl;
return -1;
}


//code to write configration of server to IN_CONFIG.in
if(IN_CONFIG_PATH){

UNIVERSAL_DATA_STRING=IN_CONFIG_PATH; //re-using BASH_RC variable for IN-config file path
UNIVERSAL_DATA_STRING += in_server_file;

Bashfile.open(UNIVERSAL_DATA_STRING , std::ios::out); // to open IN-config path
       if(Bashfile.is_open()){
              write_config_file(Bashfile);
              Bashfile.close();
              std::cout<<VT100_COLOR_GREEN<<"IN_config.in file writing sucess"<<std::endl;
              std::cout<<VT100_COLOR_GREEN<<"IN_config.in file path"<<UNIVERSAL_DATA_STRING<<std::endl;
         }
      else{
          std::cout<<VT100_COLOR_RED<<"in_config writing error using $(your_variable)"<<VT100_COLOR_RESET<<std::endl;
          return -1;
          }
}
else
{
UNIVERSAL_DATA_STRING += in_server_file;
Bashfile.open(UNIVERSAL_DATA_STRING , std::ios::out);

          if(Bashfile.is_open()){
              write_config_file(Bashfile);
              Bashfile.close();
              std::cout<<VT100_COLOR_GREEN<<"IN_config.in file writing sucess"<<std::endl;
         }
            else{
          std::cout<<VT100_COLOR_RED<<"in_config writing error using your path"<<VT100_COLOR_RESET<<std::endl;
          return -1;

          }

}
}
std::cout<<VT100_COLOR_RESET;
return 1;
}
