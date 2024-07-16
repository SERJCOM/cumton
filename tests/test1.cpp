#include <catch2/catch_test_macros.hpp>

#include "Blockchain/Block.hpp"
#include "Blockchain/BlockchainDB.hpp"

#include <iostream>

using namespace cumton::blockchain;
using namespace cumton;

TEST_CASE("BLOCKCHAIN DB TEST")
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

    REQUIRE(db->GetSize() == 3);

    REQUIRE(db->GetBlock(block2.block_hash) == block2);

    REQUIRE(db->GetBlock(block1.block_hash) == block1);

    REQUIRE(db->GetLastBlock() == block3);

    db->RemoveBlock();

    REQUIRE(db->GetSize() == 2);

    REQUIRE(db->GetLastBlock() == block2);
}

TEST_CASE("BlockchainDB test2")
{
    auto db = CreateBlockChainDB("/tmp/testdb");

    REQUIRE(db->GetSize() == 2);

    std::cout << db->GetSize() << std::endl;

    // REQUIRE(db->GetSize() == 3);

    Block block1;
    block1.prev_block = crypto::sha256("1");
    block1.CalculateBlockHash();

    Block block2;
    block2.prev_block = block1.block_hash;
    block2.CalculateBlockHash();

    REQUIRE(db->GetLastBlock() == block2);
}