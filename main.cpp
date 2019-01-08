//
// Created by somal on 08.01.19.
//

#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "Connection.h"
#include "Joint.h"

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

void handle_data(std::vector<float> &input_data) {
    if (input_data.size() != 4) {
        throw std::invalid_argument("Data should has 4 elements inside");
    }
    float previous_time = 0;

    float x = input_data[0];
    float y = input_data[1];
    float z = input_data[2];
    float time = input_data[3];


}

void parse_line(string &line, Connection *connection) {
    std::vector<std::string> line_vector;
    std::vector<float> input_vector;
    std::cout << line << std::endl;


    split(line, line_vector);

    std::for_each(line_vector.begin(), line_vector.end(),
                  [&input_vector](string &n) { input_vector.push_back(std::stof(n)); });
    handle_data(input_vector);
}

int main() {
    ifstream myfile;
    string line;
    auto connection = new Connection();
    auto *joints = new vector<RevoluteJoint>();
    auto joint1 = new RevoluteJoint("Joint1", 0, 0, 1);
    joint1->set_angle(3);
//    joints.push_back(new RevoluteJoint("Joint1", 0, 0, 1));
//    joints[0].set_angle(0);
    myfile.open("/home/somal/Documents/2ndtest_mastersscholarshipinrobotics_sokolovmaxim/input.in");
    if (myfile.is_open()) {
        while (getline(myfile, line)) parse_line(line, connection);
    } else std::cout << "Unable to open file";

    myfile.close();
    return 0;
}

