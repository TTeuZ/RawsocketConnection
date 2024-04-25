#include <iostream>

#include "src/Argparser/Argparser.hpp"
#include "src/RawSocket/RawSocket.hpp"

int main(int argc, char** argv) {
  bool loopback = network::Argparser::parserArguments(argc, argv);
  network::RawSocket* rawSocket{new network::RawSocket{loopback}};

  rawSocket->recvMessage();

  delete rawSocket;
}