// Cryptocurrency Unified Monetary Token for Online Networks - CUMTON

#pragma once

#include <cstdint>
#include <array>
#include "Transaction.hpp"
#include <iostream>
#include <string>
#include <filesystem>

#include "Crypto/Hash.hpp"
#include "Crypto/CryptoUtilities.h"

namespace cumton::blockchain
{

    struct Block
    {
        int32_t version = 0;
        crypto::SHA256 prev_block;
        crypto::SHA256 merkle_root;
        crypto::SHA256 block_hash;
        uint32_t timestap = 0;
        uint32_t bits = 0;
        uint32_t nonce = 0;
        std::vector<transaction::Transaction> transactions;
        uint64_t block_number = 0;
        int height = 0;

        Block() = default;

        Block(int32_t version, crypto::SHA256 prev_block,
              crypto::SHA256 merkle_root,
              uint32_t timestap,
              uint32_t bits,
              uint32_t nonce,
              uint64_t block_number) : version(version), prev_block(std::move(prev_block)), timestap(timestap), bits(bits),
                                       nonce(nonce), block_number(block_number)
        {
            block_hash = GetBlockHash();
        }

        void CalculateBlockHash()
        {
            block_hash = GetBlockHash();
        }

        void AddTransaction(const transaction::Transaction &transaction);

        void SaveBlockToFile(std::filesystem::path path);

        void LoadBlockFromFile(std::filesystem::path path);

        void LoadBlockFromString(std::string str);

        std::string SerializeBlockToString();

        std::vector<uint8_t> GetBlockBytes();

        crypto::SHA256 GetBlockHash() const;

        

        Block &operator=(const Block &block)
        {
            version = block.version;
            prev_block = block.prev_block;
            merkle_root = block.merkle_root;
            block_hash = block.block_hash;
            timestap = block.timestap;
            bits = block.bits;
            nonce = block.nonce;
            transactions = block.transactions;
            block_number = block.block_number;

            return *this;
        }

        bool operator==(const Block &block) const 
        {
            // bool flag = true;
            // flag = version == block.version && prev_block == block.prev_block;
            // flag = flag && merkle_root == block.merkle_root && block_hash == block.block_hash;
            // flag = flag && timestap == block.timestap && bits == block.bits;
            // flag = &&
            // nonce == block.nonce );

            // for(int i = 0; i < transactions.size(); i++){
            //     flag = flag && transaction[i] == block[i]
            // }

            // transactions == block.transactions &&
            // block_number == block.block_number );

            return GetBlockHash() == block.GetBlockHash();

            // return flag;
        }
    };

}


std::ostream &operator<<(std::ostream &stream, cumton::blockchain::Block &block);