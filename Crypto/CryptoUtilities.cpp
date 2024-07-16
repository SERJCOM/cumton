#include "CryptoUtilities.h"
#include <sstream>
#include <iostream>
#include <iomanip>

cumton::crypto::SHA256 cumton::crypto::sha256(const std::string &str)
{
    std::array<unsigned char, SHA256_LENGTH> hash;

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash.data(), &sha256);

    return hash;
}

cumton::crypto::SHA256 cumton::crypto::sha256(const std::vector<uint8_t> &data)
{
    std::array<unsigned char, SHA256_LENGTH> hash;

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.data(), data.size());
    SHA256_Final(hash.data(), &sha256);

    return hash;
}

cumton::crypto::SHA256 cumton::crypto::sha256(void *data, size_t size)
{
    std::array<unsigned char, SHA256_LENGTH> hash;

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, size);
    SHA256_Final(hash.data(), &sha256);

    return hash;
}

std::ostream &operator<<(std::ostream &stream, cumton::crypto::SHA256 &sha256)
{
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)sha256[i];
    }

    stream << ss.str();
    return stream;
}
