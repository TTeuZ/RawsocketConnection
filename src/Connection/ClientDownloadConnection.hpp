#ifndef CLIENT_DOWNLOAD_CONNECTION_HPP
#define CLIENT_DOWNLOAD_CONNECTION_HPP

#include "../../enums/PackageTypeEnum.hpp"
#include "../../exceptions/TimeoutException/TimeoutException.hpp"
#include "../Constants/Constants.hpp"
#include "../Package/Package.hpp"
#include "../RawSocket/RawSocket.hpp"
#include "Connection.hpp"

namespace network {
class ClientDownloadConnection : public Connection {
 public:
  ClientDownloadConnection(RawSocket* rawSocket, const std::string& videoName);

  virtual ~ClientDownloadConnection() = default;

  void run() override;

 private:
  std::string videoName;
};
};  // namespace network

#endif