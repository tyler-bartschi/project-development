#pragma once

#include <sstream>
using std::stringstream;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <unordered_set>
using std::unordered_set;
#include <utility>
using std::move;
#include <cctype>
using std::isalpha;
#include "Token.h"

extern const unordered_set<string> single_values;

class Scanner {
private:
    string input;
    vector<Token> tokens;

public:
    explicit Scanner(string input) : input(move(input)) {
    }

    vector<Token> tokenize() {
        stringstream value;
        TokenType current_type = EMPTY;
        for (auto const &c : input) {
            string character{c};

            if (single_values.contains(character)) {
                if (current_type == EMPTY) {
                    tokens.emplace_back(SINGLE, character);
                } else {
                    tokens.emplace_back(current_type, value.str());
                    current_type = EMPTY;
                    value.str("");
                    value.clear();
                    tokens.emplace_back(SINGLE, character);
                }
            } else if (isalpha(c)) {
                if (current_type == EMPTY) {
                    current_type = STRING;
                    value << character;
                } else if (current_type == STRING) {
                    value << character;
                } else {
                    tokens.emplace_back(current_type, value.str());
                    value.str("");
                    value.clear();
                    current_type = STRING;
                    value << character;
                }
            } else {
                if (current_type == EMPTY) {
                    current_type = DIGIT;
                    value << character;
                } else if (current_type == DIGIT) {
                    value << character;
                } else {
                    tokens.emplace_back(current_type, value.str());
                    value.str("");
                    value.clear();
                    value << character;
                }
            }
        }
        tokens.emplace_back(current_type, value.str());
        return tokens;
    }
};
