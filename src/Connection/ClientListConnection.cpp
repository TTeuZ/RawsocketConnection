#include "ClientListConnection.hpp"

namespace network {
ClientListConnection::ClientListConnection(RawSocket* rawSocket) : Connection{rawSocket} {};

void ClientListConnection::run() {
  Package initialPackage{Constants::INIT_MARKER, 0, 0, network::PackageTypeEnum::LIST};
  this->rawSocket->sendPackage(initialPackage);
}
}  // namespace network
