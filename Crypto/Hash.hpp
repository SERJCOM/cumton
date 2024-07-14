#pragma once

#include <array>
#include <string>

namespace cumton::crypto
{

    using SHA256 = std::array<uint8_t, 32>;

    SHA256 StringToHash(const std::string &str);

    std::string HashToString(const SHA256 &hash);

}