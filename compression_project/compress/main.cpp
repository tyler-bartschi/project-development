#include <iostream>
using std::cout, std::cerr, std::endl;
#include <fstream>
using std::ifstream, std::ofstream;
#include <sstream>
using std::stringstream;
#include <string>
using std::string;

int main(int argc, char* argv[]) {
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

}