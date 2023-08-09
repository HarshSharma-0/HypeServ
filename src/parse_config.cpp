#include "parse_config.hpp"

int parse_config_file(std::fstream& in_config_parse){
bool parse_stop = false;
while (parse_stop != true){
std::getline(in_config_parse,SERVER_CONFIG_DATA,'\n');
if(SERVER_CONFIG_DATA == "SERVER:"){
SERVER_CONFIG_DATA.clear();
std::getline(in_config_parse,SERVER_CONFIG_DATA,'<');
std::cout<<SERVER_CONFIG_DATA;
}
parse_stop = true;

}

return 0;
}
