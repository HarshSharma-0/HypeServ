#include "config.hpp"
#include "parse_config.hpp"
#define in_server_file "/.IN-config.in";

std::fstream ConfigFile;
const char* IN_CONFIG_PATH {0};
std::string UNIVERSAL_DATA_STRING = "";
int getenv_and_openfile(std::string& file_path);
int ret_val = 0;

int setup_config_path(bool parse, std::string& PATH){

if(parse == true){
PATH += in_server_file;
    ret_val = getenv_and_openfile(PATH);
      if(ret_val == 0){
      parse_config_file(ConfigFile);
     }else if (ret_val == 1){
      write_config_file(ConfigFile);
      ConfigFile.open(PATH,std::ios::in);
      parse_config_file(ConfigFile);
      ConfigFile.close();
     }else{return -1;}


}
else {

}
return 1;
}


int getenv_and_openfile(std::string& file_path){
int sucess_code = 0;
if (std::filesystem::exists(file_path)) {
 ConfigFile.open(file_path,std::ios::in);
 sucess_code = 0;
}else{ sucess_code = 1; ConfigFile.open(file_path,std::ios::out); }
if(ConfigFile.is_open()){} else{ sucess_code = -1;}

return sucess_code;

}
