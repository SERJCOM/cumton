#include <catch2/catch_test_macros.hpp>

#include "Blockchain/Block.hpp"
#include "Blockchain/BlockchainDB.hpp"

#include <iostream>

using namespace cumton::blockchain;
using namespace cumton;

TEST_CASE("Block test serialization")
{
    Block block1;
    block1.bits = 1;
    block1.block_number = 11;
    block1.height = 111;
    block1.prev_block = crypto::sha256("1");
    block1.CalculateBlockHash();

    std::string block_s = block1.SerializeBlockToString();

    Block block2;
    block2.LoadBlockFromString(block_s);
    block2.CalculateBlockHash();

    REQUIRE(block2.bits == block1.bits);
    REQUIRE(block2.block_number == block1.block_number);
    REQUIRE(block2.height == block1.height);
    REQUIRE(block2.block_hash == block1.block_hash);
}

TEST_CASE("blockchain db TEST")
{
    {
        auto db = CreateBlockChainDB("/tmp/testdb");

        Block block1;
        block1.prev_block = crypto::sha256("1");
        block1.CalculateBlockHash();

        CHECK_THROWS(db->AddNewBlock(block1));
    }
    {
        auto db = CreateBlockChainDB("/tmp/testdb");

        db->Clear();

        Block block1;
        block1.block_number=1;
        block1.prev_block = crypto::sha256("1");
        block1.CalculateBlockHash();

        Block block2;
        block2.block_number = 2;
        block2.prev_block = block1.block_hash;
        block2.CalculateBlockHash();

        Block block3;
        block3.block_number=3;
        block3.prev_block = block2.block_hash;
        block3.CalculateBlockHash();

        db->AddNewBlock(block1);
        db->AddNewBlock(block2);
        db->AddNewBlock(block3);

        auto hash =  db->GetLastBlock().block_hash;
        for(int i = 0; i < db->GetSize(); i++){
            auto block = db->GetBlock(hash);
            std::cout << block << std::endl;
            std::cout << "================ \n" << std::endl;
            hash = block.prev_block;
        }

        REQUIRE(db->GetSize() == 3);

        REQUIRE(db->GetBlock(block2.block_hash) == block2);

        REQUIRE(db->GetBlock(block1.block_hash) == block1);

        REQUIRE(db->GetLastBlock() == block3);
    }
    {
        auto db = CreateBlockChainDB("/tmp/testdb");

        REQUIRE(db->GetSize() == 3);

        Block block1;
        block1.prev_block = crypto::sha256("1");
        block1.CalculateBlockHash();

        Block block2;
        block2.prev_block = block1.block_hash;
        block2.CalculateBlockHash();

        Block block3;
        block3.prev_block = block2.block_hash;
        block3.CalculateBlockHash();

        REQUIRE(db->GetLastBlock() == block3);
    }
}
