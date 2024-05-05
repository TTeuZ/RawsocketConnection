#include <iostream>

#include "src/Argparser/Argparser.hpp"
#include "src/Package/Package.hpp"
#include "src/RawSocket/RawSocket.hpp"

int main(int argc, char** argv) {
  bool loopback = network::Argparser::parserArguments(argc, argv);
  network::RawSocket* rawSocket{new network::RawSocket{loopback}};

  while (true) {
    std::unique_ptr<network::Package> package = rawSocket->recvPackage();

    if (package != nullptr) {
      package->dummy();
    }
  }

  delete rawSocket;
}