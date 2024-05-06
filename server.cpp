#include <iostream>

#include "enums/PackageTypeEnum.hpp"
#include "src/ArgParser/ArgParser.hpp"
#include "src/Connection/ServerListConnection.hpp"
#include "src/Constants/Constants.hpp"
#include "src/Package/Package.hpp"
#include "src/RawSocket/RawSocket.hpp"

int main(int argc, char** argv) {
  bool loopback = network::ArgParser::parseArguments(argc, argv);
  network::RawSocket* rawSocket{new network::RawSocket{loopback}};

  while (true) {
    std::unique_ptr<network::Package> package{rawSocket->recvPackage()};

    if (package->checkCrc()) {
      switch (package->getType()) {
        case network::PackageTypeEnum::LIST: {
          network::ServerListConnection connection{rawSocket};
          connection.run();

          break;
        }
        case network::PackageTypeEnum::DOWNLOAD: {
          std::cout << "recebido download" << std::endl;
          break;
        }
        default: {
          // This can cause infinite looping
          network::Package nack{network::Constants::INIT_MARKER, 0, 0, network::PackageTypeEnum::NACK};
          rawSocket->sendPackage(nack);
          break;
        }
      }
    } else {
      network::Package nack{network::Constants::INIT_MARKER, 0, 0, network::PackageTypeEnum::NACK};
      rawSocket->sendPackage(nack);
    }
  }

  delete rawSocket;
}