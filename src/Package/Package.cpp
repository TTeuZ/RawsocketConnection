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

void Package::setCrc() {
  bool bits[DATA_SIZE + SEQUENCE_SIZE + TYPE_SIZE + (this->dataSize * BITS_IN_BYTE)];
  int count{0};

  for (int i = 0; i < DATA_SIZE; ++i) bits[count++] = (this->dataSize >> (DATA_SIZE - 1 - i)) & 1;
  for (int i = 0; i < SEQUENCE_SIZE; ++i) bits[count++] = (this->sequence >> (SEQUENCE_SIZE - 1 - i)) & 1;
  for (int i = 0; i < TYPE_SIZE; ++i)
    bits[count++] = (static_cast<uint8_t>(this->type) >> (TYPE_SIZE - 1 - i)) & 1;
  for (int i = 0; i < this->dataSize; ++i)
    for (int j = 0; j < BITS_IN_BYTE; ++j) bits[count++] = (this->data[i] >> (BITS_IN_BYTE - 1 - j)) & 1;

  uint8_t crcValue = 0x00;
  for (bool bit : bits) {
    crcValue ^= (bit ? 1 : 0);
    for (int i = 0; i < BITS_IN_BYTE; ++i) {
      if (crcValue & 0x80)
        crcValue = (crcValue << 1) ^ Constants::CRC_POLYNOMIAL;
      else
        crcValue <<= 1;
    }
  }
  this->crc = crcValue;
}
}  // namespace network
