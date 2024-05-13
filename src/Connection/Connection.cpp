#include "Connection.hpp"

namespace network {
Connection::Connection(RawSocket* rawSocket) : rawSocket{rawSocket} {};
}  // namespace network
