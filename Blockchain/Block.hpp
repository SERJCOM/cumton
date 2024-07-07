// Cryptocurrency Unified Monetary Token for Online Networks - CUMTON

#pragma once

#include <cstdint>
#include <array>
#include "Transaction.hpp"
#include <iostream>
#include <string>
#include <filesystem>

#include "Utilities/CryptoUtilities.h"

namespace cumton::blockchain
{

    struct Block
    {
        int32_t version;
        std::array<uint8_t, 32> prev_block;
        std::array<uint8_t, 32> merkle_root;
        std::array<uint8_t, 32> block_hash;
        uint32_t timestap;
        uint32_t bits;
        uint32_t nonce;
        std::vector<transaction::Transaction> transactions;
        uint64_t block_number;

        Block() = default;

        Block(int32_t version, std::array<unsigned char, 32> prev_block,
              std::array<unsigned char, 32> merkle_root,
              uint32_t timestap,
              uint32_t bits,
              uint32_t nonce,
              uint64_t block_number) : version(version), prev_block(std::move(prev_block)), timestap(timestap), bits(bits),
                                       nonce(nonce), block_number(block_number)
        {

            auto bytes = GetBlockBytes();
            block_hash = utilities::crypto::sha256(bytes);
        }

        void CalculateBlockHash();

        void AddTransaction(const transaction::Transaction &transaction);

        void SaveBlockToFile(std::filesystem::path path);

        void LoadBlockFromFile(std::filesystem::path path);

        std::vector<uint8_t> GetBlockBytes();

        friend std::ostream &operator<<(std::ostream &stream, Block &block)
        {
            stream << "{\n";
            stream << "Block #" << block.block_number << "\n";
            stream << "version: " << block.version << "\n";
            stream << "prev_block hash: " << block.prev_block << "\n";
            stream << "merkle_root hash: " << block.merkle_root << "\n";
            stream << "timestap: " << block.timestap << "\n";
            stream << "bits: " << block.bits << "\n";
            stream << "nonce: " << block.nonce << "\n";
            stream << "txn_count: " << block.transactions.size() << "\n";
            stream << "block hash: " << block.block_hash << "\n";

            stream << "transactions: {" << "\n";
            for (auto &i : block.transactions)
            {
                stream << i;
            }

            stream << "}\n}";

            return stream;
        }
    };

    // std::array<uint8_t, 32> GetBlockHash()

}