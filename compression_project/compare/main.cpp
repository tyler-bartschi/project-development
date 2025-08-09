#include <iostream>
using std::cout, std::endl, std::cerr, std::cin;
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <filesystem>

namespace fs = std::filesystem;

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

void size_comparison(const string &data_1, const string &data_2, const fs::path &path_1, const fs::path &path_2) {
    const size_t size_one = data_1.size();
    const size_t size_two = data_2.size();
    const string path_name_one = path_1.filename().string();
    const string path_name_two = path_2.filename().string();

    cout << endl;

    if (size_one < size_two) {
        const float ratio = (static_cast<float>(size_one) / static_cast<float>(size_two)) * 100;
        cout << path_name_one << " is smaller than " << path_name_two << "." << endl;
        cout << path_name_one << " is " << ratio << "% the size of " << path_name_two << endl;
    } else if (size_two < size_one) {
        const float ratio = (static_cast<float>(size_two) / static_cast<float>(size_one)) * 100;
        cout << path_name_two << " is smaller than " << path_name_one << "." << endl;
        cout << path_name_two << " is " << ratio << "% the size of " << path_name_one << endl;
    } else {
        cout << path_name_one << " and " << path_name_two << " are the same size." << endl;
    }
}

void character_comparison(const string &data_1, const string &data_2) {
    size_t count_1 = 0;
    size_t count_2 = 0;

    while (count_1 < data_1.size() && count_2 < data_2.size()) {
        if (data_1[count_1++] != data_2[count_2++]) {
            cout << "Characters in files/folders do not match exactly." << endl;
            return;
        }
    }
    if (count_1 < data_1.size() || count_2 < data_2.size()) {
        cout << "Characters in files/folders do not match exactly." << endl;
    } else {
        cout << "Characters in files/folders match exactly." << endl;
    }
}

int read_file(const fs::path &path, stringstream &stream) {
    ifstream in;

    if (fs::is_regular_file(path)) {
        if (!is_text_file(path)) {
            cerr << "Invalid argument: " << path.filename().string() << " is not a text file." << endl;
            return 2;
        }
        in.open(path);
        if (!in.is_open()) {
            cerr << "An error occured opening file: " << path.filename().string() << endl;
            return 2;
        }
        stream << in.rdbuf();
        in.close();
        return 0;
    }

    if (!fs::is_directory(path)) {
        cerr << "Invalid argument: " << path.filename().string() << " is not a file or directory." << endl;
        return 2;
    }

    bool need_endl = false;

    for (const auto &item: fs::recursive_directory_iterator(path)) {
        if (fs::is_regular_file(item)) {
            if (is_text_file(item)) {
                in.open(item.path());
                if (!in.is_open()) {
                    cerr << "An error occured opening file: " << item.path().filename().string() << endl;
                    return 2;
                }
                stream << in.rdbuf();
                in.close();
            } else {
                cout << "Ignored " << item.path().filename().string() << " because it is not a text file." << endl;
                need_endl = true;
            }
        }
    }

    if (need_endl) {
        cout << endl;
    }

    return 0;
}

int check_args(const fs::path &path1, const fs::path &path2) {
    if (!fs::exists(path1)) {
        cerr << "Invalid argument: " << path1.filename().string() << " is an invalid path." << endl;
        return 2;
    }
    if (!fs::exists(path2)) {
        cerr << "Invalid argument: " << path2.filename().string() << " is an invalid path." << endl;
        return 2;
    }
    return 0;
}

int main(const int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Incorrect arguments. Requires two folders or files to analyze." << endl;
        return 1;
    }

    const fs::path input1 = argv[1];
    const fs::path input2 = argv[2];

    if (check_args(input1, input2) == 2) {
        return 2;
    }

    stringstream ss;

    if (read_file(input1, ss) != 0) {
        return 2;
    }
    const string data_1 = ss.str();
    ss.clear();
    ss.str("");

    if (read_file(input2, ss) != 0) {
        return 2;
    }
    const string data_2 = ss.str();

    cout << "Would you like to perform an exact character comparison? (y/n)" << endl;
    string user_input;
    cin >> user_input;

    if (user_input == "y" || user_input == "Y") {
        character_comparison(data_1, data_2);
    }

    cout << endl << "Would you like to perform a size comparison? (y/n)" << endl;
    user_input = "";
    cin >> user_input;

    if (user_input == "y" || user_input == "Y") {
        size_comparison(data_1, data_2, input1, input2);
    }

    return 0;
}
