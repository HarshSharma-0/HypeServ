#include "parse_config.hpp"

void write_config_file(std::fstream& in_config_write){

 std::cout << "***************** SERVER SETUP *********************"<< std::endl;
  in_config_write<<"SERVER:"<<"\n";
  std::cout <<VT100_COLOR_YELLOW<<"SERVER NAME                                "<<VT100_COLOR_GREEN;
  std::cin >> UNIVERSAL_DATA_STRING;
  in_config_write<<"-SERVER-NAME    <"<<UNIVERSAL_DATA_STRING<<">\n";
  UNIVERSAL_DATA_STRING.clear();
  std::cin.clear();


  std::cout << "\033[1;33mPORT NUMBER         \033[1;32m"<< "                       ";
  std::cin >> UNIVERSAL_DATA_STRING;
  in_config_write<<"-PORT-NUMBER    <"<<UNIVERSAL_DATA_STRING<<">\n";
  UNIVERSAL_DATA_STRING.clear();
  std::cin.clear();


  std::cout << "\033[0m"<< "\033[1;33mIP ADERESS    \033[1;32m"<< "                             ";
  std::cin >> UNIVERSAL_DATA_STRING;
  in_config_write<<"-IP-ADDRESS     <"<<UNIVERSAL_DATA_STRING<<">\n";
  UNIVERSAL_DATA_STRING.clear();
  std::cin.clear();

  std::cout << "\033[1;33mPATH MOUNT          \033[1;32m"<< "                       ";
  std::cin >> UNIVERSAL_DATA_STRING;
  in_config_write<<"-MOUNT-PATH     <"<<UNIVERSAL_DATA_STRING<<">\n";
  UNIVERSAL_DATA_STRING.clear();
  std::cin.clear();


  std::cout << "\033[1;33mlocalhost (1/0)(default 0)"<< "                 ";
  in_config_write<<"-LOCAL-HOST     <"<<UNIVERSAL_DATA_STRING<<">\n";
  std::cin >> UNIVERSAL_DATA_STRING;
  std::cin.clear();
  std::cout << "\x1b[Alaunch localhost server         "<< "           ";
  (UNIVERSAL_DATA_STRING == "1") ? std::cout << "\033[1;32mTRUE" << std::endl
                    : std::cout << "\033[1;31mFALSE" << std::endl;
  UNIVERSAL_DATA_STRING.clear();


  std::cout << "\033[1;33mPROTOCOL HTTPs (1/0)(default 0)    \033[1;32m"<< "        ";
  std::cin >> UNIVERSAL_DATA_STRING;
  in_config_write<<"-PROTOCOL-HTTPs <"<<UNIVERSAL_DATA_STRING<<">\n";
  std::cout << "\x1b[A\033[1;33mPROTOCOL HTTPs (1/0)(default 0)    \033[1;32m"<< "        ";
  (UNIVERSAL_DATA_STRING == "1") ? std::cout << "\033[1;32mTRUE" << std::endl
                    : std::cout << "\033[1;31mFALSE" << std::endl;UNIVERSAL_DATA_STRING.clear();
  std::cin.clear();



  std::cout << "\033[1;33mPROXY              \033[1;32m "<< "                       ";
  std::cin >> UNIVERSAL_DATA_STRING;
  in_config_write<<"-PROXY          <"<<UNIVERSAL_DATA_STRING<<">\n";
  UNIVERSAL_DATA_STRING.clear();
  std::cin.clear();

  std::cout << "\033[1;33mINTERNAL DNS RESOLVER IP              \033[1;32m "<< "    ";
  std::cin >> UNIVERSAL_DATA_STRING;
  in_config_write<<"-INTERNAL-DNS-RESOLVER  <"<<UNIVERSAL_DATA_STRING<<">\n"<<"@end<\n";
  UNIVERSAL_DATA_STRING.clear();
  std::cin.clear();


  in_config_write<<"WORKER:\n";

  std::cout<<VT100_COLOR_YELLOW<<"WORKER DERSIRED NUMBER                     "<<VT100_COLOR_GREEN;
  std::cin>>UNIVERSAL_DATA_STRING;
  in_config_write<<"-DESIRED-WORKER-NO    <"<<UNIVERSAL_DATA_STRING<<">\n";
  UNIVERSAL_DATA_STRING.clear();

  std::cout<<VT100_COLOR_YELLOW<<"CONNECTION PER WORKER                      "<<VT100_COLOR_GREEN;
  std::cin>>UNIVERSAL_DATA_STRING;
  in_config_write<<"-CONNECTION-PER-WORKER  <"<<UNIVERSAL_DATA_STRING<<">\n";
  UNIVERSAL_DATA_STRING.clear();
  std::cin.clear();

  std::cout<<VT100_COLOR_YELLOW<<"WORKER MOUNT PATH                          "<<VT100_COLOR_GREEN;
  std::cin>>UNIVERSAL_DATA_STRING;
  in_config_write<<"-MOUNT-PATH-WORKER    <"<<UNIVERSAL_DATA_STRING<<">\n";
  UNIVERSAL_DATA_STRING.clear();
  std::cin.clear();

  in_config_write<<"@end<\n";
  std::cout << "\033[0m****************************************************"<< std::endl;


}
