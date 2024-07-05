#pragma once

#include <openssl/evp.h>
#include <openssl/sha.h>
#include <string>
#include <array>
#include <ostream>

#define SHA256_LENGTH 32

namespace cumton::utilities::crypto
{

    std::array<unsigned char, SHA256_LENGTH> sha256(const std::string &str);

}

std::ostream &operator<<(std::ostream &stream, std::array<unsigned char, SHA256_LENGTH> &sha256);