#include <iostream>

#include "Blockchain/Block.hpp"
#include "Utilities/CryptoUtilities.h"

using namespace std;

int main()
{

    cumton::blockchain::Block block;
    block.bits = 5;
    block.nonce = 5;
    block.version = 1;
    block.block_number = 0;
    block.prev_block = cumton::utilities::crypto::sha256("Terminal Root");
    block.merkle_root = cumton::utilities::crypto::sha256("Terminal Root1");
    

    cout << block << endl;

    return 0;
}
