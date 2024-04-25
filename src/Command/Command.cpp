#include "Command.hpp"

namespace network {
void Command::listVideos() { std::cout << "listando" << std::endl; }

void Command::downloadVideo() { std::cout << "Baixando" << std::endl; }
}  // namespace network