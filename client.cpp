#include "client.h"
#include "conversions.h"
#include "network_helper.h"
#include <iostream>
#include <stdexcept>
#include <errno.h>
#include <cstdlib>
namespace flt4 {
  std::vector<std::string> client::wait_for_round_start() {
    char * packet = get_raw_packet(sockfd);
    std::string jsonstr(packet);
    std::free(packet);
    return json_to_team(jsonstr);
  }

  void client::send_round_start(std::vector<std::string> t) { 
    auto jsonout = team_to_json(t);
    send_string_packet(jsonout, sockfd);
  }

  std::map<std::string, int> client::get_turn_end() { 
    auto packet = get_raw_packet(sockfd);
    std::string jsonstr(packet);
    std::free(packet);
    return json_to_actions(jsonstr);
  }

  void client::send_turn_end(std::map<std::string, int> a) { 
    auto jsonout = actions_to_json(a);
    send_string_packet(jsonout, sockfd); 
  } 

  bool client::get_round_status() {
    auto packet = get_raw_packet(sockfd);
    std::string jsonstr(packet);
    std::free(packet);
    return json_to_status(jsonstr);
  }

  void client::send_round_status(bool s) {
    auto jsonout = status_to_json(s);
    send_string_packet(jsonout, sockfd);
  }

  void client::init() {
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo_status = getaddrinfo(
      server_addr.c_str(), // server ip
      "3490", // server port
      &hints, // connection type
      &servinfo // return data
    );

    if (getaddrinfo_status < 0) {
      throw std::runtime_error("getaddrinfo failed");
    }

    sockfd = socket(
      servinfo->ai_family,
      servinfo->ai_socktype,
      servinfo->ai_protocol
    );
    if (sockfd < 0) {
      throw std::runtime_error("Socket fd");
    }

    std::cout << "Ready to connect to server" << std::endl;
  } 
  void client::connect() {
    int connect_status;
    connect_status = ::connect(
      sockfd, 
      servinfo->ai_addr,
      servinfo->ai_addrlen
    );

    if (connect_status < 0) {
      throw std::runtime_error("Problem connecting to server: "
        + std::string(std::strerror(errno)));
    }
  }
} 
