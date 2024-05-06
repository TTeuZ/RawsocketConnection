#ifndef SERVER_LIST_CONNECTION_HPP
#define SERVER_LIST_CONNECTION_HPP

#include "../RawSocket/RawSocket.hpp"
#include "Connection.hpp"

namespace network {
class ServerListConnection : public Connection {
 public:
  ServerListConnection(RawSocket* rawSocket);

  virtual ~ServerListConnection() = default;

  void run() override;
};
}  // namespace network

#endif