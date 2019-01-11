#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <zconf.h>
#include <random>

#include "Vector.h"
#include "Manipulator.h"

#ifndef DEBUG
#define DEBUG 1 // set debug mode
#endif

#if DEBUG
#define log(str) { std::cout << str << std::endl;}
#else
#define log(str)
#endif

const float PRECISION = 1e-1;

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

float get_distance_to_goal(std::vector<float> pt1, Manipulator *manipulator) {
    auto end_eff_pos = manipulator->get_end_effector_pos();
    Vector *vec = new Vector(end_eff_pos, pt1);
    return vec->get_length();
}

std::vector<unsigned char> convert_to_bytes(std::vector<float> *data_vector) {
    unsigned char const *p;
    auto p_res = std::vector<unsigned char>();
    for (auto data: *data_vector) {
        p = reinterpret_cast<unsigned char const *>(&data);
        for (std::size_t ii = 0; ii != sizeof(float); ++ii) {
            p_res.push_back(p[ii]);
        }
    }

    return p_res;
}

std::vector<float> convert_to_floats(std::vector<unsigned char> &data) {
    auto res = vector<float>();
    for (int i = 0; i < data.size() / sizeof(float); i++) {
        auto tmp = std::vector<unsigned char>();
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


void handle_data(std::vector<float> &input_data, Manipulator *manipulator) {
    if (input_data.size() != 4) {
        throw std::invalid_argument("Data should has 4 elements inside");
    }

    auto needed_pos = std::vector<float>{input_data[0], input_data[1], input_data[2]};
    auto current_pos = manipulator->get_end_effector_pos();

    // Try to find optimal angle
    bool was_optimization;
    float delta_angle;
    float prev_dist;
    float prev_angle;
    float improvement_plus;
    float improvement_minus;
    while (get_distance_to_goal(needed_pos, manipulator) > PRECISION) {
        was_optimization = false;
        for (auto i = static_cast<int>(manipulator->get_links()->size() - 1); i > 0; i--) {
            vector<Link> links = *(manipulator->get_links());
            auto joint = links[i].get_joint();

            delta_angle = M_PI;

            log("Start optimization");
            while (abs(delta_angle) > M_PI / 2048) {
                prev_dist = get_distance_to_goal(needed_pos, manipulator);
                prev_angle = joint->get_angle();
                log("Now we use joint " + joint->get_name() + " with angle " + std::to_string(joint->get_angle())
                    + ". The manipulator has distance " + std::to_string(get_distance_to_goal(needed_pos, manipulator))
                    + ". The delta angle is " + std::to_string(delta_angle));
                joint->turn_on_the_angle(delta_angle);
                improvement_plus = prev_dist - get_distance_to_goal(needed_pos, manipulator);
                joint->set_angle(prev_angle);
                delta_angle = -delta_angle;


                joint->turn_on_the_angle(delta_angle);
                improvement_minus = prev_dist - get_distance_to_goal(needed_pos, manipulator);
                joint->set_angle(prev_angle);
                delta_angle = -delta_angle;

                if (improvement_plus <= PRECISION && improvement_minus <= PRECISION) {
                    delta_angle = delta_angle / 2;
                } else {
                    delta_angle = improvement_plus > improvement_minus ? delta_angle : -delta_angle;
                    joint->turn_on_the_angle(delta_angle);
                    was_optimization = true;
                    auto end_eff_pos = manipulator->get_end_effector_pos();
                }
            }
        }
        // Use mutations in local minimum case
        if (not was_optimization) {
            log("Use mutation for all joints");
            auto links = *(manipulator->get_links());
            for (int i = 1; i < links.size() - 1; i++) {
                auto joint = links[i].get_joint();
                joint->set_random_angle();
            }
        }
    }

    // Send calculated angles
    auto angles_for_conn = convert_to_bytes(manipulator->get_all_angles());
    manipulator->get_connection()->send(angles_for_conn);

    // Update by real angles
    auto byte_angles = *(new vector<unsigned char>());
    manipulator->get_connection()->receive(byte_angles);
    auto angles = convert_to_floats(byte_angles);
    manipulator->update_angles(angles);
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
    auto joints = std::vector<RevoluteJoint>{RevoluteJoint("Joint0", 0, 0, 0),
                                             RevoluteJoint("Joint1", 0, -M_PI, M_PI),
                                             RevoluteJoint("Joint2", 0, -M_PI / 2, M_PI / 2),
                                             RevoluteJoint("Joint3", 0, -M_PI, M_PI)
    };

    auto links = std::vector<Link>{Link("Link0", 0, 0, 0, &joints[0]),
                                   Link("Link1", M_PI / 2, 10, 0, &joints[1]),
                                   Link("Link2", 0, 5, 0, &joints[2]),
                                   Link("Link3", 0, 5, 0, &joints[3])};

    auto connection = new Connection();
    auto manipulator = new Manipulator(&links, connection);

    // Working with input file
    std::ifstream myfile;
    std::string line;

    myfile.open("/home/somal/Documents/2ndtest_mastersscholarshipinrobotics_sokolovmaxim/input.in");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            auto vector_float = parse_line(line);
            handle_data(vector_float, manipulator);
        }
    } else log("Unable to open file");

    myfile.close();
    return 0;
}

