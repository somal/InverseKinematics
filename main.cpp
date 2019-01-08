//
// Created by somal on 08.01.19.
//

#include <iostream>
#include <iterator>
#include <sstream>
#include "fstream"
#include "Connection.cpp"

#include <iomanip>
#include <algorithm>

void split(const std::string &str, std::vector<std::string> &v) {
    std::stringstream ss(str);
    ss >> std::noskipws;
    std::string field;
    char ws_delim;
    while (true) {
        if (ss >> field)
            v.push_back(field);
        else if (ss.eof())
            break;
        else
            v.push_back(std::string());
        ss.clear();
        ss >> ws_delim;
    }
}

using namespace std;

int main() {
    ifstream myfile;
    string line;
    myfile.open("/home/somal/Documents/2ndtest_mastersscholarshipinrobotics_sokolovmaxim/input.in");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            std::cout << line << std::endl;

            std::vector<std::string> v;
            split(line, v);

            std::for_each(v.begin(), v.end(), [](string &n) { std::stof(n); });
//            std::cout << v[0] << std::endl;
//            handle_data(v);
        }
    } else std::cout << "Unable to open file";

    myfile.close();
    return 0;
}

