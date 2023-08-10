#include "parse_config.hpp"
#include "server.hpp"
#include <sstream>

int parse_config_file(std::fstream& in_config_parse){

bool parse_stop = false;
bool parse_stop_server = false;
bool parse_stop_worker = false;

while (parse_stop != true){
SERVER_CONFIG_DATA.clear();
std::getline(in_config_parse,SERVER_CONFIG_DATA,'\n');
if(SERVER_CONFIG_DATA == "SERVER:"){
     while (parse_stop_server !=true ){

SERVER_CONFIG_DATA.clear();
std::getline(in_config_parse,SERVER_CONFIG_DATA,'<');
SERVER_CONFIG_DATA.erase(std::remove(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),' '),SERVER_CONFIG_DATA.end());
SERVER_CONFIG_DATA.erase(std::remove(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),'\n'),SERVER_CONFIG_DATA.end());

              if (SERVER_CONFIG_DATA == "-SERVER-NAME"){
                    BREAK_HALT(in_config_parse);
                    SERVER_CONFIG_t.serverName = new char[SERVER_CONFIG_DATA.size()+1];
                    if (SERVER_CONFIG_t.serverName == nullptr) { std::cout<<VT100_COLOR_RED<<"While parsing memory allcocation failed for serverName"<<VT100_COLOR_RESET<<std::endl; return -1; }
                    std::copy(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),SERVER_CONFIG_t.serverName);
                    SERVER_CONFIG_t.serverName[SERVER_CONFIG_DATA.size()] = '\0'; // Null-terminate the string
                    std::cout<<SERVER_CONFIG_t.serverName<<std::endl;
                   }
              else if (SERVER_CONFIG_DATA == "-PORT-NUMBER"){
                    BREAK_HALT(in_config_parse);
                    SERVER_CONFIG_t.portNumber = std::stoi(SERVER_CONFIG_DATA);
                    std::cout<<SERVER_CONFIG_t.portNumber<<std::endl;
                   }
              else if (SERVER_CONFIG_DATA == "-IP-ADDRESS"){
                   BREAK_HALT(in_config_parse);
                   SERVER_CONFIG_t.ipAddress = new char[SERVER_CONFIG_DATA.size()+1];
                   if (SERVER_CONFIG_t.ipAddress == nullptr){ std::cout<<VT100_TEXT_BLINK<<VT100_COLOR_RED<<"While parsing memory allcocation failed for serveripaddress"<<VT100_COLOR_RESET<<std::endl; return -1;}
                   std::copy(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),SERVER_CONFIG_t.ipAddress);
                   SERVER_CONFIG_t.ipAddress[SERVER_CONFIG_DATA.size()] = '\0'; // Null-terminate the string
                   std::cout<<SERVER_CONFIG_t.ipAddress<<std::endl;
                   }
              else if(SERVER_CONFIG_DATA == "-MOUNT-PATH"){
                   BREAK_HALT(in_config_parse);
                   SERVER_CONFIG_t.mountPath = new char[SERVER_CONFIG_DATA.size()+1];
                   if (SERVER_CONFIG_t.mountPath == nullptr) { std::cout<<VT100_COLOR_RED<<" While parsing memory allcocation failed for mountPath"<<VT100_COLOR_RESET<<std::endl; return -1;}
                   std::copy(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),SERVER_CONFIG_t.mountPath);
                   SERVER_CONFIG_t.mountPath[SERVER_CONFIG_DATA.size()] = '\0'; // Null-terminate the string
                   std::cout<<SERVER_CONFIG_t.mountPath<<std::endl;
                   }
              else if(SERVER_CONFIG_DATA == "-LOCAL-HOST"){
                   BREAK_HALT(in_config_parse);
                   SERVER_CONFIG_t.isLocalHost = (SERVER_CONFIG_DATA == "1") ? true : false ;
                   std::cout<<SERVER_CONFIG_t.isLocalHost<<std::endl;
                   }
              else if(SERVER_CONFIG_DATA == "-PROTOCOL-HTTPs"){
                   BREAK_HALT(in_config_parse);
                   SERVER_CONFIG_t.protocolHttps = (SERVER_CONFIG_DATA == "1") ? true : false ;
                   std::cout<<SERVER_CONFIG_t.protocolHttps<<std::endl;
                   }
              else if (SERVER_CONFIG_DATA == "-PROXY"){
                   BREAK_HALT(in_config_parse);
                   SERVER_CONFIG_t.proxy = new char[SERVER_CONFIG_DATA.size()+1];
                   if (SERVER_CONFIG_t.proxy == nullptr){ std::cout<<VT100_TEXT_BLINK<<VT100_COLOR_RED<<"While parsing memory allcocation failed for serverProxy"<<VT100_COLOR_RESET<<std::endl; return -1;}
                   std::copy(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),SERVER_CONFIG_t.proxy);
                   SERVER_CONFIG_t.proxy[SERVER_CONFIG_DATA.size()] = '\0'; // Null-terminate the string
                   std::cout<<SERVER_CONFIG_t.proxy<<std::endl;
                   }
              else if (SERVER_CONFIG_DATA == "-INTERNAL-DNS-RESOLVER"){
                   BREAK_HALT(in_config_parse);
                   SERVER_CONFIG_t.internalDnsResolver = new char[SERVER_CONFIG_DATA.size()+1];
                   if (SERVER_CONFIG_t.internalDnsResolver == nullptr){ std::cout<<VT100_TEXT_BLINK<<VT100_COLOR_RED<<"While parsing memory allcocation failed for serverinternalDnsResolver"<<VT100_COLOR_RESET<<std::endl; return -1;}
                   std::copy(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),SERVER_CONFIG_t.internalDnsResolver);
                   SERVER_CONFIG_t.internalDnsResolver[SERVER_CONFIG_DATA.size()] = '\0'; // Null-terminate the string
                   std::cout<<SERVER_CONFIG_t.internalDnsResolver<<std::endl;
                   }
              else if(SERVER_CONFIG_DATA == "@end"){
                   parse_stop_server = true;
                   goto ENSURE_HALT_EXECUTION;
                   }else{ continue; }

}
}
else if ( SERVER_CONFIG_DATA == "WORKER:" ) {

           while( parse_stop_worker != true ){
                  SERVER_CONFIG_DATA.clear();
                  std::getline(in_config_parse,SERVER_CONFIG_DATA,'<');
                  SERVER_CONFIG_DATA.erase(std::remove(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),' '),SERVER_CONFIG_DATA.end());
                  SERVER_CONFIG_DATA.erase(std::remove(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),'\n'),SERVER_CONFIG_DATA.end());

                    if (SERVER_CONFIG_DATA == "-DESIRED-WORKER-NO") {
                          BREAK_HALT(in_config_parse);
                          SERVER_CONFIG_t.WORKER.desiredWorkerNo = std::stoi(SERVER_CONFIG_DATA);
                          std::cout<<SERVER_CONFIG_t.WORKER.desiredWorkerNo<<std::endl;
                       }
                    else if( SERVER_CONFIG_DATA == "-AUDIENCE-PER-WORKER"){
                          BREAK_HALT(in_config_parse);
                          SERVER_CONFIG_t.WORKER.audiencePerWorker = std::stoi(SERVER_CONFIG_DATA);
                          std::cout<<SERVER_CONFIG_t.WORKER.audiencePerWorker<<std::endl;
                       }
                    else if (SERVER_CONFIG_DATA == "-MOUNT-PATH-WORKER" ){
                          BREAK_HALT(in_config_parse);
                          SERVER_CONFIG_t.WORKER.mountPathWorker = new char[SERVER_CONFIG_DATA.size()+1];
                          if ( SERVER_CONFIG_t.WORKER.mountPathWorker == nullptr ) { std::cout<<VT100_COLOR_RED<<"While parsing memory allcocation failed for WorkermountPath"<<VT100_COLOR_RESET<<std::endl; return -1; }
                          std::copy(SERVER_CONFIG_DATA.begin(),SERVER_CONFIG_DATA.end(),SERVER_CONFIG_t.WORKER.mountPathWorker);
                          SERVER_CONFIG_t.WORKER.mountPathWorker[SERVER_CONFIG_DATA.size()] = '\0'; // Null-terminate the string
                          std::cout<<SERVER_CONFIG_t.WORKER.mountPathWorker<<std::endl;

                       }
                    else if(SERVER_CONFIG_DATA == "@end") {
                        parse_stop_worker = true ;
                       }
                    else{ continue; }
}
}

else{
     if( parse_stop_worker == true && parse_stop_server == true ){
        parse_stop = true;
        std::cout<<"else called for var change"<<std::endl;
      }
continue;
}
}

return 0;
}
