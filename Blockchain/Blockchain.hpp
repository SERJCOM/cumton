#pragma once

#include <cstdint>
#include <array>
#include <filesystem>
#include <vector>
#include <map>
#include <array>

#include "Block.hpp"

namespace cumton::blockchain
{

    class BlockChain
    {
    public:
        BlockChain();
        

        bool AddBlock(const Block& block);

    private:

        std::map<std::array<uint8_t, 32>, std::vector<Block>> blockchain_db;

    };

}