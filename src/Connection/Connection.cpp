#include "Connection.hpp"

namespace network {
Connection::Connection(RawSocket* rawSocket) : rawSocket{rawSocket} {};

bool Connection::checkRepeated(const Package* const package) {
  if (this->sequenceOfLastPackage != package->getSequence()) {
    this->sequenceOfLastPackage = package->getSequence();
    return false;
  }
  return true;
}
}  // namespace network
