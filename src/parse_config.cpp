#include "parse_config.hpp"
#include "server.hpp"

void parse_config_file(std::fstream& in_config_parse){
int check_hit {0};
bool parse_stop = false;
bool parse_stop_server = false;
bool parse_stop_worker = false;
//parser loop starts

while (parse_stop != true){ //parser condition

SERVER_CONFIG_DATA.clear(); //clearing the buffer
if(!std::getline(in_config_parse,SERVER_CONFIG_DATA,'\n')){std::cout<<VT100_COLOR_RED<<"EOF reached and parsing unsucessfull"<<VT100_COLOR_RESET<<std::endl; parse_true = false; return;}  //reading from file the first line

if(SERVER_CONFIG_DATA == "SERVER:"){    //checking for SERVER LABEL

     while (parse_stop_server !=true ){    //server lable parser

SERVER_CONFIG_DATA.clear();                               //clearing the buffer
std::getline(in_config_parse,SERVER_CONFIG_DATA,'<');    // checking for tag data

SERVER_CONFIG_DATA.erase(std::remove(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),' '),SERVER_CONFIG_DATA.end());         // erasing soaces from data
SERVER_CONFIG_DATA.erase(std::remove(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),'\n'),SERVER_CONFIG_DATA.end());       // erasing \n marker from data

// ********************************************************* checking the buffer if matched with any of the tag  ********************************************************


              if (SERVER_CONFIG_DATA == "-SERVER-NAME"){
                    BREAK_HALT(in_config_parse);
                    SERVER_CONFIG_t.serverName = new char[SERVER_CONFIG_DATA.size()+1];
                    if (SERVER_CONFIG_t.serverName == nullptr) { std::cout<<VT100_COLOR_RED<<"While parsing memory allcocation failed for serverName"<<VT100_COLOR_RESET<<std::endl; return; }
                    std::copy(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),SERVER_CONFIG_t.serverName);
                    SERVER_CONFIG_t.serverName[SERVER_CONFIG_DATA.size()] = '\0'; // Null-terminate the string
                   }
              else if (SERVER_CONFIG_DATA == "-PORT-NUMBER"){
                    BREAK_HALT(in_config_parse);
                    SERVER_CONFIG_t.portNumber = std::stoi(SERVER_CONFIG_DATA);
                   }
              else if (SERVER_CONFIG_DATA == "-IP-ADDRESS"){
                   BREAK_HALT(in_config_parse);
                   SERVER_CONFIG_t.ipAddress = new char[SERVER_CONFIG_DATA.size()+1];
                   if (SERVER_CONFIG_t.ipAddress == nullptr){ std::cout<<VT100_TEXT_BLINK<<VT100_COLOR_RED<<"While parsing memory allcocation failed for serveripaddress"<<VT100_COLOR_RESET<<std::endl; return;}
                   std::copy(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),SERVER_CONFIG_t.ipAddress);
                   SERVER_CONFIG_t.ipAddress[SERVER_CONFIG_DATA.size()] = '\0'; // Null-terminate the string 
                   }
              else if(SERVER_CONFIG_DATA == "-MOUNT-PATH"){
                   BREAK_HALT(in_config_parse);
                   SERVER_CONFIG_t.mountPath = new char[SERVER_CONFIG_DATA.size()+1];
                   if (SERVER_CONFIG_t.mountPath == nullptr) { std::cout<<VT100_COLOR_RED<<" While parsing memory allcocation failed for mountPath"<<VT100_COLOR_RESET<<std::endl; return;}
                   std::copy(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),SERVER_CONFIG_t.mountPath);
                   SERVER_CONFIG_t.mountPath[SERVER_CONFIG_DATA.size()] = '\0'; // Null-terminate the string
                   }
              else if(SERVER_CONFIG_DATA == "-LOCAL-HOST"){
                   BREAK_HALT(in_config_parse);
                   SERVER_CONFIG_t.isLocalHost = (SERVER_CONFIG_DATA == "1") ? true : false ;
                   }
              else if(SERVER_CONFIG_DATA == "-PROTOCOL-HTTPs"){
                   BREAK_HALT(in_config_parse);
                   SERVER_CONFIG_t.protocolHttps = (SERVER_CONFIG_DATA == "1") ? true : false ;
                   }
              else if (SERVER_CONFIG_DATA == "-PROXY"){
                   BREAK_HALT(in_config_parse);
                   SERVER_CONFIG_t.proxy = new char[SERVER_CONFIG_DATA.size()+1];
                   if (SERVER_CONFIG_t.proxy == nullptr){ std::cout<<VT100_TEXT_BLINK<<VT100_COLOR_RED<<"While parsing memory allcocation failed for serverProxy"<<VT100_COLOR_RESET<<std::endl; return;}
                   std::copy(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),SERVER_CONFIG_t.proxy);
                   SERVER_CONFIG_t.proxy[SERVER_CONFIG_DATA.size()] = '\0'; // Null-terminate the string 
                   }
              else if (SERVER_CONFIG_DATA == "-INTERNAL-DNS-RESOLVER"){
                   BREAK_HALT(in_config_parse);
                   SERVER_CONFIG_t.internalDnsResolver = new char[SERVER_CONFIG_DATA.size()+1];
                   if (SERVER_CONFIG_t.internalDnsResolver == nullptr){ std::cout<<VT100_TEXT_BLINK<<VT100_COLOR_RED<<"While parsing memory allcocation failed for serverinternalDnsResolver"<<VT100_COLOR_RESET<<std::endl; return;}
                   std::copy(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),SERVER_CONFIG_t.internalDnsResolver);
                   SERVER_CONFIG_t.internalDnsResolver[SERVER_CONFIG_DATA.size()] = '\0'; // Null-terminate the string
                   }
              else if(SERVER_CONFIG_DATA == "@end"){
                   parse_stop_server = true;
                   }else{ check_hit++ ; if(check_hit == 1){std::cout<<VT100_COLOR_RED<<"Parsing error please see or correct syntax or variable name of file in SERVER: tag section"<<VT100_COLOR_RESET; check_hit = 0; parse_true = false; return;} continue;}

}
}
// ********************************************************************************************************************************************************************

// *************************************************** checking buffer for WORKER tag *********************************************************************************

else if ( SERVER_CONFIG_DATA == "WORKER:" ) {

           while( parse_stop_worker != true ){
                  SERVER_CONFIG_DATA.clear();
                  std::getline(in_config_parse,SERVER_CONFIG_DATA,'<');
                  SERVER_CONFIG_DATA.erase(std::remove(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),' '),SERVER_CONFIG_DATA.end());
                  SERVER_CONFIG_DATA.erase(std::remove(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),'\n'),SERVER_CONFIG_DATA.end());

                    if (SERVER_CONFIG_DATA == "-DESIRED-WORKER-NO") {
                          BREAK_HALT(in_config_parse);
                          SERVER_CONFIG_t.WORKER.desiredWorkerNo = std::stoi(SERVER_CONFIG_DATA);
                       }
                    else if( SERVER_CONFIG_DATA == "-CONNECTION-PER-WORKER"){
                          BREAK_HALT(in_config_parse);
                          SERVER_CONFIG_t.WORKER.connectionPerWorker = std::stoi(SERVER_CONFIG_DATA);
                       }
                    else if (SERVER_CONFIG_DATA == "-MOUNT-PATH-WORKER" ){
                          BREAK_HALT(in_config_parse);
                          SERVER_CONFIG_t.WORKER.mountPathWorker = new char[SERVER_CONFIG_DATA.size()+1];
                          if ( SERVER_CONFIG_t.WORKER.mountPathWorker == nullptr ) { std::cout<<VT100_COLOR_RED<<"While parsing memory allcocation failed for WorkermountPath"<<VT100_COLOR_RESET<<std::endl; return; }
                          std::copy(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),SERVER_CONFIG_t.WORKER.mountPathWorker);
                          SERVER_CONFIG_t.WORKER.mountPathWorker[SERVER_CONFIG_DATA.size()] = '\0'; // Null-terminate the string
                       }
                    else if(SERVER_CONFIG_DATA == "@end") {
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

}
