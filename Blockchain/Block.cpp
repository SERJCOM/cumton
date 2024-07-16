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

void cumton::blockchain::Block::LoadBlockFromString(std::string str)
{
    FBE::proto::BlockModel writer1;
    writer1.attach(str.data(), str.size());
}

std::string cumton::blockchain::Block::SerializeBlockToString()
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

    std::string res;
    res.resize(writer.buffer().size());

    for (int i = 0; i < writer.buffer().size(); i++)
    {
        res[i] = *(writer.buffer().data() + i);
    }

    return res;
}

std::vector<uint8_t> cumton::blockchain::Block::GetBlockBytes()
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

    std::vector<uint8_t> res;

    for (int i = 0; i < writer.buffer().size(); i++)
    {
        res.push_back(writer.buffer().data()[i]);
    }

    return res;
}

std::array<uint8_t, 32> cumton::blockchain::Block::GetBlockHash() const
{
    std::array<uint8_t, 32> hash;
    SHA256_CTX ctx;

    SHA256_Init(&ctx);
    // SHA256_Update(&ctx, (void *)&version, sizeof(version));
    // SHA256_Update(&ctx, (void *)&timestap, sizeof(timestap));
    // SHA256_Update(&ctx, (void *)&bits, sizeof(bits));
    // SHA256_Update(&ctx, (void *)&nonce, sizeof(nonce));
    // SHA256_Update(&ctx, (void *)&block_number, sizeof(block_number));
    SHA256_Update(&ctx, (void *)prev_block.data(), sizeof(uint8_t) * prev_block.size());
    // SHA256_Update(&ctx, (void *)merkle_root.data(), sizeof(uint8_t) * merkle_root.size());

    // for (auto &i : transactions)
    // {
    //     auto hash = i.GetTransactionHash();
    //     SHA256_Update(&ctx, hash.c_str(), sizeof(char) * hash.size());
    // }

    SHA256_Final(hash.data(), &ctx);

    return hash;
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
    if (file.is_open())
        file.write((char *)writer.buffer().data(), writer.buffer().size());
    else
    {
        std::cout << "ERROR WITH FILE" << std::endl;
        assert(false);
    }
    file.close();
}
