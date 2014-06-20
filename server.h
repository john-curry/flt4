#ifndef SERVER_H
#define SERVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "network_helper.h"
namespace flt4 {
  class server {
  public:
    server() { }
    ~server() { close(sockfd); }
    void init(); // setup server so it is ready to listen

    void listen(); // start server listening
    void accept(); // blocking acceptor of incoming connections
    // sends a list of members of players team 
    void round_start(std::vector<std::string>);

    // gets the opponents team
    std::vector<std::string> round_acknoledge();

    // send server done turn map<name, damage_done>
    void send_turn_end(std::map<std::string, int>);

    // get client done turn map<name, damage_done>
    std::map<std::string, int> turn_end_acknoledge();
    
    // send game status
    void send_roundstatus(bool);

    // get game status from client
    // returns true if round not over
    // returns false if round over
    bool get_roundstatus();

  private:
    int status; // getaddrinfo error code
    struct addrinfo hints; // tells getaddrinfo what type of connection it is handling
    struct addrinfo *servinfo; // return list of server info
    int sockfd; // file descriptor that we will bind against

    // info for making connection
    struct sockaddr_storage their_addr_info;
    socklen_t addr_size;
    int connection_fd;
    
  };
}


#endif
