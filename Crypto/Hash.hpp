#pragma once

#include <array>
#include <string>


namespace cumton::crypto
{

    #define SHA256_LENGTH 32

    using SHA256 = std::array<uint8_t, SHA256_LENGTH>;

    SHA256 StringToHash(const std::string &str);

    std::string HashToString(const SHA256 &hash);

}