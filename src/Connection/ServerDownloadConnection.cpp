#include "ServerDownloadConnection.hpp"

namespace network {
ServerDownloadConnection::ServerDownloadConnection(RawSocket* rawSocket, const std::string& videoName)
    : Connection{rawSocket} {
  this->lastSequence = 0;
  this->videoName = videoName;
};

void ServerDownloadConnection::run() {
  this->rawSocket->activateTimeout();
  bool running{true};

  try {
    std::cout << "Iniciando conexao - DOWNLOAD - " << this->videoName << std::endl;

    Package ack{Constants::INIT_MARKER, 0, 0, PackageTypeEnum::ACK};
    this->rawSocket->sendPackage(ack);

    // Opening file
    std::ifstream file{Constants::VIDEOS_PATH + '/' + this->videoName};
    if (!file.is_open()) {
      uint8_t errorCode[1] = {2};
      Package error{Constants::INIT_MARKER, 1, 0, PackageTypeEnum::ERROR, errorCode};
      this->rawSocket->sendPackage(error);

      while (running) {
        Package package{this->rawSocket->recvPackage()};

        if (package.getType() != PackageTypeEnum::ACK)
          this->rawSocket->sendPackage(error);
        else
          running = false;
      }

      return;
    }

    std::cout << "ABRIU MEU CONSAGRADO" << std::endl;

  } catch (exceptions::TimeoutException& e) {
    std::cerr << "Connection Timeout - closing" << std::endl;
    this->rawSocket->inactivateTimeout();
  }

  this->rawSocket->inactivateTimeout();
}
}  // namespace network
