#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

#include <boost/program_options.hpp>

namespace network {
class Argparser {
 public:
  Argparser() = delete;

  virtual ~Argparser() = default;

  static bool parserArguments(int argc, char** argv);
};
}  // namespace network

#endif