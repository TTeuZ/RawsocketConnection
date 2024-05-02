#include <iostream>

#include "src/Argparser/Argparser.hpp"
#include "src/Connection/ClientListConnection.hpp"
#include "src/RawSocket/RawSocket.hpp"

int main(int argc, char** argv) {
  bool loopback = network::Argparser::parserArguments(argc, argv);
  network::RawSocket* rawSocket{new network::RawSocket{loopback}};

  std::cout << "Seja bem vindo ao RedesTube" << std::endl;
  std::cout << "Selecione uma das seguintes opcoes: " << std::endl;

  std::cout << "1 - listar filmes disponiveis" << std::endl;
  std::cout << "2 - Baixar filme" << std::endl;
  std::cout << "0 - Sair" << std::endl;

  std::cout << "Comando: ";
  int command;
  std::cin >> command;
  while (command != 0) {
    switch (command) {
      case 1: {
        network::ClientListConnection connection{rawSocket};
        connection.run();

        break;
      }
      case 2: {
        std::cout << "Futuro" << std::endl;
        break;
      }
      case 0: {
        std::cout << "Saindo.." << std::endl;
        break;
      }
      default: {
        std::cout << "Comando invalido" << std::endl;
        break;
      }
    }
    std::cout << "Proximo comando: ";
    std::cin >> command;
  }

  delete rawSocket;
}