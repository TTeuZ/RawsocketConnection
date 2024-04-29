#include "Constants.hpp"

namespace network {
const char* Constants::LOOPBACK_INTERFACE_NAME = "lo";
const char* Constants::ETHERNET_INTERFACE_NAME = "TBD";
const int Constants::TIMEOUT = 30;

const uint8_t Constants::INIT_MARKER = 126;
const uint8_t Constants::CRC_POLYNOMIAL = 0x07;

const uint8_t Constants::MAX_PACKAGE_SIZE = static_cast<uint8_t>(760);
}  // namespace network