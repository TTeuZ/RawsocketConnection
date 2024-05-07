#include "Package.hpp"

#include <iostream>

namespace network {
Package::Package(uint8_t initMarker, uint8_t dataSize, uint8_t sequence, PackageTypeEnum type,
                 const uint8_t* data)
    : initMarker{initMarker}, type{type} {
  this->setDataSize(dataSize);
  this->setSequence(sequence);
  std::memcpy(this->data, data, MAX_DATA_SIZE);

  this->crc = this->calcCrc();
  this->size = (4 * BITS_IN_BYTE) + (this->dataSize * BITS_IN_BYTE);
}

Package::Package(uint8_t initMarker, uint8_t dataSize, uint8_t sequence, PackageTypeEnum type)
    : initMarker{initMarker}, type{type} {
  this->setDataSize(dataSize);
  this->setSequence(sequence);
  std::memset(this->data, 0, MAX_DATA_SIZE);

  this->crc = this->calcCrc();
  this->size = (4 * BITS_IN_BYTE) + (this->dataSize * BITS_IN_BYTE);
}

Package::Package(const char* const buffer) {
  size_t count{3};

  this->initMarker = buffer[0];
  this->dataSize = (buffer[1] >> 2) & 0x3F;
  this->sequence = ((buffer[1] & 0x03) << 3) | ((buffer[2] & 0xE0) >> 5);
  this->type = static_cast<PackageTypeEnum>(buffer[2] & 0x1F);
  for (size_t i = 0; i < this->dataSize; ++i) this->data[i] = buffer[count++];
  this->crc = buffer[count];
}

Package::Package(Package&& package) {
  initMarker = package.initMarker;
  dataSize = package.dataSize;
  sequence = package.sequence;
  type = package.type;
  std::memcpy(data, package.data, MAX_DATA_SIZE);
  crc = package.crc;
  size = package.size;
}

Package& Package::operator=(Package&& package) {
  initMarker = package.initMarker;
  dataSize = package.dataSize;
  sequence = package.sequence;
  type = package.type;
  std::memcpy(data, package.data, MAX_DATA_SIZE);
  crc = package.crc;
  size = package.size;

  return *this;
}

void Package::setDataSize(uint8_t dataSize) { this->dataSize = dataSize > 63 ? 63 : dataSize; }

void Package::setSequence(uint8_t sequence) { this->sequence = sequence > 31 ? 31 : sequence; }

BitArray Package::getRawPackage() {
  size_t size =
      this->size < Constants::MIN_PACKAGE_SIZE_IN_BITS ? Constants::MIN_PACKAGE_SIZE_IN_BITS : this->size;

  BitArray bits{size};
  this->fillUpRawArray(bits, true);

  return bits;
}

uint16_t Package::getSize() const { return this->size; }

PackageTypeEnum Package::getType() const { return this->type; }

uint8_t Package::getSequence() const { return this->sequence; }

bool Package::checkCrc() {
  uint8_t tempCrc{this->calcCrc()};
  return tempCrc == this->crc;
}

uint8_t Package::calcCrc() {
  size_t bits_qty = (DATA_SIZE + SEQUENCE_SIZE + TYPE_SIZE + (this->dataSize * BITS_IN_BYTE));
  BitArray bits{bits_qty};

  this->fillUpRawArray(bits, false);

  uint8_t crcValue = 0x00;
  for (size_t i = 0; i < bits.size(); ++i) {
    crcValue ^= (bits[i] ? 1 : 0);
    for (size_t i = 0; i < BITS_IN_BYTE; ++i) {
      if (crcValue & 0x80)
        crcValue = (crcValue << 1) ^ Constants::CRC_POLYNOMIAL;
      else
        crcValue <<= 1;
    }
  }

  return crcValue;
}

void Package::fillUpRawArray(BitArray bits, bool full) {
  size_t count{0};

  if (full)
    for (size_t i = 0; i < BITS_IN_BYTE; ++i)
      bits[count++] = (this->initMarker >> (BITS_IN_BYTE - 1 - i)) & 1;

  for (size_t i = 0; i < DATA_SIZE; ++i) bits[count++] = (this->dataSize >> (DATA_SIZE - 1 - i)) & 1;
  for (size_t i = 0; i < SEQUENCE_SIZE; ++i) bits[count++] = (this->sequence >> (SEQUENCE_SIZE - 1 - i)) & 1;
  for (size_t i = 0; i < TYPE_SIZE; ++i)
    bits[count++] = (static_cast<uint8_t>(this->type) >> (TYPE_SIZE - 1 - i)) & 1;
  for (size_t i = 0; i < this->dataSize; ++i)
    for (size_t j = 0; j < BITS_IN_BYTE; ++j) bits[count++] = (this->data[i] >> (BITS_IN_BYTE - 1 - j)) & 1;

  if (full)
    for (size_t i = 0; i < BITS_IN_BYTE; ++i) bits[count++] = (this->crc >> (BITS_IN_BYTE - 1 - i)) & 1;
}

void Package::dummy() {
  std::cout << this->initMarker << std::endl;
  std::cout << (int)this->dataSize << std::endl;
  std::cout << (int)this->sequence << std::endl;
  std::cout << (int)this->type << std::endl;
  for (size_t i = 0; i < this->dataSize; ++i) std::cout << this->data[i];
  std::cout << std::endl;
  std::cout << (int)this->crc << std::endl;
}
}  // namespace network
