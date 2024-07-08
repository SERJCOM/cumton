#pragma once

#include <memory>

#include "Block.hpp"
#include "Crypto/Hash.hpp"


namespace cumton::blockchain
{

    // Эта хуйня нужна для того чтобы управлять блоками, следить за последовательностью блоков и тд короче хуетень

    class IBlockChainDB
    {
    public:
        IBlockChainDB() = default;
        virtual ~IBlockChainDB() = default;

        virtual bool AddNewBlock(const Block &new_block, const Hash256 &prev_block) = 0;

        virtual bool AddFirstBlock(const Block &new_block) = 0;

        virtual Block *GetPreviosBlock(const Hash256 &current_block) const = 0;

        virtual std::vector<Block *> GetNextBlock(const Hash256 &current_block) const = 0;

        virtual bool EraceLastBlock(const Hash256 &block) = 0;

        virtual void RemoveTree(const Hash256 &block) = 0;

        virtual size_t GetSize() = 0;
    };

    std::unique_ptr<IBlockChainDB> CreateBlockChainDB();

}