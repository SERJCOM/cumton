#include "Blockchain.hpp"

#include "Utilities/CodeGeneration/proto_models.h"
#include "Crypto/CryptoUtilities.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>

cumton::blockchain::BlockChain::BlockChain()
{
}

bool cumton::blockchain::BlockChain::AddBlock(const Block &block)
{
    blockchain_db[block.block_hash] = std::make_unique<Block>(block);
    return true;
}

std::vector<cumton::blockchain::Block *> cumton::blockchain::BlockChain::GetNextBlock(const Block &current_block) const
{
    std::vector<Block *> res;
    // TODO исправить это говно
    for (auto &i : blockchain_db)
    {
        if (i.second->prev_block == current_block.block_hash)
        {
            res.push_back(i.second.get());
        }
    }

    return res;
}

cumton::blockchain::Block *cumton::blockchain::BlockChain::GetPreviosBlock(const Block &current_block) const
{
    return blockchain_db.at(current_block.prev_block).get();
}
