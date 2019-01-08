//
// Created by somal on 08.01.19.
//

#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "Manipulator.h"

using namespace std;

vector<vector<float>> mult(vector<vector<float>> A, vector<vector<float>> B) {
    unsigned long N = A.size();
    auto C = vector<vector<float>>(N, vector<float>(N, 0));
    cout << N << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float num = 0;
            for (int k = 0; k < N; k++) {
                num += A[i][k] * B[k][j];
            }
            C[i][j] = num;
        }
    }

    return C;
}

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

void handle_data(std::vector<float> &input_data, Manipulator *manipulator) {
    if (input_data.size() != 4) {
        throw std::invalid_argument("Data should has 4 elements inside");
    }
    float previous_time = 0;

    float x = input_data[0];
    float y = input_data[1];
    float z = input_data[2];
    float time = input_data[3];


}

vector<float> parse_line(string &line) {
    std::vector<std::string> line_vector;
    std::vector<float> input_vector;

    split(line, line_vector);

    std::for_each(line_vector.begin(), line_vector.end(),
                  [&input_vector](string &n) { input_vector.push_back(std::stof(n)); });
    return input_vector;
}

int main() {
    // Manipulator configuration
    auto joints = vector<RevoluteJoint>{RevoluteJoint("Joint0", 0, 0, 0),
                                        RevoluteJoint("Joint1", 0, -M_PI, M_PI),
                                        RevoluteJoint("Joint2", 0, -M_PI / 2, M_PI / 2),
                                        RevoluteJoint("Joint3", 0, -M_PI, M_PI)
    };

    auto links = vector<Link>{Link("Link0", 0, 0, 0, &joints[0]),
                              Link("Link1", M_PI / 2, 10, 0, &joints[1]),
                              Link("Link2", 0, 5, 0, &joints[2]),
                              Link("Link3", 0, 5, 0, &joints[3])};

    auto connection = new Connection();
    auto manipulator = new Manipulator(&links, connection);

    joints[1].set_angle(M_PI / 3);
    auto tmp = links[0].get_displacement_matrix(false);
    auto res = mult(tmp, tmp);

    // Working with input file
    ifstream myfile;
    string line;

    myfile.open("/home/somal/Documents/2ndtest_mastersscholarshipinrobotics_sokolovmaxim/input.in");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            auto vector_float = parse_line(line);
            handle_data(vector_float, manipulator);
        }
    } else std::cout << "Unable to open file";

    myfile.close();
    return 0;
}

