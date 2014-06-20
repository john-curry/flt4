#include "server.h"
#include "conversions.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <json/reader.h> 
namespace flt4 {

void server::round_start(std::vector<std::string> team) {
  std::string jsonout = team_to_json(team);
  send_string_packet(jsonout, connection_fd);
}

//char * server::get_raw_packet() {
//  char * buffer = (char *)std::malloc(101);
//  std::cout << "Recieving round data..." << std::endl;
//  int recvstatus = ::recv(connection_fd, buffer, 101, 0);
//  if (recvstatus < 0) {
//    throw std::runtime_error("Bad recv call..");
//  }
//  return buffer;
//}
//
//void server::send_string_packet(std::string p) {
//  std::cout << "Sending packet..." << std::endl;
//  int len = p.size();
//  if (::send(connection_fd, p.c_str(), len, 0) < 0) {
//    throw std::runtime_error(
//      "send_string_packet did not complete. Failed on packet"
//      ":" + p);
//  }
//}
//
std::vector<std::string> server::round_acknoledge() {
  char * buffer = get_raw_packet(connection_fd);
  std::string jsonstr(buffer);
  std::free(buffer);
  return json_to_team(jsonstr);
}

void server::send_turn_end(std::map<std::string, int> actns) {
  std::string jsonstr = actions_to_json(actns);
  send_string_packet(jsonstr, connection_fd);
}

std::map<std::string, int> server::turn_end_acknoledge() {
  char * packet = get_raw_packet(connection_fd);
  std::string json(packet);
  std::free(packet);
  return json_to_actions(json);
}

void server::send_roundstatus(bool status) {
  std::string jsonstr = status_to_json(status);
  send_string_packet(jsonstr, connection_fd);
}

bool server::get_roundstatus() {
  char * packet = get_raw_packet(connection_fd);
  std::string json(packet);
  std::free(packet);
  return json_to_status(json);
}

void server::init() {
    std::cout << "Starting server" << std::endl;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    std::cout << "Calling getaddrinfo" << std::endl;
    status = getaddrinfo(NULL, "3490", &hints, &servinfo);
    if (status < 0) {
      throw std::runtime_error(gai_strerror(status));
    }
    std::cout << "Getting socket file descriptor" << std::endl;
    sockfd = socket(
      servinfo->ai_family, 
      servinfo->ai_socktype,
      servinfo->ai_protocol
    );
    if (sockfd < 0) {
      throw std::runtime_error("socket() error getting file descriptor");
    }
    std::cout << "Binding socket file descriptor to server info" << std::endl;
    if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) < 0) {
      throw std::runtime_error("Failed to bind file desc to servinfo");
    }
    std::cout << "Ready to listen" << std::endl;
  }
  void server::listen() {
    std::cout << "setting up listening" << std::endl;
    int listenstatus;

    listenstatus = ::listen(sockfd, 10);

    if (listenstatus < 0) {
      throw std::runtime_error("Failed to listen");
    }
    std::cout << "Listening for connection" << std::endl;
  }
  void server::accept() {
    std::cout << "Waiting to accept connection" << std::endl;
    addr_size = sizeof(their_addr_info);
    connection_fd = ::accept(
      sockfd, // listening socket file descriptor 
      (struct sockaddr *)&their_addr_info, // client info
      &addr_size
    );
    if (connection_fd < 0) {
      throw std::runtime_error("Error making connection");
    }
    std::cout << "Made connection" << std::endl;
  }
}
