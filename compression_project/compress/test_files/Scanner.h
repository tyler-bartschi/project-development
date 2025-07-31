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
#include <iostream>
using std::endl;
#include "Token.h"

extern const unordered_set<char> single_values;

class Scanner {
private:
    string input;
    vector<Token> tokens;

public:
    explicit Scanner(string input) : input(move(input)) {
    }

    vector<Token> tokenize() {
        // generates a vector of token objects from the input string
        stringstream value;
        TokenType current_type = EMPTY;

        for (auto const &c: input) {
            // conversion to string to properly create token objects
            string character{c};

            if (c == '\r') {
                // ignore \r
                continue;
            }

            if (single_values.contains(c)) {
                // character is of the SINGLE type
                if (current_type == EMPTY) {
                    // no other current tokens in processing, can be added immediately
                    tokens.emplace_back(SINGLE, character);
                } else {
                    // a current token is processing, add the current token, clear the value and reset current type, then add the single token
                    tokens.emplace_back(current_type, value.str());
                    current_type = EMPTY;
                    value.str("");
                    value.clear();
                    tokens.emplace_back(SINGLE, character);
                }
            } else if (isalpha(c)) {
                // current character is an alphabetical character, and should be part of a STRING token
                if (current_type == EMPTY) {
                    // no current token, so begin creating a STRING token
                    current_type = STRING;
                    value << character;
                } else if (current_type == STRING) {
                    // STRING token is currently available, just add the character to the token
                    value << character;
                } else {
                    // a different token is currently processing, add the current token, clear and reset, then begin the STRING token
                    tokens.emplace_back(current_type, value.str());
                    value.str("");
                    value.clear();
                    current_type = STRING;
                    value << character;
                }
            } else {
                // character is not STRING or SINGLE, therefore must be DIGIT
                if (current_type == EMPTY) {
                    // no current token, begin creating a DIGIT token
                    current_type = DIGIT;
                    value << character;
                } else if (current_type == DIGIT) {
                    // current token is a DIGIT, so just add the character
                    value << character;
                } else {
                    // different token in processing, add the current token, clear and reset, begin the DIGIT token
                    tokens.emplace_back(current_type, value.str());
                    value.str("");
                    value.clear();
                    current_type = DIGIT;
                    value << character;
                }
            }
        }

        if (current_type != EMPTY) {
            // if the current type is STRING or DIGIT, add it to the vector
            tokens.emplace_back(current_type, value.str());
        }

        return tokens;
    }

    [[nodiscard]] vector<Token> get_tokens() const {
        // returns the vector of Token objects
        return tokens;
    }

    [[nodiscard]] string str() const {
        // returns the vector of token objects as a string with on Token object per line
        stringstream out;
        for (auto const &token : tokens) {
            out << token.str() << endl;
        }
        return out.str();
    }
};
