//Cryptocurrency Unified Monetary Token for Online Networks - CUMTON

#pragma once

#include <cstdint>
#include <array>
#include "Transaction.hpp"
#include <iostream>
#include "Utilities/CryptoUtilities.h"

namespace cumton::blockchain
{

    struct Block
    {
        int32_t version;
        std::array<unsigned char, 32> prev_block;
        std::array<unsigned char, 32> merkle_root;
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
                                       nonce(nonce), block_number(block_number) {}

        void AddTransaction(const transaction::Transaction &transaction)
        {
            transactions.push_back(transaction);
        }

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

            for (auto &i : block.transactions)
            {
                stream << i;
            }

            stream << "}";

            return stream;
        }
    };

}