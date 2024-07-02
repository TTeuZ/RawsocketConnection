#include "Connection.hpp"

namespace network {
Connection::Connection(RawSocket* rawSocket) : rawSocket{rawSocket} {};

void Connection::wait_ack(const Package& package) const {
  while (true) {
    Package package{this->rawSocket->recvPackage()};

    if (package.getType() == PackageTypeEnum::NACK)
      this->rawSocket->sendPackage(package);
    else if (package.getType() == PackageTypeEnum::ACK)
      return;
  }
}
}  // namespace network
