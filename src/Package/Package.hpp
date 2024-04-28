#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <cstring>

#include "../../enums/PackageTypeEnum.hpp"
#include "../Constants/Constants.hpp"

#define MAX_DATA_SIZE 63
#define DATA_SIZE 6
#define SEQUENCE_SIZE 5
#define TYPE_SIZE 5
#define BITS_IN_BYTE 8

namespace network {
class Package {
 public:
  Package(uint8_t initMarker, uint8_t dataSize, uint8_t sequence, PackageTypeEnum type, const uint8_t* data);
  Package(uint8_t initMarker, uint8_t dataSize, uint8_t sequence, PackageTypeEnum type);

  virtual ~Package() = default;

  // Setters
  void setDataSize(uint8_t dataSize);
  void setSequence(uint8_t sequence);

 private:
  void setCrc();

  uint8_t initMarker;
  uint8_t dataSize : DATA_SIZE;
  uint8_t sequence : SEQUENCE_SIZE;
  PackageTypeEnum type;
  uint8_t data[MAX_DATA_SIZE];
  uint8_t crc;
};
}  // namespace network

#endif