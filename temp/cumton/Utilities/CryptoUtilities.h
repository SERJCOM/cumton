#pragma once

#include <openssl/evp.h>
#include <openssl/sha.h>
#include <string>
#include <array>
#include <ostream>
#include <vector>

#define SHA256_LENGTH 32

namespace cumton::utilities::crypto
{

    

    std::array<uint8_t, SHA256_LENGTH> sha256(const std::string &str);

    std::array<uint8_t, SHA256_LENGTH> sha256(const std::vector<uint8_t> &data);

    std::array<uint8_t, SHA256_LENGTH> sha256(void *data, size_t size);

    

}

std::ostream &operator<<(std::ostream &stream, std::array<unsigned char, SHA256_LENGTH> &sha256);