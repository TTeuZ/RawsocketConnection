#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "../RawSocket/RawSocket.hpp"

namespace network {
class Connection {
 public:
  Connection(const RawSocket* const rawSocket);

  virtual ~Connection() = default;

  virtual void run() = 0;

 private:
  const RawSocket* rawSocket;
};
}  // namespace network

#endif