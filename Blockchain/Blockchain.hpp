#pragma once

#include <filesystem>
#include <vector>
#include <iostream>
#include <memory
#include "BlockchainDB.hpp"
#include "Crypto/Hash.hpp"
#include "Block.hpp"

namespace cumton::blockchain
{
    class BlockChain
    {
    public:
        BlockChain();

        bool AddBlock(const Block &block);

        std::vector<Block *> GetNextBlock(const Block &current_block) const;

        Block *GetPreviosBlock(const Block &current_block) const;

    private:
        std::unique_ptr<IBlockChainDB> blockchain;
    };

}