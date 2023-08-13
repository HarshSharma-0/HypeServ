#ifndef PARSE_CONFIG
#define PARSE_CONFIG
#include <fstream>
#include <iostream>
#include <VT100.hpp>
#include <string>
#include <cstdlib>
extern void parse_config_file(std::fstream& in_config_parse);
extern void write_config_file(std::fstream& in_config_write);
extern std::string UNIVERSAL_DATA_STRING;  //holder of user input path or env to  configration file path
#endif
