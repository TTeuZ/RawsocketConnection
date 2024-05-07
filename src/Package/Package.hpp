#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <cstring>
#include <memory>

#include "../../enums/PackageTypeEnum.hpp"
#include "../BitArray/BitArray.hpp"
#include "../Constants/Constants.hpp"

namespace network {
class Package {
 public:
  Package(uint8_t initMarker, uint8_t dataSize, uint8_t sequence, PackageTypeEnum type, const uint8_t* data);
  Package(uint8_t initMarker, uint8_t dataSize, uint8_t sequence, PackageTypeEnum type);
  Package(const char* const buffer);

  Package(Package&& package);
  Package& operator=(Package&& package);

  virtual ~Package() = default;

  // Setters
  void setDataSize(uint8_t dataSize);
  void setSequence(uint8_t sequence);

  // Getters
  BitArray getRawPackage();
  uint16_t getSize() const;
  PackageTypeEnum getType() const;
  uint8_t getSequence() const;

  bool checkCrc();

  // Remove it
  void dummy();

 private:
  uint8_t calcCrc();

  void fillUpRawArray(BitArray bits, bool full);

  uint8_t initMarker;
  uint8_t dataSize : DATA_SIZE;
  uint8_t sequence : SEQUENCE_SIZE;
  PackageTypeEnum type;
  uint8_t data[MAX_DATA_SIZE];
  uint8_t crc;
  uint16_t size;
};
}  // namespace network

#endif