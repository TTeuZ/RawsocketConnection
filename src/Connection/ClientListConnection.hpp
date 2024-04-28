#ifndef CLIENT_LIST_CONNECTION_HPP
#define CLIENT_LIST_CONNECTION_HPP

#include "../../enums/PackageTypeEnum.hpp"
#include "../Constants/Constants.hpp"
#include "../Package/Package.hpp"
#include "../RawSocket/RawSocket.hpp"
#include "Connection.hpp"

namespace network {
class ClientListConnection : public Connection {
 public:
  ClientListConnection(const RawSocket* const rawSocket);

  virtual ~ClientListConnection() = default;

  void run() override;
};
}  // namespace network

#endif