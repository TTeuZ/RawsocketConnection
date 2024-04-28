#ifndef SEND_FAILED_EXCEPTION_HPP
#define SEND_FAILED_EXCEPTION_HPP

#include <stdexcept>

namespace exceptions {
class SendFailedException : public std::runtime_error {
 public:
  explicit SendFailedException(const std::string& desc);

  virtual ~SendFailedException() = default;

  const std::string desc;
};
}  // namespace exceptions

#endif