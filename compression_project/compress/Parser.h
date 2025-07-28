#pragma once

#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <unordered_map>
using std::unordered_map;
#include <utility>
using std::move;
#include <vector>
using std::vector;
#include "Token.h"
#include "Tuple.h"
#include "Heap.h"

class Parser {
private:
    vector<Token> input;
    unordered_map<string, int> frequencies;
    Heap compressible_tokens;

    void generate_frequencies() {
        for (auto const& t : input) {
            TokenType t_type = t.get_type();
            if (t_type == STRING || t_type == DIGIT) {
                frequencies[t.get_value()]++;
            }
        }
    }

public:
    explicit Parser (vector<Token> input) : input(move(input)) {
        generate_frequencies();
    }

    [[nodiscard]] string print_frequencies() const {
        // returns a string representation of the frequencies
        stringstream out;
        for (auto const &item : frequencies) {
            out << "('" << item.first << "'," << item.second << ")" << endl;
        }
        return out.str();
    }

    [[nodiscard]] Heap& generate_compressibles() {
        for (auto const & item : frequencies) {
            Tuple new_item(item.first, item.second);
            compressible_tokens.insert(new_item);
        }
        return compressible_tokens;
    }

    [[nodiscard]] Heap& get_compressible() {
        return compressible_tokens;
    }
};