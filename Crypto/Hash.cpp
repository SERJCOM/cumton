#include "Hash.hpp"

#include <iostream>

namespace cumton::crypto
{

    SHA256 StringToHash(const std::string &str)
    {
        SHA256 res;
        for (int i = 0; i < str.size(); i++)
            res[i] = str.at(i);
        return res;
    }

    std::string HashToString(const SHA256 &hash)
    {
        std::string res;
        res.resize(hash.size());

        for (int i = 0; i < hash.size(); i++)
        {
            res[i] = hash.at(i);
        }

        return res;
    }
}