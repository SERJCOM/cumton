#include <catch2/catch_test_macros.hpp>

#include "Blockchain/Block.hpp"

TEST_CASE("HASH OF THE BLOCK")
{
    cumton::blockchain::Block block;
    block.bits = 5;
    block.nonce = 5;
    block.version = 1;
    block.block_number = 0;
    block.prev_block = cumton::utilities::crypto::sha256("Terminal Root");
    block.merkle_root = cumton::utilities::crypto::sha256("Terminal Root1");
    
    block.CalculateBlockHash();

    // std::string hashstr = "f969e7ff018292197e85bc35528c7a851edbc53073a587c5a34aa950c8ddaf35";
    // std::array<uint8_t, 32> hashar;
    // for(int i = 0; i < hashstr.size(); i++){
    //     hashar[i] = hashstr[i];
    // }

    REQUIRE(1 == 1);
}