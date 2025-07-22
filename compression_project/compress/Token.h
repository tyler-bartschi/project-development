#pragma once

#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <unordered_map>
using std::unordered_map;
#include <utility>
using std::move;

enum TokenType {
    STRING, DIGIT, SINGLE, EMPTY
};

// defined in main.cpp
extern const unordered_map<TokenType, string> token_lookup;

class Token {
private:
    TokenType token_type;
    string value;

    static string lookup(const TokenType &token_type) {
        // returns the string value in the token_lookup map
        return token_lookup.at(token_type);
    }

public:
    Token() : token_type(EMPTY) {
        // default constructor, sets token to EMPTY
    }

    Token(const TokenType &token_type, string value) : token_type(token_type), value(move(value)) {
        // constructor
    }

    [[nodiscard]] TokenType get_type() const {
        // returns the token type
        return token_type;
    }

    [[nodiscard]] string get_value() const {
        // returns the token's value
        return value;
    }

    [[nodiscard]] string str() const {
        // returns a string representation of the token
        stringstream out;
        out << "(" << lookup(token_type) << ",'" << value << "')";
        return out.str();
    }
};
