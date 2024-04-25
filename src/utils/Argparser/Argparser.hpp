#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

#include <boost/program_options.hpp>

namespace utils {
class Argparser {
  Argparser() = delete;

  virtual ~Argparser() = default;

 public:
  static bool parserArguments(int argc, char** argv);
};
}  // namespace utils

#endif