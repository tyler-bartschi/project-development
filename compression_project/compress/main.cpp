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
#include <filesystem>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Compressor.h"

namespace fs = std::filesystem;

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
    '\'', '"', ',', '<', '.', '>', '/', '?', ' ', '\n', '\t', '\r'
};

bool is_text_file(const fs::path &file_path, const size_t &check_size = 4096) {
    ifstream in(file_path, std::ios::binary);

    if (!in.is_open()) {
        return false;
    }

    size_t count = 0;
    char ch;

    while (count < check_size && in.get(ch)) {
        if (ch == '\0') {
            return false;
        }
        count++;
    }
    return true;
}

int validate_infile(const fs::path &input) {
    if (!fs::exists(input)) {
        cerr << "Invalid argument: " << input.filename().string() << " is an invalid path." << endl;
        return 2;
    }
    return 0;
}

void check_if_open(ifstream &file, const string &filename) {
    if (!file.is_open()) {
        stringstream msg;
        msg << "Error: " << filename << " could not be opened." << endl;
        throw std::invalid_argument(msg.str());
    }
}

void check_if_open(ofstream &file, const string &filename) {
    if (!file.is_open()) {
        stringstream msg;
        msg << "Error: " << filename << " could not be opened." << endl;
        throw std::invalid_argument(msg.str());
    }
}

void do_file_compression(const string &input, const fs::path &output) {
    Scanner s(input);
    const vector<Token> tokens = s.tokenize();

    Parser p(tokens);
    Heap &tuples = p.generate_compressibles();

    Compressor c;
    const unordered_map<string, string> compressed = c.compress(tuples);
    const string result = c.compress_tokens(tokens, compressed);

    ofstream out;
    out.open(output);
    check_if_open(out, output.filename().string());
    out << result;
    out.close();
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Invalid number of arguments." << endl;
        cerr << "Usage: ./<executable> <input file or folder> <output file or folder>" << endl;
        return 1;
    }

    const fs::path input = argv[1];
    const fs::path output = argv[2];

    if (validate_infile(input) == 2) {
        return 2;
    }

    if (fs::is_regular_file(input) && fs::is_regular_file(output)) {
        // both files, can proceed with file compression
        if (!is_text_file(input)) {
            cerr << "Invalid argument: " << input.filename().string() << " is not a text file." << endl;
            return 2;
        }
        ifstream in;
        in.open(input);
        check_if_open(in, input.filename().string());

        stringstream ss;
        ss << in.rdbuf();
        string file_contents = ss.str();
        in.close();

        do_file_compression(file_contents, output);
    } else if (fs::is_directory(input) && fs::is_directory(output)) {
        // both folders, can proceed with folder compression
    } else if (fs::is_regular_file(input) && fs::is_directory(output)) {
        // file input, place into a folder for output
    } else {
        cerr << "Invalid arguments. Must be two files, two folders, or an input file and an output folder." << endl;
        cerr << "Cannot be an input folder and an output file." << endl;
        return 2;
    }

    return 0;

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
    //
    // Scanner s(input);
    // vector<Token> tokens = s.tokenize();
    // // cout << s.str() << endl;
    //
    // Parser p(tokens);
    // // cout << p.print_frequencies() << endl;
    // Heap &tuples = p.generate_compressibles();
    // Compressor c;
    // const unordered_map<string, string> compressed = c.compress(tuples);
    //
    // const string result = c.compress_tokens(tokens, compressed);
    //
    // ofstream out;
    // out.open(argv[2]);
    // if (!out.is_open()) {
    //     cerr << "Unable to open file: " << argv[2] << endl;
    //     return 1;
    // }
    // out << result;
    // out.close();
    //
    // return 0;
}
