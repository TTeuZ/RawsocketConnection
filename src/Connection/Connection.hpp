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
  RawSocket* rawSocket;
};
}  // namespace network

#endif