#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

namespace network {
class Constants {
 public:
  Constants() = delete;

  virtual ~Constants() = default;

  const static char* LOOPBACK_INTERFACE_NAME;
  const static char* ETHERNET_INTERFACE_NAME;
  const static int TIMEOUT;
};
}  // namespace network

#endif