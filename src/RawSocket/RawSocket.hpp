#ifndef RAWSOCKET_HPP
#define RAWSOCKET_HPP

#include <arpa/inet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netpacket/packet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "../../exceptions/SendFailedException/SendFailedException.hpp"
#include "../../exceptions/SocketCreateException/SocketCreateException.hpp"
#include "../../exceptions/TimeoutException/TimeoutException.hpp"
#include "../BitArray/BitArray.hpp"
#include "../Constants/Constants.hpp"
#include "../Package/Package.hpp"

namespace network {
class RawSocket {
 public:
  RawSocket(const bool loopback);

  virtual ~RawSocket();

  void sendPackage(Package& package);

  Package recvPackage();

 private:
  bool can_write();
  bool can_read();

  bool loopback;
  int socket_id;
  struct sockaddr_ll address;
  struct packet_mreq mr;
  struct timeval timeout_main;
  struct timeval timeout_select;

  // Loopback only
  int skipNext;
};
}  // namespace network

#endif