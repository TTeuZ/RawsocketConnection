#include "ClientListConnection.hpp"

namespace network {
ClientListConnection::ClientListConnection(RawSocket* rawSocket) : Connection{rawSocket} {};

void ClientListConnection::run() {
  this->rawSocket->activateTimeout();
  bool running{true};

  try {
    Package initialPackage{Constants::INIT_MARKER, 0, 0, network::PackageTypeEnum::LIST};
    this->rawSocket->sendPackage(initialPackage);

    while (running) {
      std::unique_ptr<network::Package> package{this->rawSocket->recvPackage()};
      if (!package->checkCrc()) {
        Package nack{Constants::INIT_MARKER, 0, 0, network::PackageTypeEnum::NACK};
        this->rawSocket->sendPackage(nack);
      } else if (package->getType() == PackageTypeEnum::NACK) {
        this->rawSocket->sendPackage(initialPackage);
      } else {
        running = false;
      }
    }

    // while (running) {
    //   std::unique_ptr<network::Package> package{this->rawSocket->recvPackage()};

    //   if (package != nullptr && package->getType() == PackageTypeEnum::NACK)
    //     this->rawSocket->sendPackage(initialPackage);

    //   // CONTINUE THE PROCESSING
    // }

  } catch (exceptions::TimeoutException& e) {
    std::cerr << "Connection Timeout - closing" << std::endl;
    this->rawSocket->inactivateTimeout();
  }

  this->rawSocket->inactivateTimeout();
}
}  // namespace network
