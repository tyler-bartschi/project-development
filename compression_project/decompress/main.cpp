#include <iostream>
using std::cout, std::cerr, std::endl, std::cin;
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
#include <filesystem>
#include "Scanner.h"
#include "Token.h"
#include "Decompressor.h"

namespace fs = std::filesystem;

const unordered_map<TokenType, string> lookup_table = {
    {SINGLE, "SINGLE"},
    {DIGIT, "DIGIT"},
    {STRING, "STRING"},
    {EMPTY, "EMPTY"}
};

const unordered_set<char> single_values = {
    '~', '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '+', '=', '[',
    ']', '{', '}', ';', ':', '"', '\'', '|', '\\', ',', '<', '.', '>', '?', '/', '\n', ' ', '\r'
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

void do_file_decompression(const fs::path &infile, const fs::path &outfile) {
    ifstream in;
    in.open(infile);
    check_if_open(in, infile.filename().string());

    stringstream stream;
    stream << in.rdbuf();
    in.close();

    Scanner s(stream.str());
    string decompressed_file = Decompressor::decompress(s.get_tokens(), s.get_decoding_table());

    ofstream out;
    out.open(outfile);
    check_if_open(out, outfile.filename().string());
    out << decompressed_file;
    out.close();

    cout << "Decompression complete." << endl;
}

string find_decoding_table(const fs::path &infolder) {
    for (const auto &item: fs::directory_iterator(infolder)) {
        if (fs::is_regular_file(item) && item.path().filename().string() == "map.compressed") {
            ifstream in;
            in.open(item.path());
            check_if_open(in, item.path().filename().string());

            stringstream ss;
            ss << in.rdbuf();
            in.close();
            return ss.str();
        }
    }
    return "";
}

void move_file(const fs::path &source, const fs::path &destination) {
    ifstream in;
    in.open(source);
    check_if_open(in, source.filename().string());

    ofstream out;
    out.open(destination);
    check_if_open(out, destination.filename().string());

    out << in.rdbuf();

    in.close();
    out.close();
}

void decompress_file(const fs::path &infile, const fs::path &outfile,
                     const unordered_map<string, string> &decoding_table) {
    ifstream in;
    in.open(infile);
    check_if_open(in, infile.filename().string());

    stringstream stream;
    stream << in.rdbuf();
    in.close();

    const vector<Token> tokens = Scanner::tokenize_file(stream.str());
    string decompressed_file = Decompressor::decompress(tokens, decoding_table);

    ofstream out;
    out.open(outfile);
    check_if_open(out, outfile.filename().string());
    out << decompressed_file;
    out.close();
}

void do_folder_decompression(const fs::path &infolder, const fs::path &outfolder) {
    string decoding_file = find_decoding_table(infolder);
    if (decoding_file.empty()) {
        cerr << "Could not find decoding table." << endl;
        return;
    }

    Scanner table_container(decoding_file);
    const unordered_map<string, string> &decoding_table = table_container.get_decoding_table();

    if (fs::exists(outfolder)) {
        fs::remove_all(outfolder);
    }

    fs::create_directory(outfolder);
    for (auto const &item: fs::recursive_directory_iterator(infolder)) {
        fs::path relative = fs::relative(item.path(), infolder);
        fs::path dest_path = outfolder / relative;

        if (fs::is_directory(item)) {
            fs::create_directories(dest_path);
        } else if (item.path().filename().string() == "map.compressed") {
            // skip file
        } else if (fs::is_regular_file(item)) {
            fs::create_directories(dest_path.parent_path());
            if (is_text_file(item)) {
                decompress_file(item.path(), dest_path, decoding_table);
            } else {
                move_file(item.path(), dest_path);
            }
        }
    }

    cout << "Decompression complete." << endl;
}

int main(const int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Invalid number of arguments." << endl;
        cerr << "Usage: ./<executable> <input file or folder> <output file or folder>" << endl;
        cerr <<
                "Note, if input is a file, output will also be a file. If input is a folder, output will also be a folder."
                << endl;
        return 1;
    }

    const fs::path input = argv[1];
    const fs::path output = argv[2];

    if (fs::exists(output)) {
        cout << "Warning: " << output.filename().string() <<
                " already exists. Proceeding with decompression will overwrite all content currently stored there." <<
                endl;
        cout << "Would you like to proceed? (y/n) ";
        string user_response;
        cin >> user_response;
        if (user_response == "n" || user_response == "N") {
            cout << "\nCanceling operation..." << endl;
            return 3;
        }
    }

    if (fs::is_regular_file(input) && is_text_file(input)) {
        // file decompression
        do_file_decompression(input, output);
    } else if (fs::is_directory(input)) {
        // folder decompression
        do_folder_decompression(input, output);
    } else {
        cerr << "Invalid argument: " << input.filename().string() << endl;
        cerr << "Must be a text file or compressed folder." << endl;
        return 2;
    }

    return 0;
}
