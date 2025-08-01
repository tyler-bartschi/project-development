#pragma once

#include <vector>
using std::vector;
#include <unordered_map>
using std::unordered_map;
#include <sstream>
using std::stringstream;
#include <string>
using std::string;
#include "Token.h"

class Decompressor {
public:
    Decompressor() = default;

    [[nodiscard]] static string decompress(const vector<Token> &tokens, const unordered_map<string, string> &decoding_table) {
        stringstream out;
        for (auto const & token : tokens) {
            if (token.get_type() == SINGLE) {
                out << token.get_value();
            } else if (token.get_type() == DIGIT || token.get_type() == STRING) {
                out << decoding_table.at(token.get_value());
            }
        }
        return out.str();
    }
};