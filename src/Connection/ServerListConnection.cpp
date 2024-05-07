#include "ServerListConnection.hpp"

namespace network {
ServerListConnection::ServerListConnection(RawSocket* rawSocket) : Connection{rawSocket} {
  this->sequenceOfLastPackage = -1;
};

void ServerListConnection::run() {
  this->rawSocket->activateTimeout();
  bool running{true};

  try {
    Package ack{Constants::INIT_MARKER, 0, 0, network::PackageTypeEnum::ACK};
    this->rawSocket->sendPackage(ack);

  } catch (exceptions::TimeoutException& e) {
    std::cerr << "Connection Timeout - closing" << std::endl;
    this->rawSocket->inactivateTimeout();
  }

  this->rawSocket->inactivateTimeout();
}
}  // namespace network