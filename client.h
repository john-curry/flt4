#ifndef CLIENT_H
#define CLIENT_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <map>
namespace flt4 {
  class client {
    public:
      client(std::string server_addr_) // 
      : server_addr(server_addr_) { }

      void init(); // setup client to talk to server
      void connect(); // connect to server
      std::vector<std::string> wait_for_round_start();
      void send_round_start(std::vector<std::string>);
      std::map<std::string, int> get_turn_end();
      void send_turn_end(std::map<std::string, int>);
      bool get_round_status();
      void send_round_status(bool);

    private:
      std::string server_addr;
      // error status'
      int getaddrinfo_status;
      // end error

      struct addrinfo hints; // connection info
      struct addrinfo *servinfo; // return list

      int sockfd; // socket file descriptor 

      //char * buffer; // recv buffer for server communication
  };
}
#endif
