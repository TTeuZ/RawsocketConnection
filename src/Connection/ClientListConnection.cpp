#include "ClientListConnection.hpp"

namespace network {
ClientListConnection::ClientListConnection(const RawSocket* const rawSocket) : Connection{rawSocket} {};

void ClientListConnection::run() { std::cout << "Batata" << std::endl; }
}  // namespace network
