#include <iostream>

#include "Blockchain/Block.hpp"
#include "Crypto/CryptoUtilities.h"
#include "Blockchain/Blockchain.hpp"
#include "Blockchain/BlockchainDB.hpp"

#include <assert.h>

using namespace std;
using namespace cumton::blockchain;
using namespace cumton;

void Test1()
{
    cumton::blockchain::BlockChain chain;

    cumton::blockchain::Block block;
    block.bits = 5;
    block.nonce = 5;
    block.version = 1;
    block.block_number = 0;
    block.prev_block = cumton::crypto::sha256("Terminal Root");
    block.merkle_root = cumton::crypto::sha256("Terminal Root1");

    block.CalculateBlockHash();

    cout << block << endl;
}

void Test2()
{
    auto db = CreateBlockChainDB("/tmp/testdb");

    Block block1;
    block1.prev_block = crypto::sha256("1");
    block1.CalculateBlockHash();

    Block block2;
    block2.prev_block = block1.block_hash;
    block2.CalculateBlockHash();

    Block block3;
    block3.prev_block = block2.block_hash;
    block3.CalculateBlockHash();

    db->AddNewBlock(block1);
    db->AddNewBlock(block2);
    db->AddNewBlock(block3);

    std::cout << db->GetSize() << std::endl;

    // crypto::SHA256 hash = db->GetLastBlock().block_hash;
    // std::cout << "hash1: " << hash << std::endl;

    // std::cout << "hash2: " << block3.block_hash << std::endl;
}

void Test3()
{
    auto db = CreateBlockChainDB("/tmp/testdb");

    std::cout << db->GetSize() << std::endl;

    Block block1;
    block1.prev_block = crypto::sha256("1");
    block1.CalculateBlockHash();
    std::cout << "test3 block1 hash  " << block1.block_hash << std::endl;

    Block block2;
    block2.prev_block = block1.block_hash;
    block2.CalculateBlockHash();
    std::cout << "test3 block2 hash  " << block2.block_hash << std::endl;

    Block block3;
    block3.prev_block = block2.block_hash;
    block3.CalculateBlockHash();
    std::cout << "test3 block3 hash  " << block3.block_hash << std::endl;

    // std::cout << block2.block_hash << "\n";

    crypto::SHA256 hash = db->GetLastBlock().block_hash;
    std::cout << "test3 hash " << hash << std::endl;
    std::cout << "test3 block3 hash  " << block3.block_hash << std::endl;

    assert(db->GetLastBlock() == block3);
}

int main()
{
    Test2();
    Test3();

    return 0;
}
