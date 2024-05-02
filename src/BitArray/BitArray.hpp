#ifndef BIT_ARRAY_HPP
#define BIT_ARRAY_HPP

#include <cstring>
#include <memory>

#include "../Constants/Constants.hpp"
#include "BitElement.hpp"

namespace network {
class BitArray {
 public:
  BitArray(const size_t bits);

  virtual ~BitArray() = default;

  bool get(size_t bit) const;
  void set(size_t bit, bool val);

  size_t size() const;
  size_t sizeBytes() const;

  char* getData() const;

  // Operators
  BitElement operator[](size_t bit) const;

 private:
  std::shared_ptr<char[]> mArr;
  const size_t mTotalBits;
};
}  // namespace network

#endif