#pragma once

#include <unordered_map>
using std::unordered_map;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <sstream>
using std::stringstream;
#include "Tuple.h"
#include "Heap.h"

class Compressor {
private:
    static bool all_zeros(vector<int> &indexes) {
        for (auto const &index: indexes) {
            if (index != 0) {
                return false;
            }
        }
        return true;
    }

    string generate_new_string(vector<int> &indexes) {
        const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        indexes.back()++;
        if (indexes.back() == alphabet.size()) {
            indexes.back() = 0;
            if (indexes.size() == 1) {
                indexes.push_back(0);
            } else {
                for (int i = indexes.size() - 2; i >= 0; i--) {
                    indexes.at(i)++;
                    if (indexes.at(i) != alphabet.size()) {
                        break;
                    }
                    indexes.at(i) = 0;
                }
                if (all_zeros(indexes)) {
                    indexes.push_back(0);
                }
            }
        }

        stringstream new_string;
        for (auto const &i: indexes) {
            new_string << alphabet.at(i);
        }
        return new_string.str();
    }

    string compression_map_str(const unordered_map<string, string> &m) {
        stringstream out;
        out << "[[";
        for (auto const &item : m) {
            out << "(" << item.first << "," << item.second << ")";
        }
        out << "]]";
        return out.str();
    }

public:
    Compressor() = default;

    [[nodiscard]] unordered_map<string, string> compress(Heap &tuples) {
        unordered_map<string, string> compressed;
        vector<int> indexes = {0};

        const int size = tuples.size();
        for (int i = 0; i < size; i++) {
            Tuple next = tuples.pop();
            const string new_string = generate_new_string(indexes);
            compressed[next.get_value()] = new_string;
        }

        return compressed;
    }

    [[nodiscard]] string compress_string(const vector<Token> &tokens, const unordered_map<string, string> &compression_map ) {
        stringstream out;
        out << compression_map_str(compression_map) << endl;
        for (auto const & token : tokens) {
            if (token.get_type() == SINGLE) {
                out << token.get_value();
            } else if (token.get_type() == DIGIT || token.get_type() == STRING) {
                out << compression_map.at(token.get_value());
            }
        }
        return out.str();
    }
};
