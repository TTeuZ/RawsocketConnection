#include "Connection.hpp"

namespace network {
Connection::Connection(RawSocket* rawSocket) : rawSocket{rawSocket} {};

void Connection::wait_ack(const Package& package) const {
  while (true) {
    Package package{this->rawSocket->recvPackage()};

    if (package.getType() != PackageTypeEnum::ACK)
      this->rawSocket->sendPackage(package);
    else
      return;
  }
}
}  // namespace network
