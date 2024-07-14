#include "Transaction.hpp"

#include "Utilities/CryptoUtilities.h"

// std::ostream &operator<<(std::ostream &stream, const cumton::transaction::Transaction& tx){

// }
std::string cumton::transaction::Transaction::GetTransactionHash() const
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;

    SHA256_Init(&ctx);

    for (auto &i : input)
    {
        SHA256_Update(&ctx, i.hash.c_str(), i.hash.size());
        SHA256_Update(&ctx, &i.previos_output_index, sizeof(i.previos_output_index));
    }

    for (auto &i : output)
    {
        SHA256_Update(&ctx, &i.value, sizeof(i.value));
    }

    SHA256_Update(&ctx, &version, sizeof(version));

    SHA256_Final(hash, &ctx);

    std::string hash_str(hash, hash + SHA256_DIGEST_LENGTH);
    return hash_str;
}