#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "../RawSocket/RawSocket.hpp"

namespace network {
class Connection {
 public:
  Connection(RawSocket* rawSocket);

  virtual ~Connection() = default;

  virtual void run() = 0;

 protected:
  bool checkRepeated(const Package* const package);

  RawSocket* rawSocket;
  int8_t sequenceOfLastPackage;
};
}  // namespace network

#endif