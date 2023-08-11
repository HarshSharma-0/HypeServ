#include "parse_config.hpp"

int write_config_file(std::fstream& in_config_write){

 std::cout << "***************** SERVER SETUP *********************"<< std::endl;
  in_config_write<<"SERVER:"<<"\n";
  std::cout <<VT100_COLOR_YELLOW<<"SERVER NAME                                "<<VT100_COLOR_GREEN;
  std::cin >> SERVER_CONFIG_DATA;
  in_config_write<<"-SERVER-NAME    <"<<SERVER_CONFIG_DATA<<">\n";
  SERVER_CONFIG_DATA.clear();
  std::cin.clear();


  std::cout << "\033[1;33mPORT NUMBER         \033[1;32m"<< "                       ";
  std::cin >> SERVER_CONFIG_DATA;
  in_config_write<<"-PORT-NUMBER    <"<<SERVER_CONFIG_DATA<<">\n";
  SERVER_CONFIG_DATA.clear();
  std::cin.clear();


  std::cout << "\033[0m"<< "\033[1;33mIP ADERESS    \033[1;32m"<< "                             ";
  std::cin >> SERVER_CONFIG_DATA;
  in_config_write<<"-IP-ADDRESS     <"<<SERVER_CONFIG_DATA<<">\n";
  SERVER_CONFIG_DATA.clear();
  std::cin.clear();

  std::cout << "\033[1;33mPATH MOUNT          \033[1;32m"<< "                       ";
  std::cin >> SERVER_CONFIG_DATA;
  in_config_write<<"-MOUNT-PATH     <"<<SERVER_CONFIG_DATA<<">\n";
  SERVER_CONFIG_DATA.clear();
  std::cin.clear();


  std::cout << "\033[1;33mlocalhost (1/0)(default 0)"<< "                 ";
  in_config_write<<"-LOCAL-HOST     <"<<SERVER_CONFIG_DATA<<">\n";
  std::cin >> SERVER_CONFIG_DATA;  
  std::cin.clear();
  std::cout << "\x1b[Alaunch localhost server         "<< "           ";
  (SERVER_CONFIG_DATA == "1") ? std::cout << "\033[1;32mTRUE" << std::endl
                    : std::cout << "\033[1;31mFALSE" << std::endl;
  SERVER_CONFIG_DATA.clear();


  std::cout << "\033[1;33mPROTOCOL HTTPs (1/0)(default 0)    \033[1;32m"<< "        ";
  std::cin >> SERVER_CONFIG_DATA;
  in_config_write<<"-PROTOCOL-HTTPs <"<<SERVER_CONFIG_DATA<<">\n";
  std::cout << "\x1b[A\033[1;33mPROTOCOL HTTPs (1/0)(default 0)    \033[1;32m"<< "        ";
  (SERVER_CONFIG_DATA == "1") ? std::cout << "\033[1;32mTRUE" << std::endl
                    : std::cout << "\033[1;31mFALSE" << std::endl;SERVER_CONFIG_DATA.clear();
  std::cin.clear();



  std::cout << "\033[1;33mPROXY              \033[1;32m "<< "                       ";
  std::cin >> SERVER_CONFIG_DATA;
  in_config_write<<"-PROXY          <"<<SERVER_CONFIG_DATA<<">\n";
  SERVER_CONFIG_DATA.clear();
  std::cin.clear();

  std::cout << "\033[1;33mINTERNAL DNS RESOLVER IP              \033[1;32m "<< "    ";
  std::cin >> SERVER_CONFIG_DATA;
  in_config_write<<"-INTERNAL-DNS-RESOLVER  <"<<SERVER_CONFIG_DATA<<">\n"<<"@end<\n";
  SERVER_CONFIG_DATA.clear();
  std::cin.clear();


  in_config_write<<"WORKER:\n";

  std::cout<<VT100_COLOR_YELLOW<<"WORKER DERSIRED NUMBER                     "<<VT100_COLOR_GREEN;
  std::cin>>SERVER_CONFIG_DATA;
  in_config_write<<"-DESIRED-WORKER-NO    <"<<SERVER_CONFIG_DATA<<">\n";
  SERVER_CONFIG_DATA.clear();

  std::cout<<VT100_COLOR_YELLOW<<"CONNECTION PER WORKER                      "<<VT100_COLOR_GREEN;
  std::cin>>SERVER_CONFIG_DATA;
  in_config_write<<"-CONNECTION-PER-WORKER  <"<<SERVER_CONFIG_DATA<<">\n";
  SERVER_CONFIG_DATA.clear();
  std::cin.clear();

  std::cout<<VT100_COLOR_YELLOW<<"WORKER MOUNT PATH                          "<<VT100_COLOR_GREEN;
  std::cin>>SERVER_CONFIG_DATA;
  in_config_write<<"-MOUNT-PATH-WORKER    <"<<SERVER_CONFIG_DATA<<">\n";
  SERVER_CONFIG_DATA.clear();
  std::cin.clear();

  in_config_write<<"@end<\n";
  std::cout << "\033[0m****************************************************"<< std::endl;

return 0;
}
