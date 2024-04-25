#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include "../Constants/Constants.hpp"

#define MAX_DATA_SIZE 63

namespace network {
class Package {
 public:
 private:
  unsigned char initMarker;
  unsigned char dataSize : 6;
  unsigned char sequence : 5;
  unsigned char type : 5;
  unsigned char data[MAX_DATA_SIZE];
  unsigned char crc;
};
}  // namespace network

#endif