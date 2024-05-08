#ifndef BIT_ARRAY_HPP
#define BIT_ARRAY_HPP

#include <cstring>
#include <memory>
#include <vector>

#include "../Constants/Constants.hpp"
#include "BitElement.hpp"

namespace network {
class BitArray {
 public:
  BitArray(const size_t bits);

  virtual ~BitArray() = default;

  // Both can be removed (not used only the ones from BitElement)
  bool get(size_t bit) const;
  void set(size_t bit, bool val);

  size_t size() const;
  size_t sizeBytes() const;

  char* getData() const;

  void insert(char byte, size_t index);

  // Operators
  BitElement operator[](size_t bit) const;

 private:
  std::shared_ptr<std::vector<char>> mArr;
  size_t mTotalBits;
};
}  // namespace network

#endif