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

class Parser {
private:
    vector<Token> input;
    unordered_map<string, int> frequencies;

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


};