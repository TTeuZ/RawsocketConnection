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

#include "exceptions/SocketCreationException/SocketCreationException.hpp"

namespace network {
class RawSocket {
   public:
    RawSocket(const bool const loopback);

    virtual ~RawSocket();

   private:
    bool loopback;
    int socket_id;
    struct sockaddr_ll dest_address;
};
}  // namespace network

#endif