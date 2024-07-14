#include <unordered_map>
#include <vector>

#include "Blockchain.hpp"
#include "BlockchainDB.hpp"
#include <list>
#include <leveldb/db.h>

using namespace cumton::blockchain;
using namespace cumton;

class BlockChainDB : public cumton::blockchain::IBlockChainDB
{
public:
    BlockChainDB()
    {
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
        assert(status.ok());

        leveldb::Iterator *it = db->NewIterator(leveldb::ReadOptions());
        for (it->SeekToFirst(); it->Valid(); it->Next())
        {
            hash_block[crypto::StringToHash(it->key().ToString().data())] = Block{};
            hash_block[crypto::StringToHash(it->key().ToString().data())].LoadBlockFromString(it->value().ToString());
        }
    }

    bool AddNewBlock(const Block &new_block)
    {
        hash_block[new_block.block_hash] = new_block;
    }

    Block GetPreviosBlock(const cumton::crypto::SHA256 &current_block) const {}

    bool EraceLastBlock(const cumton::crypto::SHA256 &block) {}

    size_t GetSize()
    {
        return hash_block.size();
    }

    Block GetBlock(const crypto::SHA256 hash) override
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
        last_block = temp;
    }

private:
    leveldb::DB *db;

    std::map<cumton::crypto::SHA256, Block> hash_block;

    crypto::SHA256 last_block;
};

std::unique_ptr<cumton::blockchain::IBlockChainDB> cumton::blockchain::CreateBlockChainDB()
{
    // сделать эту херь статичной
    return std::make_unique<BlockChainDB>();
}
