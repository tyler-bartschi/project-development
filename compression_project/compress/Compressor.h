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
};
