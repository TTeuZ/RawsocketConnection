#include "Connection.hpp"

namespace network {
Connection::Connection(RawSocket* rawSocket) : rawSocket{rawSocket} {};

void Connection::wait_ack(Package& sentPackage) {
  Package receivedPackage;
  int status;

  while (true) {
    status = this->rawSocket->recvPackage(receivedPackage);

    if (status == Constants::STATUS_RETRY || receivedPackage.getType() == PackageTypeEnum::NACK)
      this->rawSocket->sendPackage(sentPackage);
    else if (receivedPackage.getType() == PackageTypeEnum::ACK)
      return;
  }
}
}  // namespace network
