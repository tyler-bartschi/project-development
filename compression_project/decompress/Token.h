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

extern const unordered_map<TokenType, string> lookup_table;

class Token {
private:
    TokenType t_type;
    string value;

    static string lookup(const TokenType &t) {
        return lookup_table.at(t);
    }

public:
    Token() : t_type(EMPTY) {
    };

    Token(const TokenType &t_type, string value) : t_type(t_type), value(move(value)) {
    };

    [[nodiscard]] TokenType get_type() const {
        return t_type;
    }

    [[nodiscard]] string get_type_string() const {
        return lookup(t_type);
    }

    [[nodiscard]] string get_value() const {
        return value;
    }

    [[nodiscard]] string str() const {
        stringstream out;
        out << "(" << lookup(t_type) << ",'";

        for (const char &c: value) {
            switch (c) {
                case '\n':
                    out << "\\n";
                    break;
                case '\t':
                    out << "\\t";
                    break;
                case '\\':
                    out << "\\\\";
                    break;
                case '\'':
                    out << "\\'";
                    break;
                default:
                    out << c;
            }
        }

        out << "')";
        return out.str();
    }
};
