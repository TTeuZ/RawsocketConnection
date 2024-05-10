#include "ClientListConnection.hpp"

namespace network {
ClientListConnection::ClientListConnection(RawSocket* rawSocket) : Connection{rawSocket} {
  this->lastSequence = 0;
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
    running = true;
    while (running) {
      Package package{this->rawSocket->recvPackage()};

      if (package.checkCrc() && !this->checkRepeated(&package)) {
        switch (package.getType()) {
          case PackageTypeEnum::SHOW: {
            std::cout << package.getData() << std::endl;

            Package ack{Constants::INIT_MARKER, 0, static_cast<uint8_t>(this->lastSequence + 1),
                        PackageTypeEnum::ACK};
            this->rawSocket->sendPackage(ack);
            break;
          }
          case PackageTypeEnum::ERROR: {
            std::cout << "Falha de acesso no diretorio de videos. Encerrando." << std::endl;
            running = false;
            break;
          }
          case PackageTypeEnum::END_TX: {
            Package ack{Constants::INIT_MARKER, 0, static_cast<uint8_t>(this->lastSequence + 1),
                        PackageTypeEnum::ACK};
            this->rawSocket->sendPackage(ack);

            running = false;
            break;
          }
          default: {
            break;
          }
        }
      } else {
        Package nack{Constants::INIT_MARKER, 0, this->lastSequence, PackageTypeEnum::NACK};
        this->rawSocket->sendPackage(nack);
      }
    }
  } catch (exceptions::TimeoutException& e) {
    std::cerr << "Connection Timeout - closing" << std::endl;
    this->rawSocket->inactivateTimeout();
  }

  this->rawSocket->inactivateTimeout();
}
}  // namespace network
