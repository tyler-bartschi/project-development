#include <iostream>
using std::cout, std::cerr, std::endl;
#include <fstream>
using std::ifstream, std::ofstream;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <unordered_map>
using std::unordered_map;
#include <unordered_set>
using std::unordered_set;
#include "Scanner.h"
#include "Token.h"
#include "Decompressor.h"

const unordered_map<TokenType, string> lookup_table = {
    {SINGLE, "SINGLE"},
    {DIGIT, "DIGIT"},
    {STRING, "STRING"},
    {EMPTY, "EMPTY"}
};

const unordered_set<char> single_values = {
    '~', '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '+', '=', '[',
    ']', '{', '}', ';', ':', '"', '\'', '|', '\\', ',', '<', '.', '>', '?', '/', '\n', ' '
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Invalid number of arguments." << endl;
        cerr << "Usage: ./<executable> <infile> <outfile>" << endl;
        return 1;
    }

    ifstream in;
    in.open(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file: " << argv[1] << endl;
        return 1;
    }

    stringstream ss;
    ss << in.rdbuf();
    string input = ss.str();
    in.close();

    try {
        Scanner s(input);
        // cout << s.str() << endl;
        // issue is that scanner thinks numbers are different tokens than the rest of the actual token value
        // fix scanner tokenizer function to properly tokenize
        string decompressed_file = Decompressor::decompress(s.get_tokens(), s.get_decoding_table());
        ofstream out;
        out.open(argv[2]);
        if (!out.is_open()) {
            cerr << "Unable to open file: " << argv[2] << endl;
            return 1;
        }
        out << decompressed_file;
        out.close();
    } catch (const std::exception &e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
