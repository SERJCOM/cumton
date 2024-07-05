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
        uint32_t inpuc_count;
        std::vector<InputTransaction> input;
        uint32_t output_count;
        std::vector<OutputTransaction> output;

        friend std::ostream &operator<<(std::ostream &stream, Transaction &tx)
        {
            stream << "version: " << tx.version << "\n";
            stream << "inpuc_count: " << tx.inpuc_count << "\n";

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