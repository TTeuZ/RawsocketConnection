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

  const static uint8_t INIT_MARKER;
  const static uint8_t POLYNOMIAL_CRC;
};
}  // namespace network

#endif