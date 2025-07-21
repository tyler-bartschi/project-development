#pragma once

#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <unordered_map>
using std::unordered_map;
#include <utility>
using std::move;
#include <iostream>
using std::endl;

enum TokenType {
    STRING, DIGIT, SINGLE
};

extern const unordered_map<TokenType, string> token_lookup;

class Token {
private:
    TokenType token_type;
    string value;

    static string lookup(const TokenType &token_type) {
        return token_lookup.at(token_type);
    }

public:
    Token(const TokenType &token_type, string value) : token_type(token_type), value(move(value)) {
    }

    [[nodiscard]] TokenType get_type() const {
        return token_type;
    }

    [[nodiscard]] string get_value() const {
        return value;
    }

    [[nodiscard]] string str() const {
        stringstream out;
        out << "(" << lookup(token_type) << ", " << value << ")" << endl;
        return out.str();
    }
};
