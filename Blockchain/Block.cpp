#include "Block.hpp"
#include "Utilities/CodeGeneration/proto_models.h"
#include <fstream>

void cumton::blockchain::Block::AddTransaction(const transaction::Transaction &transaction)
{
    transactions.push_back(transaction);
}

void cumton::blockchain::Block::LoadBlockFromFile(std::filesystem::path path)
{
    FBE::proto::BlockModel writer1;
    std::ifstream file1(path, std::ios::binary);
    if (file1.is_open())
    {
        file1.seekg(0, std::ios::end);
        auto file_size = file1.tellg();
        file1.seekg(0, std::ios::beg);

        std::vector<char> temp_data(file_size);
        file1.read(temp_data.data(), std::streamsize(temp_data.size()));
        std::vector<uint8_t> data;
        for (int i = 0; i < temp_data.size(); i++)
            data.push_back((uint8_t)temp_data[i]);

        writer1.attach(data);
    }
    else
    {
        std::cout << "ERROR WITH FILE" << std::endl;
        assert(false);
    }

    file1.close();
}

void cumton::blockchain::Block::SaveBlockToFile(std::filesystem::path path)
{
    proto::Block block;
    block.bits = bits;
    block.block_number = block_number;
    block.merkle_root = merkle_root;
    block.nonce = nonce;
    block.prev_block = prev_block;
    block.version = version;

    FBE::proto::BlockModel writer;
    writer.serialize(block);

    std::ofstream file(path, std::ios::binary);
    if(file.is_open())
        file.write((char *)writer.buffer().data(), writer.buffer().size());
    else{
        std::cout << "ERROR WITH FILE" << std::endl;
        assert(false);
    }
    file.close();
}
