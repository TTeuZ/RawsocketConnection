#include <iostream>

#include "utils/Argparser/Argparser.hpp"

int main(int argc, char** argv) {
  bool loopback;

  loopback = utils::Argparser::parserArguments(argc, argv);

  std::cout << loopback << std::endl;
}