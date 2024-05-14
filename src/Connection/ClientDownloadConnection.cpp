#include "ClientDownloadConnection.hpp"

namespace network {
ClientDownloadConnection::ClientDownloadConnection(RawSocket* rawSocket, const std::string& videoName)
    : Connection{rawSocket} {
  this->lastSequence = 0;
  this->videoName = videoName;
};

void ClientDownloadConnection::run() {
  if (this->videoName.length() > MAX_DATA_SIZE) {
    std::cout << "Nome excedeu os limites!" << std::endl;
    return;
  }

  this->rawSocket->activateTimeout();
  bool running{true};

  try {
    const uint8_t* data = reinterpret_cast<const uint8_t*>(this->videoName.c_str());
    Package initialPackage{Constants::INIT_MARKER, static_cast<uint8_t>(this->videoName.length()), 0,
                           PackageTypeEnum::DOWNLOAD, data};
    this->rawSocket->sendPackage(initialPackage);

    // Waiting ACK from server
    while (running) {
      Package package{this->rawSocket->recvPackage()};

      if (package.getType() != PackageTypeEnum::ACK)
        this->rawSocket->sendPackage(initialPackage);
      else
        running = false;
    }

    // Waiting header
    running = true;
    while (running) {
      Package package{this->rawSocket->recvPackage()};

      if (package.checkCrc()) {
        if (package.getType() == PackageTypeEnum::FILE_HEADER) {
          std::cout << "OK" << std::endl;
        } else {
          std::cout << "Arquivo inexistente!" << std::endl;
          Package ack{Constants::INIT_MARKER, 0, this->lastSequence, PackageTypeEnum::ACK};
          this->rawSocket->sendPackage(ack);

          return;
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
