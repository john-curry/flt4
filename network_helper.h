#ifndef NETWORK_HELPER_H
#define NETWORK_HELPER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
namespace flt4 {
  char * get_raw_packet(int file_descriptor);
  void send_string_packet(std::string p, int file_descriptor);
}
#endif
