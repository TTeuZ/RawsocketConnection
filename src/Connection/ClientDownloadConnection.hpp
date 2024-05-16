#ifndef CLIENT_DOWNLOAD_CONNECTION_HPP
#define CLIENT_DOWNLOAD_CONNECTION_HPP

#include <cmath>
#include <fstream>

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
  void showProgress(const uintmax_t recvPackages, const uintmax_t totalPackages) const;

  std::string videoName;
};
};  // namespace network

#endif