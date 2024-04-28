#include "Constants.hpp"

namespace network {
const char* Constants::LOOPBACK_INTERFACE_NAME = "lo";
const char* Constants::ETHERNET_INTERFACE_NAME = "TBD";
const int Constants::TIMEOUT = 30;

const uint8_t Constants::INIT_MARKER = 126;
const uint8_t Constants::POLYNOMIAL_CRC = 0xEA;
}  // namespace network