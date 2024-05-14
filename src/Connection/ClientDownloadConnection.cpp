#include "ClientDownloadConnection.hpp"

namespace network {
ClientDownloadConnection::ClientDownloadConnection(RawSocket* rawSocket, const std::string& videoName)
    : Connection{rawSocket} {
  this->lastSequence = 0;
  this->videoName = videoName;
};

void ClientDownloadConnection::run() {
  this->rawSocket->activateTimeout();

  try {
    std::cout << this->videoName << std::endl;
  } catch (exceptions::TimeoutException& e) {
    std::cerr << "Connection Timeout - closing" << std::endl;
    this->rawSocket->inactivateTimeout();
  }

  this->rawSocket->inactivateTimeout();
}
}  // namespace network
