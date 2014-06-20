#include "network_helper.h"
namespace flt4 {
  char * get_raw_packet(int file_descriptor) {
    char * buffer = (char *)std::malloc(101);
    std::cout << "Recieving data..." << std::endl;
    int recvstatus = ::recv(file_descriptor, buffer, 101, 0);
    if (recvstatus < 0) {
      throw std::runtime_error("Bad recv call..");
    }
    return buffer;
  }
  void send_string_packet(std::string p, int file_descriptor) {
    std::cout << "Sending packet..." << std::endl;
    int len = p.size();
    if (::send(file_descriptor, p.c_str(), len, 0) < 0) {
      throw std::runtime_error(
        "send_string_packet did not complete. Failed on packet"
        ":" + p);
    }
  }
}
