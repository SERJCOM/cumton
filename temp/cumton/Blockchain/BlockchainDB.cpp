#include <unordered_map>
#include <vector>

#include "Blockchain.hpp"
#include "BlockchainDB.hpp"


using namespace cumton::blockchain;

struct BlockLine
{

    Hash256 current_hash;
    std::vector<Hash256> next_hashes;
    Hash256 previos_hash;
};

class TempBlockChainDB : public cumton::blockchain::IBlockChainDB
{
public:

    TempBlockChainDB() = default;

    bool AddNewBlock(const Block &new_block, const Hash256 &prev_block){}

    bool AddFirstBlock(const Block &new_block){}
    
    Block *GetPreviosBlock(const Hash256 &current_block) const{}

    std::vector<Block *> GetNextBlock(const Hash256 &current_block) const{}

    bool EraceLastBlock(const Hash256 &block){}

    void RemoveTree(const Hash256 &block){}

    size_t GetSize(){}

private:
    std::map<Hash256, std::unique_ptr<Block>> blockchain_db;

    std::vector<BlockLine> blockchain_list;
};

std::unique_ptr<cumton::blockchain::IBlockChainDB> cumton::blockchain::CreateBlockChainDB()
{
    return std::make_unique<TempBlockChainDB>();
}