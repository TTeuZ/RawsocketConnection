#include "Connection.hpp"

namespace network {
Connection::Connection(RawSocket* rawSocket) : rawSocket{rawSocket} {};

bool Connection::checkRepeated(const Package* const package) {
  if (this->lastSequence != package->getSequence()) {
    this->lastSequence = package->getSequence();
    return false;
  }
  return true;
}
}  // namespace network
