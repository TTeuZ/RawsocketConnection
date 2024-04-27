#include "Connection.hpp"

namespace network {
Connection::Connection(const RawSocket* const rawSocket) : rawSocket{rawSocket} {};
}  // namespace network
