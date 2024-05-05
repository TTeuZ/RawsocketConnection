#include "ClientListConnection.hpp"

namespace network {
ClientListConnection::ClientListConnection(RawSocket* rawSocket) : Connection{rawSocket} {};

void ClientListConnection::run() {
  this->rawSocket->activateTimeout();

  Package initialPackage{Constants::INIT_MARKER, 0, 0, network::PackageTypeEnum::LIST};
  this->rawSocket->sendPackage(initialPackage);

  Package two{Constants::INIT_MARKER, 0, 31, network::PackageTypeEnum::LIST};
  this->rawSocket->sendPackage(two);

  uint8_t data1[64] = "012345678901234567890123456789012345678901234567890123456789012";
  Package three{Constants::INIT_MARKER, 63, 0, network::PackageTypeEnum::LIST, data1};
  this->rawSocket->sendPackage(three);

  uint8_t data2[64] = "012345678901234567890123456789012345678901234567890123456789012";
  Package four{Constants::INIT_MARKER, 63, 31, network::PackageTypeEnum::LIST, data2};
  this->rawSocket->sendPackage(four);

  uint8_t data3[61] = "012345678901234567890123456789012345678901234567890123456789";
  Package five{Constants::INIT_MARKER, 60, 31, network::PackageTypeEnum::LIST, data3};
  this->rawSocket->sendPackage(five);

  uint8_t data4[64] = "012345678901234567890123456789012345678901234567890123456789012";
  Package six{Constants::INIT_MARKER, 63, 7, network::PackageTypeEnum::LIST, data4};
  this->rawSocket->sendPackage(six);

  uint8_t data5[64] = "012345678901234567890123456789012345678901234567890123456789012";
  Package seven{Constants::INIT_MARKER, 63, 8, network::PackageTypeEnum::LIST, data5};
  this->rawSocket->sendPackage(seven);

  uint8_t data6[64] = "012345678901234567890123456789012345678901234567890123456789012";
  std::unique_ptr<Package> eight = std::make_unique<Package>(
      Package{Constants::INIT_MARKER, 63, 20, network::PackageTypeEnum::LIST, data6});
  this->rawSocket->sendPackage(*eight);

  this->rawSocket->inactivateTimeout();
}
}  // namespace network
