#include "RawSocket.hpp"

namespace network {
RawSocket::RawSocket(const bool loopback) {
  this->socket_id = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

  if (this->socket_id < 0)
    throw exceptions::SocketCreateException(
        "Faild in function socket() - Please check if you have root permissions!");
}

RawSocket::~RawSocket() { close(this->socket_id); }
}  // namespace network
