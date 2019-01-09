#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstring>

#include "Manipulator.h"

using namespace std;

vector<vector<float>> matrix_multiplication(vector<vector<float>> A, vector<vector<float>> B) {
    unsigned long N = A.size();
    auto C = vector<vector<float>>(N, vector<float>(N, 0));
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

vector<float> get_end_effector_pos(vector<Link> links) {
    vector<vector<float>> common_displacement_matrix = links[0].get_displacement_matrix(false);
    for (int i = 1; i < links.size(); i++) {
        vector<vector<float>> matrix = links[i].get_displacement_matrix(false);
//        cout << links[i].joint->get_angle() << endl;

//        for (int k = 0; k < matrix.size(); k++) {
//            for (int j = 0; j < matrix[0].size(); j++)
//                cout << common_displacement_matrix[k][j] << ' ';
//            cout << endl;
//        }
//        cout << endl;

        common_displacement_matrix = matrix_multiplication(common_displacement_matrix,
                                                           links[i].get_displacement_matrix(false));
    }


//    for (int i = 0; i < common_displacement_matrix.size(); i++) {
//        for (int j = 0; j < common_displacement_matrix[0].size(); j++)
//            cout << common_displacement_matrix[i][j] << ' ';
//        cout << endl;
//    }
//    cout << endl;

    auto res = vector<float>{common_displacement_matrix[0][3],
                             common_displacement_matrix[1][3],
                             common_displacement_matrix[2][3]};
    return res;
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
    float i = 0;
    vector<float> tmp;
    while (i < M_PI) {
        joints[1].set_angle(i);
        i = i + M_PI / 16;
        tmp = get_end_effector_pos(links);
        for (auto n: tmp) cout << n << ' ';
        cout << endl;
    }



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

