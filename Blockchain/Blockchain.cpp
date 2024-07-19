#include "Blockchain.hpp"

#include "Utilities/CodeGeneration/proto_models.h"
#include "Crypto/CryptoUtilities.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>

cumton::blockchain::BlockChain::BlockChain()
{
    db = CreateBlockChainDB(std::filesystem::path("/tmp/testdb"));
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
