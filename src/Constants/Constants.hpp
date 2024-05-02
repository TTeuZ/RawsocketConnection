#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

#define MAX_DATA_SIZE 63
#define DATA_SIZE 6
#define SEQUENCE_SIZE 5
#define TYPE_SIZE 5
#define BITS_IN_BYTE 8

namespace network {
class Constants {
 public:
  Constants() = delete;

  virtual ~Constants() = default;

  const static char* LOOPBACK_INTERFACE_NAME;
  const static char* ETHERNET_INTERFACE_NAME;
  const static int TIMEOUT;

  const static uint8_t INIT_MARKER;
  const static uint8_t CRC_POLYNOMIAL;

  const static uint8_t MAX_PACKAGE_SIZE;
  const static uint8_t MIN_PACKAGE_SIZE_IN_BITS;
};
}  // namespace network

#endif