#pragma once

#include <cstdint>
#include <array>
#include <string>
#include <vector>
#include "Object.hpp"
#include <sstream>

namespace cumton::transaction
{
    struct InputTransaction
    {
        std::string hash;
        int32_t previos_output_index;

        friend std::ostream &operator<<(std::ostream &stream, InputTransaction &tx)
        {
            stream << "hash: " << tx.hash.data() << "\n";
            stream << "previos_output_index: " << tx.previos_output_index;

            return stream;
        }
    };

    struct OutputTransaction
    {
        int64_t value;
    };

    struct Transaction
    {
        int32_t version;
        std::vector<InputTransaction> input;
        std::vector<OutputTransaction> output;

        std::string GetTransactionHash() const;

        friend std::ostream &operator<<(std::ostream &stream, Transaction &tx)
        {
            stream << "version: " << tx.version << "\n";
            stream << "inpuc_count: " << tx.input.size() << "\n";

            for (InputTransaction &i : tx.input)
            {
                stream << i << "\n";
            }

            for (OutputTransaction &i : tx.output)
            {
                stream << i.value << "\n";
            }

            return stream;
        }
    };

}