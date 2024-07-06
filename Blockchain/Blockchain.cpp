#include "Blockchain.hpp"

#include "Utilities/CodeGeneration/proto_models.h"
#include "Utilities/CryptoUtilities.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>

cumton::blockchain::BlockChain::BlockChain()
{
    proto::Block block = {1, utilities::crypto::sha256("test"), utilities::crypto::sha256("test1"),
                          1, 1, 1, 1};

    FBE::proto::BlockModel writer;
    writer.serialize(block);

    std::ofstream file("filename.txt", std::ios::binary);

    file.write((char *)writer.buffer().data(), writer.buffer().size());

    file.close();

    FBE::proto::BlockModel writer1;
    std::ifstream file1("filename.txt", std::ios::binary);

    std::vector<uint8_t> data;

    std::array<char, 104> array_temp;
    file1.read(array_temp.data(), std::streamsize(array_temp.size()));
    file1.close();

    for (int i = 0; i < array_temp.size(); i++)
        data.push_back((uint8_t)array_temp[i]);

    writer1.attach(data);

    proto::Block block1;

    writer1.deserialize(block1);
}
