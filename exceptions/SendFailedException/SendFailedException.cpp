#include "SendFailedException.hpp"

using namespace exceptions;

SendFailedException::SendFailedException(const std::string& desc)
    : runtime_error{"Fail in send package through socket"}, desc{desc} {};
