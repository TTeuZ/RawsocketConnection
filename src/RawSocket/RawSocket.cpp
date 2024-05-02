#include "RawSocket.hpp"

namespace network {
RawSocket::RawSocket(const bool loopback) : loopback{loopback} {
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

  if (bind(socket_id, (struct sockaddr*)&this->address, sizeof(this->address)) == -1)
    throw exceptions::SocketCreateException("Error binding socket!");

  this->mr = {0};
  this->mr.mr_ifindex = ifindex;
  this->mr.mr_type = PACKET_MR_PROMISC;

  if (setsockopt(this->socket_id, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &this->mr, sizeof(this->mr)) == -1)
    throw exceptions::SocketCreateException("Error executing setsockopt!");

  this->inactivateTimeout();
}

RawSocket::~RawSocket() { close(this->socket_id); }

void RawSocket::activateTimeout() {
  this->timeout.tv_sec = Constants::TIMEOUT;
  this->timeout.tv_usec = 0;
  if (setsockopt(this->socket_id, SOL_SOCKET, SO_SNDTIMEO, &this->timeout, sizeof(this->timeout)) < 0)
    throw exceptions::SocketCreateException("Error activating timeout for send!");

  if (setsockopt(this->socket_id, SOL_SOCKET, SO_RCVTIMEO, &this->timeout, sizeof(this->timeout)) < 0)
    throw exceptions::SocketCreateException("Error activating timeout for recv!");
}

void RawSocket::inactivateTimeout() {
  this->timeout.tv_sec = 0;
  this->timeout.tv_usec = 0;
  if (setsockopt(this->socket_id, SOL_SOCKET, SO_SNDTIMEO, &this->timeout, sizeof(this->timeout)) < 0)
    throw exceptions::SocketCreateException("Error inactivating timeout for send!");

  if (setsockopt(this->socket_id, SOL_SOCKET, SO_RCVTIMEO, &this->timeout, sizeof(this->timeout)) < 0)
    throw exceptions::SocketCreateException("Error inactivating timeout for recv!");
}

void RawSocket::sendPackage(Package& package) {
  BitArray bits{package.getRawPackage()};

  if (write(this->socket_id, bits.getData(), bits.sizeBytes()) == -1)
    throw exceptions::SendFailedException("Error sending package");
}

void RawSocket::recvPackage() const {
  char buffer[Constants::MAX_PACKAGE_SIZE];
  ssize_t recv_len;

  recv_len = read(this->socket_id, &buffer, sizeof(buffer));

  if (buffer[0] == '~') {
    std::cout << "Bits array: ";
    for (int i = 0; i < recv_len; ++i) std::cout << buffer[i] << " ";
    std::cout << std::endl;
  }
}
}  // namespace network