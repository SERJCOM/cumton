#include "Blockchain.hpp"

#include "Utilities/CodeGeneration/proto_models.h"
#include "Crypto/CryptoUtilities.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>

cumton::blockchain::BlockChain::BlockChain()
{
    blockchain = CreateBlockChainDB(std::filesystem::path("/tmp/testdb"));
}

bool cumton::blockchain::BlockChain::AddBlock(const Block &block)
{
}

std::vector<cumton::blockchain::Block *> cumton::blockchain::BlockChain::GetNextBlock(const Block &current_block) const
{
}

cumton::blockchain::Block *cumton::blockchain::BlockChain::GetPreviosBlock(const Block &current_block) const
{
}

void cumton::blockchain::BlockChain::PrintAllBlocks()
{

    auto hash =  blockchain->GetLastBlock().block_hash;
    for(int i = 0; i < blockchain->GetSize(); i++){
    auto block = blockchain->GetBlock(hash);
    std::cout << block << std::endl;
    std::cout << "================ \n" << std::endl;
    hash = block.prev_block;
    }
}
