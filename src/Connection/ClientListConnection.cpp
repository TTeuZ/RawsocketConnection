#include "ClientListConnection.hpp"

namespace network {
ClientListConnection::ClientListConnection(RawSocket* rawSocket) : Connection{rawSocket} { this->lastSequence = 0; };

void ClientListConnection::run() {
  this->rawSocket->activateTimeout();
  bool running{true};

  try {
    Package initialPackage{Constants::INIT_MARKER, 0, 0, network::PackageTypeEnum::LIST};
    this->rawSocket->sendPackage(initialPackage);

    // Waiting ACK from server
    while (running) {
      Package package{this->rawSocket->recvPackage()};

      if (package.getType() != PackageTypeEnum::ACK)
        this->rawSocket->sendPackage(initialPackage);
      else
        running = false;
    }

    std::cout << "\n---------------[LISTA]---------------\n";

    // Start receive data packages
    running = true;
    while (running) {
      Package package{this->rawSocket->recvPackage()};

      if (package.checkCrc()) {
        switch (package.getType()) {
          case PackageTypeEnum::SHOW: {
            for (size_t i = 0; i < package.getDataSize(); ++i) std::cout << package.getData()[i];

            Package ack{Constants::INIT_MARKER, 0, package.getSequence(), PackageTypeEnum::ACK};
            this->lastSequence = package.getSequence();

            this->rawSocket->sendPackage(ack);
            break;
          }
          case PackageTypeEnum::ERROR: {
            std::cout << "Falha de acesso no diretorio de videos. Encerrando..." << std::endl;
            running = false;
            break;
          }
          case PackageTypeEnum::END_TX: {
            Package ack{Constants::INIT_MARKER, 0, package.getSequence(), PackageTypeEnum::ACK};
            this->rawSocket->sendPackage(ack);
            std::cout << std::endl;

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
