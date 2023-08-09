#ifndef PARSE_CONFIG
#define PARSE_CONFIG
#include <fstream>
#include <iostream>
#include <VT100.hpp>
#include <string>
#include <cstdlib>
extern int parse_config_file(std::fstream& in_config_parse);
extern std::string SERVER_CONFIG_DATA;  //holder of user input path or env to  configration file path
#endif
