#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstring>

#include "Manipulator.h"

using namespace std;


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
    float current_time = 0;
    float needed_time = input_data[3];

    auto needed_pos = vector<float>{input_data[0], input_data[1], input_data[2]};
    auto current_pos = manipulator->get_end_effector_pos();


}

vector<float> parse_line(string &line) {
    std::vector<std::string> line_vector;
    std::vector<float> input_vector;

    split(line, line_vector);

    std::for_each(line_vector.begin(), line_vector.end(),
                  [&input_vector](string &n) { input_vector.push_back(std::stof(n)); });
    return input_vector;
}

vector<unsigned char> convert_to_bytes(vector<float> &data_vector) {
    unsigned char const *p = nullptr;
    auto p_res = vector<unsigned char>();
    for (auto data: data_vector) {
        p = reinterpret_cast<unsigned char const *>(&data);
        for (std::size_t ii = 0; ii != sizeof(float); ++ii) {
            p_res.push_back(p[ii]);
        }
    }

    return p_res;
}

vector<float> convert_to_floats(vector<unsigned char> &data) {
    auto res = vector<float>();
    for (int i = 0; i < data.size() / sizeof(float); i++) {
        auto tmp = vector<unsigned char>();
        for (int j = 0; j < sizeof(float); j++)
            tmp.push_back(data[i * sizeof(float) + j]);
        float f;
        std::copy(reinterpret_cast<const char *>(&tmp[0]),
                  reinterpret_cast<const char *>(&tmp[4]),
                  reinterpret_cast<char *>(&f));
        res.push_back(f);
    }
    return res;
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

