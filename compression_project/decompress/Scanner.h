#pragma once

#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <unordered_map>
using std::unordered_map;
#include <vector>
using std::vector;
#include <utility>
using std::move;
#include <unordered_set>
using std::unordered_set;
#include "Token.h"

extern const unordered_set<char> single_values;

class Scanner {
private:
    string input;
    vector<Token> tokens;
    unordered_map<string, string> decoding_table;

    void generate_encoding_table() {
        if (input.at(0) != '[') {
            throw std::invalid_argument("Not a valid compressed file");
        }

        int index = 0;
        stringstream value;
        stringstream compressed_value;
        string current_type;
        while (input.at(index) != ']') {
            char cur = input.at(index++);
            switch (cur) {
                case ('('):
                    current_type = "string";
                    break;
                case (','):
                    current_type = "compressed";
                    break;
                case (')'):
                    current_type = "";
                    decoding_table[compressed_value.str()] = value.str();
                    value.str("");
                    value.clear();
                    compressed_value.str("");
                    compressed_value.clear();
                    break;
                default:
                    if (current_type == "string") {
                        value << cur;
                    } else if (current_type == "compressed") {
                        compressed_value << cur;
                    }
                    break;
            }
        }
        index += 3;
        stringstream new_input;
        for (size_t i = index; i < input.size(); i++) {
            new_input << input.at(i);
        }
        input = new_input.str();
    }

    void tokenize() {
        generate_encoding_table();

        stringstream value;
        TokenType current_type = EMPTY;

        for (auto const &c: input) {
            string character{c};

            if (c == '\r') {
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
    }

public:
    explicit Scanner(string input) : input(move(input)) {
        tokenize();

    }

    [[nodiscard]] vector<Token>& get_tokens() {
        return tokens;
    }

    [[nodiscard]] unordered_map<string, string>& get_decoding_table() {
        return decoding_table;
    }

    [[nodiscard]] string str() const {
        stringstream out;
        out << "Decoding map" << endl;
        for (auto const & item : decoding_table) {
            out << "('" << item.first << "','" << item.second << "')" << endl;
        }
        out << endl << "Tokens" << endl;
        for (auto const &token: tokens) {
            out << token.str() << endl;
        }
        return out.str();
    }
};
