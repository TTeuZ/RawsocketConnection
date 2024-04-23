#include "SocketCreationException.hpp"

namespace exceptions {
SocketCreationException::SocketCreationException(const std::string& desc)
    : runtime_error{"Fail in create socket connection"}, desc{desc} {};
}