#include <iostream>
using std::cout, std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;

bool all_zeros(vector<int> &indexes) {
    for (auto const &index: indexes) {
        if (index != 0) {
            return false;
        }
    }
    return true;
}


void generate_new_string(vector<int> &indexes) {
    const string alphabet = "abcde";
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
}

int main() {
    vector<int> indexes = {0};
    for (int j = 0; j < 1000; j++) {
        generate_new_string(indexes);
        for (auto const &i: indexes) {
            cout << i << " ";
        }
        cout << endl;
    }
}
