#ifndef SOCKET_CREATION_EXCEPTION_HPP
#define SOCKET_CREATION_EXCEPTION_HPP

#include <stdexcept>

namespace exceptions {
class SocketCreationException : public std::runtime_error {
   public:
    explicit SocketCreationException(const std::string& desc);

    virtual ~SocketCreationException() = default;

    const std::string desc;
};
}  // namespace exceptions

#endif