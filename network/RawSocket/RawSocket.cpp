#include "RawSocket.hpp"

namespace network {
RawSocket::RawSocket(const bool const loopback) {
    this->socket_id = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if (this->socket_id < 0) {
        throw new exceptions::SocketCreationException(
            "Faild in function socket()");
    }

    struct ifreq ifr;
    if (loopback) {
        this->dest_address.sll_family = AF_INET;
        this->dest_address.s
    }
}

RawSocket::~RawSocket() { close(this->socket_id); }
}  // namespace network
