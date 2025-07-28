#include <iostream>
using std::cout, std::cerr, std::endl;
#include <fstream>
using std::ifstream, std::ofstream;
#include <sstream>
using std::stringstream;
#include <string>
using std::string;
#include <unordered_set>
using std::unordered_set;
#include <unordered_map>
using std::unordered_map;
#include <vector>
using std::vector;
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"

const unordered_map<TokenType, string> token_lookup = {
    // map of TokenTypes to strings, intended for the str() method of Token
    {STRING, "STRING"},
    {DIGIT, "DIGIT"},
    {SINGLE, "SINGLE"},
    {EMPTY, "EMPTY"},
};

const unordered_set<char> single_values = {
    // set of all single values for Tokens
    '~', '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
    '-', '_', '=', '+', '[', ']', '{', '}', '|', '\\', ':', ';',
    '\'', '"', ',', '<', '.', '>', '/', '?', ' ', '\n', '\t'
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

    Scanner s(input);
    vector<Token> tokens = s.tokenize();
    // cout << s.str() << endl;

    Parser p(tokens);
    // cout << p.print_frequencies() << endl;
    Heap &tuples = p.generate_compressibles();
    int size = tuples.size();
    cout << size << endl;
    for (int i = 0; i < size; i++) {
        Tuple next = tuples.pop();
        cout << next.str() << endl;
    }

    return 0;
}
