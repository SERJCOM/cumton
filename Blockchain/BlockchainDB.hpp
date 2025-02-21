#pragma once

#include <memory>
#include <filesystem>

#include "Block.hpp"
#include "Crypto/Hash.hpp"

namespace cumton::blockchain
{

    // Эта херь нужна для того чтобы управлять блоками, следить за последовательностью блоков и тд короче хуетень

    class IBlockChainDB
    {
    public:
        IBlockChainDB() = default;
        virtual ~IBlockChainDB() = default;

        virtual bool AddNewBlock(const Block &new_block) = 0;

        virtual Block GetPreviosBlock(const crypto::SHA256 &current_block) const = 0;

        virtual size_t GetSize() = 0;

        virtual Block GetBlock(const crypto::SHA256 hash) const = 0;

        // virtual void RemoveBlock() = 0;

        virtual Block GetLastBlock() = 0;

        virtual int GetBlockHeight(const crypto::SHA256 &hash) const = 0;

        virtual int GetCommonRelativeHeightBetweenBlocks(const crypto::SHA256 &hash1, const crypto::SHA256 &hash2) const = 0;

        virtual void Clear() = 0;
    };

    std::unique_ptr<IBlockChainDB> CreateBlockChainDB(std::filesystem::path path);

}