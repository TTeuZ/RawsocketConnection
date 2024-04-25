#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>

namespace network {
class Command {
  Command() = delete;

  virtual ~Command() = default;

 public:
  void static listVideos();

  void static downloadVideo();
};
}  // namespace network

#endif