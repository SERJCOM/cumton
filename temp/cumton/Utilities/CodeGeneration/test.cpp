#include <iostream>

#include "proto_models.h"
#include "../CryptoUtilities.h"

int main(){

    proto::Block block = {1, cumton::utilities::crypto::sha256("test"), cumton::utilities::crypto::sha256("test1"),
    1, 1, 1, 1 };

    return 0;
}