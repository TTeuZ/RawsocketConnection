#include "ServerDownloadConnection.hpp"

namespace network {
ServerDownloadConnection::ServerDownloadConnection(RawSocket* rawSocket) : Connection{rawSocket} {
  this->lastSequence = 0;
};

void ServerDownloadConnection::run() {
  this->rawSocket->activateTimeout();

  try {
  } catch (exceptions::TimeoutException& e) {
    std::cerr << "Connection Timeout - closing" << std::endl;
    this->rawSocket->inactivateTimeout();
  }

  this->rawSocket->inactivateTimeout();
}
}  // namespace network
