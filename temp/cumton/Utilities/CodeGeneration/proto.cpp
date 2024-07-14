//------------------------------------------------------------------------------
// Automatically generated by the Fast Binary Encoding compiler, do not modify!
// https://github.com/chronoxor/FastBinaryEncoding
// Source: proto.fbe
// FBE version: 1.14.5.0
//------------------------------------------------------------------------------

#include "proto.h"

namespace proto {

InputTransaction::InputTransaction()
    : hash()
    , previos_output_index((int32_t)0ll)
{}

InputTransaction::InputTransaction(const std::array<uint8_t, 32>& arg_hash, int32_t arg_previos_output_index)
    : hash(arg_hash)
    , previos_output_index(arg_previos_output_index)
{}

bool InputTransaction::operator==(const InputTransaction& other) const noexcept
{
    return (
        true
        );
}

bool InputTransaction::operator<(const InputTransaction& other) const noexcept
{
    return false;
}

void InputTransaction::swap(InputTransaction& other) noexcept
{
    using std::swap;
    swap(hash, other.hash);
    swap(previos_output_index, other.previos_output_index);
}

std::ostream& operator<<(std::ostream& stream, const InputTransaction& value)
{
    stream << "InputTransaction(";
    {
        bool first = true;
        stream << "hash=[32][";
        for (size_t i = 0; i < 32; ++i)
        {
            stream << std::string(first ? "" : ",") << (int)value.hash[i];
            first = false;
        }
        stream << "]";
    }
    stream << ",previos_output_index="; stream << value.previos_output_index;
    stream << ")";
    return stream;
}

Transaction::Transaction()
    : version((int32_t)0ll)
    , input_count((uint32_t)0ull)
{}

Transaction::Transaction(int32_t arg_version, uint32_t arg_input_count)
    : version(arg_version)
    , input_count(arg_input_count)
{}

bool Transaction::operator==(const Transaction& other) const noexcept
{
    return (
        true
        );
}

bool Transaction::operator<(const Transaction& other) const noexcept
{
    return false;
}

void Transaction::swap(Transaction& other) noexcept
{
    using std::swap;
    swap(version, other.version);
    swap(input_count, other.input_count);
}

std::ostream& operator<<(std::ostream& stream, const Transaction& value)
{
    stream << "Transaction(";
    stream << "version="; stream << value.version;
    stream << ",input_count="; stream << value.input_count;
    stream << ")";
    return stream;
}

Block::Block()
    : version((uint32_t)0ull)
    , prev_block()
    , merkle_root()
    , timestap((uint32_t)0ull)
    , bits((uint32_t)0ull)
    , nonce((uint32_t)0ull)
    , block_number((uint64_t)0ull)
{}

Block::Block(uint32_t arg_version, const std::array<uint8_t, 32>& arg_prev_block, const std::array<uint8_t, 32>& arg_merkle_root, uint32_t arg_timestap, uint32_t arg_bits, uint32_t arg_nonce, uint64_t arg_block_number)
    : version(arg_version)
    , prev_block(arg_prev_block)
    , merkle_root(arg_merkle_root)
    , timestap(arg_timestap)
    , bits(arg_bits)
    , nonce(arg_nonce)
    , block_number(arg_block_number)
{}

bool Block::operator==(const Block& other) const noexcept
{
    return (
        true
        );
}

bool Block::operator<(const Block& other) const noexcept
{
    return false;
}

void Block::swap(Block& other) noexcept
{
    using std::swap;
    swap(version, other.version);
    swap(prev_block, other.prev_block);
    swap(merkle_root, other.merkle_root);
    swap(timestap, other.timestap);
    swap(bits, other.bits);
    swap(nonce, other.nonce);
    swap(block_number, other.block_number);
}

std::ostream& operator<<(std::ostream& stream, const Block& value)
{
    stream << "Block(";
    stream << "version="; stream << value.version;
    {
        bool first = true;
        stream << ",prev_block=[32][";
        for (size_t i = 0; i < 32; ++i)
        {
            stream << std::string(first ? "" : ",") << (int)value.prev_block[i];
            first = false;
        }
        stream << "]";
    }
    {
        bool first = true;
        stream << ",merkle_root=[32][";
        for (size_t i = 0; i < 32; ++i)
        {
            stream << std::string(first ? "" : ",") << (int)value.merkle_root[i];
            first = false;
        }
        stream << "]";
    }
    stream << ",timestap="; stream << value.timestap;
    stream << ",bits="; stream << value.bits;
    stream << ",nonce="; stream << value.nonce;
    stream << ",block_number="; stream << value.block_number;
    stream << ")";
    return stream;
}

BlockHashSha256::BlockHashSha256()
    : hash()
{}

BlockHashSha256::BlockHashSha256(const std::array<uint8_t, 32>& arg_hash)
    : hash(arg_hash)
{}

bool BlockHashSha256::operator==(const BlockHashSha256& other) const noexcept
{
    return (
        true
        );
}

bool BlockHashSha256::operator<(const BlockHashSha256& other) const noexcept
{
    return false;
}

void BlockHashSha256::swap(BlockHashSha256& other) noexcept
{
    using std::swap;
    swap(hash, other.hash);
}

std::ostream& operator<<(std::ostream& stream, const BlockHashSha256& value)
{
    stream << "BlockHashSha256(";
    {
        bool first = true;
        stream << "hash=[32][";
        for (size_t i = 0; i < 32; ++i)
        {
            stream << std::string(first ? "" : ",") << (int)value.hash[i];
            first = false;
        }
        stream << "]";
    }
    stream << ")";
    return stream;
}

BlockIndexDb::BlockIndexDb()
    : index_block()
{}

BlockIndexDb::BlockIndexDb(const std::vector<::proto::BlockHashSha256>& arg_index_block)
    : index_block(arg_index_block)
{}

bool BlockIndexDb::operator==(const BlockIndexDb& other) const noexcept
{
    return (
        true
        );
}

bool BlockIndexDb::operator<(const BlockIndexDb& other) const noexcept
{
    return false;
}

void BlockIndexDb::swap(BlockIndexDb& other) noexcept
{
    using std::swap;
    swap(index_block, other.index_block);
}

std::ostream& operator<<(std::ostream& stream, const BlockIndexDb& value)
{
    stream << "BlockIndexDb(";
    {
        bool first = true;
        stream << "index_block=[" << value.index_block.size() << "][";
        for (const auto& it : value.index_block)
        {
            stream << std::string(first ? "" : ",") << it;
            first = false;
        }
        stream << "]";
    }
    stream << ")";
    return stream;
}

} // namespace proto