#ifndef RAWSOCKET_HPP
#define RAWSOCKET_HPP

#include <arpa/inet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netpacket/packet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "../../exceptions/SocketCreateException/SocketCreateException.hpp"
#include "../Constants/Constants.hpp"

namespace network {
class RawSocket {
 public:
  RawSocket(const bool loopback);

  virtual ~RawSocket();

  void sendMessage() const;

  void recvMessage() const;

 private:
  bool loopback;
  int socket_id;
  struct sockaddr_ll address;
  struct packet_mreq mr;
  struct timeval timeout;
};
}  // namespace network

#endif