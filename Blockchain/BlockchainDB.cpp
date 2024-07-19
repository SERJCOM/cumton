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

#include <iostream>

using namespace cumton::blockchain;
using namespace cumton;

leveldb::Status GetLevelDbValue(leveldb::DB *db, std::string key, std::string &value)
{
    return db->Get(leveldb::ReadOptions(), key, &value);
}

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

        std::string hash;
        std::string value;

        if (GetLevelDbValue(db, "last_block", hash).ok())
        {
            last_block = crypto::StringToHash(hash);
            int i = 0;
            while (true)
            {
                Block temp;
                if (GetLevelDbValue(db, hash, value).IsNotFound())
                {
                    break;
                }
                temp.LoadBlockFromString(value);
                temp.CalculateBlockHash();
                hash_block[crypto::StringToHash(hash)] = temp;

                hash = crypto::HashToString(temp.prev_block);
            }
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

        db->Put(leveldb::WriteOptions(), "last_block", crypto::HashToString(last_block));

        delete db;
    }

    bool AddNewBlock(const Block &new_block) override
    {
        if(hash_block.count(new_block.block_hash) != 0){
            throw std::logic_error("the block is already present in the database");
        }
        
        last_block = new_block.block_hash;

        if (hash_block.empty())
        {
            hash_block[new_block.block_hash] = new_block;
            hash_block[new_block.block_hash].height = 1;
        }
        else
        {
            hash_block[new_block.block_hash] = new_block;
            hash_block[new_block.block_hash].height = GetBlockHeight(new_block.prev_block) + 1;
        }
    }

    void Clear()
    {
        hash_block.clear();
        last_block.fill(0);
    }

    Block GetPreviosBlock(const cumton::crypto::SHA256 &current_block) const override
    {
        return GetBlock(hash_block.at(current_block).prev_block);
    }

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

    // void RemoveBlock() override
    // {
    //     crypto::SHA256 temp = GetBlock(last_block).prev_block;
    //     hash_block.erase(last_block);
    //     block_height.erase(last_block);
    //     last_block = temp;
    // }

    int GetBlockHeight(const crypto::SHA256 &hash) const override
    {
        auto it = hash_block.find(hash);

        if (it == hash_block.end())
        {
            throw std::length_error("there is not such block in blockchain");
        }

        return it->second.height;
    }

    int GetCommonRelativeHeightBetweenBlocks(const crypto::SHA256 &hash1, const crypto::SHA256 &hash2) const override
    {
        return std::abs(GetBlockHeight(hash1) - GetBlockHeight(hash2));
    }

private:
    leveldb::DB *db;

    std::map<cumton::crypto::SHA256, Block> hash_block;

    crypto::SHA256 last_block;
};

std::unique_ptr<cumton::blockchain::IBlockChainDB> cumton::blockchain::CreateBlockChainDB(std::filesystem::path path)
{
    // сделать эту херь статичной
    return std::make_unique<BlockChainDB>(path);
}
