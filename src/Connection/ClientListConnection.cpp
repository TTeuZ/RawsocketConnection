#include "ClientListConnection.hpp"

namespace network {
ClientListConnection::ClientListConnection(RawSocket* rawSocket) : Connection{rawSocket} {
  this->sequenceOfLastPackage = 0;
};

void ClientListConnection::run() {
  this->rawSocket->activateTimeout();
  bool running{true};

  try {
    Package initialPackage{Constants::INIT_MARKER, 0, 0, network::PackageTypeEnum::LIST};
    this->rawSocket->sendPackage(initialPackage);

    // Waiting ACK from server
    while (running) {
      Package package{this->rawSocket->recvPackage()};

      if (!this->checkRepeated(&package) && package.getType() != PackageTypeEnum::ACK)
        this->rawSocket->sendPackage(initialPackage);
      else
        running = false;
    }

    // Start receive data packages

  } catch (exceptions::TimeoutException& e) {
    std::cerr << "Connection Timeout - closing" << std::endl;
    this->rawSocket->inactivateTimeout();
  }

  this->rawSocket->inactivateTimeout();
}
}  // namespace network
