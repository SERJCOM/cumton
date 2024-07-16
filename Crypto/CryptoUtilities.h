#pragma once

#include <openssl/evp.h>
#include <openssl/sha.h>
#include <string>
#include <array>
#include <ostream>
#include <vector>

#include "Hash.hpp"

namespace cumton::crypto
{

    SHA256 sha256(const std::string &str);

    SHA256 sha256(const std::vector<uint8_t> &data);

    SHA256 sha256(void *data, size_t size);

}

std::ostream &operator<<(std::ostream &stream, cumton::crypto::SHA256 &sha256);