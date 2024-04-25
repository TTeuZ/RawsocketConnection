#include "RawSocket.hpp"

namespace network {
RawSocket::RawSocket(const bool loopback) {
  const char* interface_name =
      loopback ? Constants::LOOPBACK_INTERFACE_NAME : Constants::ETHERNET_INTERFACE_NAME;

  this->socket_id = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if (this->socket_id < 0)
    throw exceptions::SocketCreateException(
        "Fail in create socket - Please check if you have root permissions!");

  int ifindex = if_nametoindex(interface_name);

  this->address = {0};
  this->address.sll_family = AF_PACKET;
  this->address.sll_protocol = htons(ETH_P_ALL);
  this->address.sll_ifindex = ifindex;

  if (bind(socket_id, (struct sockaddr*)&address, sizeof(address)) == -1)
    throw exceptions::SocketCreateException("Error binding socket!");

  this->mr = {0};
  this->mr.mr_ifindex = ifindex;
  this->mr.mr_type = PACKET_MR_PROMISC;

  if (setsockopt(this->socket_id, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &this->mr, sizeof(this->mr)) == -1)
    throw exceptions::SocketCreateException("Error executing setsockopt!");

  this->timeout.tv_sec = Constants::TIMEOUT;
  this->timeout.tv_usec = 0;

  if (setsockopt(this->socket_id, SOL_SOCKET, SO_SNDTIMEO, (char*)&this->timeout, sizeof(this->timeout)) < 0)
    throw exceptions::SocketCreateException("Error setting timeout for send!");

  if (setsockopt(this->socket_id, SOL_SOCKET, SO_RCVTIMEO, (char*)&this->timeout, sizeof(this->timeout)) < 0)
    throw exceptions::SocketCreateException("Error setting timeout for recv!");
}

RawSocket::~RawSocket() { close(this->socket_id); }
}  // namespace network
