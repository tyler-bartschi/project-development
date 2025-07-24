#pragma once

#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <utility>
using std::move;

class Tuple {
private:
    string value;
    int freq;

public:
    Tuple(string value, int freq) : value(move(value)), freq(move(freq)) {
    }

    [[nodiscard]] string get_value() const {
        return value;
    }

    [[nodiscard]] int get_freq() const {
        return freq;
    }

    [[nodiscard]] string str() const {
        stringstream out;
        out << "(" << value << "," << freq << ")";
        return out.str();
    }
};
