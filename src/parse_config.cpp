#include "parse_config.hpp"
#include "server.hpp"

void BREAK_HALT(std::fstream& FILE_DATA ,int tag_extraction);
char* allocateAndCopy(char*& parse_store, std::string& parseValue);



void parse_config_file(std::fstream& in_config_parse){

int check_hit {0};
bool parse_stop = false;
bool parse_stop_server = false;
bool parse_stop_worker = false;
//parser loop starts

while (parse_stop != true){ //parser condition

UNIVERSAL_DATA_STRING.clear(); //clearing the buffer
if(!std::getline(in_config_parse,UNIVERSAL_DATA_STRING,'\n')){std::cout<<VT100_COLOR_RED<<"EOF reached and parsing unsucessfull"<<VT100_COLOR_RESET<<std::endl; parse_true = false; return;}  //reading from file the first line

if(UNIVERSAL_DATA_STRING == "SERVER:"){    //checking for SERVER LABEL

     while (parse_stop_server !=true ){    //server lable parser

    BREAK_HALT(in_config_parse,1);
// ********************************************************* checking the buffer if matched with any of the tag  ********************************************************


              if (UNIVERSAL_DATA_STRING == "-SERVER-NAME"){
                    BREAK_HALT(in_config_parse,0);
                    SERVER_CONFIG_t.serverName = allocateAndCopy(SERVER_CONFIG_t.serverName,UNIVERSAL_DATA_STRING); // Null-terminate the string
                   }
              else if (UNIVERSAL_DATA_STRING == "-PORT-NUMBER"){
                    BREAK_HALT(in_config_parse,0);
                    SERVER_CONFIG_t.portNumber = std::stoi(UNIVERSAL_DATA_STRING);
                   }
              else if (UNIVERSAL_DATA_STRING == "-IP-ADDRESS"){
                   BREAK_HALT(in_config_parse,0);
                   SERVER_CONFIG_t.ipAddress = allocateAndCopy(SERVER_CONFIG_t.ipAddress,UNIVERSAL_DATA_STRING);
                   }
              else if(UNIVERSAL_DATA_STRING == "-MOUNT-PATH"){
                   BREAK_HALT(in_config_parse,0);
                   SERVER_CONFIG_t.mountPath = allocateAndCopy(SERVER_CONFIG_t.mountPath,UNIVERSAL_DATA_STRING);
                   }
              else if(UNIVERSAL_DATA_STRING == "-LOCAL-HOST"){
                   BREAK_HALT(in_config_parse,0);
                   SERVER_CONFIG_t.isLocalHost = (UNIVERSAL_DATA_STRING == "1") ? true : false ;
                   }
              else if(UNIVERSAL_DATA_STRING == "-PROTOCOL-HTTPs"){
                   BREAK_HALT(in_config_parse,0);
                   SERVER_CONFIG_t.protocolHttps = (UNIVERSAL_DATA_STRING == "1") ? true : false ;
                   }
              else if (UNIVERSAL_DATA_STRING == "-PROXY"){
                   BREAK_HALT(in_config_parse,0);
                   SERVER_CONFIG_t.proxy = allocateAndCopy(SERVER_CONFIG_t.proxy,UNIVERSAL_DATA_STRING);
                   }
              else if (UNIVERSAL_DATA_STRING == "-INTERNAL-DNS-RESOLVER"){
                   BREAK_HALT(in_config_parse,0);
                   SERVER_CONFIG_t.internalDnsResolver = allocateAndCopy(SERVER_CONFIG_t.internalDnsResolver,UNIVERSAL_DATA_STRING);
                   }
              else if(UNIVERSAL_DATA_STRING == "@end"){
                   parse_stop_server = true;
                   }else{ check_hit++ ; if(check_hit == 1){std::cout<<VT100_COLOR_RED<<"Parsing error please see or correct syntax or variable name of file in SERVER: tag section"<<VT100_COLOR_RESET; check_hit = 0; parse_true = false; return;} continue;}

}
}
// ********************************************************************************************************************************************************************

// *************************************************** checking buffer for WORKER tag *********************************************************************************

else if ( UNIVERSAL_DATA_STRING == "WORKER:" ) {

           while( parse_stop_worker != true ){
                  BREAK_HALT(in_config_parse,1);
                    if (UNIVERSAL_DATA_STRING == "-DESIRED-WORKER-NO") {
                          BREAK_HALT(in_config_parse,0);
                          SERVER_CONFIG_t.WORKER.desiredWorkerNo = std::stoi(UNIVERSAL_DATA_STRING);
                       }
                    else if( UNIVERSAL_DATA_STRING == "-CONNECTION-PER-WORKER"){
                          BREAK_HALT(in_config_parse,0);
                          SERVER_CONFIG_t.WORKER.connectionPerWorker = std::stoi(UNIVERSAL_DATA_STRING);
                       }
                    else if (UNIVERSAL_DATA_STRING == "-MOUNT-PATH-WORKER" ){
                          BREAK_HALT(in_config_parse,0);
                          SERVER_CONFIG_t.WORKER.mountPathWorker = allocateAndCopy(SERVER_CONFIG_t.WORKER.mountPathWorker,UNIVERSAL_DATA_STRING);
                       }
                    else if(UNIVERSAL_DATA_STRING == "@end") {
                        parse_stop_worker = true ;
                       }
                    else{ check_hit++ ; if(check_hit == 1){std::cout<<VT100_COLOR_RED<<"Parsing error please see or correct syntax or variable name of file in WORKER: tag section"<<VT100_COLOR_RESET<<std::endl; check_hit = 0; parse_true = false; return;} continue;}
}
}

// ********************************************************************************************************************************************************************

else{
     if( parse_stop_worker == true && parse_stop_server == true ){  // checkibg for if parsing is completed 
        std::cout<<VT100_COLOR_GREEN<<"PARSING SUCESSFULL"<<VT100_COLOR_RESET<<std::endl;
        parse_true = true;;
        parse_stop = true;
      }
continue;
}
}
return;
}

// ********************************************************************************************************************************************************************
void BREAK_HALT(std::fstream& FILE_DATA,int tag_extraction){

if(tag_extraction == 1){
     UNIVERSAL_DATA_STRING.clear();                               //clearing the buffer
     std::getline(FILE_DATA,UNIVERSAL_DATA_STRING,'<');    // checking for tag data
     UNIVERSAL_DATA_STRING.erase(std::remove(UNIVERSAL_DATA_STRING.begin(),UNIVERSAL_DATA_STRING.end(),' '),UNIVERSAL_DATA_STRING.end());
     UNIVERSAL_DATA_STRING.erase(std::remove(UNIVERSAL_DATA_STRING.begin(),UNIVERSAL_DATA_STRING.end(),'\n'),UNIVERSAL_DATA_STRING.end());

}
else{
UNIVERSAL_DATA_STRING.clear();
std::getline(FILE_DATA,UNIVERSAL_DATA_STRING,'>');
}
return;

}

// ********************************************************************************************************************************************************************

char* allocateAndCopy(char*& parse_store, std::string& parseValue){

parse_store = new char[parseValue.size()+1];
std::copy(parseValue.begin(),parseValue.end(),parse_store);
parse_store[parseValue.size()] = '\0' ;
return parse_store;

}

