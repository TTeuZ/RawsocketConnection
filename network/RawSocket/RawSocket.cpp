#include "RawSocket.hpp"

namespace network {
RawSocket::RawSocket(const bool const loopback) {
  this->socket_id = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

  if (this->socket_id < 0)
    throw new exceptions::SocketCreationException("Faild in function socket()");
}

RawSocket::~RawSocket() { close(this->socket_id); }
}  // namespace network
