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
#include "Token.h"
#include "Scanner.h"

const unordered_map<TokenType, string> token_lookup = {
    // map of TokenTypes to strings, intended for the str() method of Token
    {STRING, "STRING"},
    {DIGIT, "DIGIT"},
    {SINGLE, "SINGLE"},
    {EMPTY, "EMPTY"},
};

const unordered_set<string> single_values = {
    // set of all single values for Tokens
    "~", "`", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")",
    "-", "_", "=", "+", "[", "]", "{", "}", "|", "\\", ":", ";",
    "'", "\"", ",", "<", ".", ">", "/", "?", " ", "\n", "\t"
};

int main(int argc, char *argv[]) {
    // if (argc != 3) {
    //     cerr << "Invalid number of arguments." << endl;
    //     cerr << "Usage: ./<executable> <infile> <outfile>" << endl;
    //     return 1;
    // }
    //
    // ifstream in;
    // in.open(argv[1]);
    // if (!in.is_open()) {
    //     cerr << "Unable to open file: " << argv[1] << endl;
    //     return 1;
    // }
    //
    // stringstream ss;
    // ss << in.rdbuf();
    // string input = ss.str();
    // in.close();


    return 0;
}
