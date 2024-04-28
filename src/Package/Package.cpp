#include "Package.hpp"

#include <iostream>

namespace network {
Package::Package(uint8_t initMarker, uint8_t dataSize, uint8_t sequence, PackageTypeEnum type,
                 const uint8_t* data)
    : initMarker{initMarker}, type{type} {
  this->setDataSize(dataSize);
  this->setSequence(sequence);
  std::memcpy(this->data, data, MAX_DATA_SIZE);

  this->setCrc();
}

Package::Package(uint8_t initMarker, uint8_t dataSize, uint8_t sequence, PackageTypeEnum type)
    : initMarker{initMarker}, type{type} {
  this->setDataSize(dataSize);
  this->setSequence(sequence);
  std::memset(this->data, 0, MAX_DATA_SIZE);

  this->setCrc();
}

void Package::setDataSize(uint8_t dataSize) { this->dataSize = dataSize > 63 ? 63 : dataSize; }

void Package::setSequence(uint8_t sequence) { this->sequence = sequence > 31 ? 31 : sequence; }

void Package::setCrc() { std::cout << static_cast<int>(this->dataSize) << std::endl; }
}  // namespace network
