#include <unordered_map>
#include <vector>

#include "Blockchain.hpp"
#include "BlockchainDB.hpp"
#include <list>
#include <leveldb/db.h>

#include "Crypto/CryptoUtilities.h"

#include <unordered_map>
#include <map>
#include <execution>

using namespace cumton::blockchain;
using namespace cumton;

class BlockChainDB : public cumton::blockchain::IBlockChainDB
{
public:
    BlockChainDB(std::filesystem::path path)
    {
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options, path.c_str(), &db);
        assert(status.ok());

        leveldb::Iterator *it = db->NewIterator(leveldb::ReadOptions());
        int i = 0;
        for (it->SeekToFirst(); it->Valid(); it->Next())
        {
            crypto::SHA256 hash = crypto::StringToHash(it->key().ToString());
            i++;

            std::cout << "hash" << i << " " << hash << std::endl;

            Block temp;
            temp.LoadBlockFromString(it->value().ToString());
            // тут может быть UB
            AddNewBlock(temp);
            // hash_block[hash] = Block{};
            // hash_block[hash].LoadBlockFromString(it->value().ToString());
            
        }
    }

    ~BlockChainDB()
    {
        for (auto hash_block : hash_block)
        {
            std::string res;
            leveldb::Status status = db->Get(leveldb::ReadOptions(), crypto::HashToString(hash_block.first), &res);
            if (status.IsNotFound())
            {
                db->Put(leveldb::WriteOptions(), crypto::HashToString(hash_block.first), hash_block.second.SerializeBlockToString());
            }
        }

        delete db;
    }

    bool AddNewBlock(const Block &new_block) override
    {
        last_block = new_block.block_hash;
        if (hash_block.empty())
        {
            block_height[new_block.block_hash] = 1;
        }
        else
        {
            block_height[new_block.block_hash] = GetBlockHeight(new_block.prev_block) + 1;
        }
        hash_block[new_block.block_hash] = new_block;
    }

    Block GetPreviosBlock(const cumton::crypto::SHA256 &current_block) const override
    {
        return GetBlock(hash_block.at(current_block).prev_block);
    }

    bool EraceLastBlock(const cumton::crypto::SHA256 &block) override {}

    size_t GetSize() override
    {
        return hash_block.size();
    }

    Block GetBlock(const crypto::SHA256 hash) const override
    {
        return hash_block.at(hash);
    }

    Block GetLastBlock() override
    {
        return GetBlock(last_block);
    }

    void RemoveBlock() override
    {
        crypto::SHA256 temp = GetBlock(last_block).prev_block;
        hash_block.erase(last_block);
        block_height.erase(last_block);
        last_block = temp;
    }

    int GetBlockHeight(const crypto::SHA256 &hash) const override
    {
        auto it = block_height.find(hash);

        if (it == block_height.end())
        {
            throw std::length_error("there is not such block in blockchain");
        }

        return it->second;
    }

    int GetCommonRelativeHeightBetweenBlocks(const crypto::SHA256 &hash1, const crypto::SHA256 &hash2) const override
    {
        return std::abs(GetBlockHeight(hash1) - GetBlockHeight(hash2));
    }

private:
    leveldb::DB *db;

    std::map<cumton::crypto::SHA256, Block> hash_block;

    std::map<cumton::crypto::SHA256, int> block_height;

    crypto::SHA256 last_block;
};

std::unique_ptr<cumton::blockchain::IBlockChainDB> cumton::blockchain::CreateBlockChainDB(std::filesystem::path path)
{
    // сделать эту херь статичной
    return std::make_unique<BlockChainDB>(path);
}
