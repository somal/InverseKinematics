#include <cmath>
#include <iostream>
#include "vector"

#include "Link.h"

vector<vector<float>> Link::get_displacement_matrix(bool print = false) {
    auto D = vector<vector<float>>(4, vector<float>(4, 0));
    float angle = this->joint->get_angle();
    D[0] = vector<float>{cos(angle), -sin(angle) * cos(this->twist), sin(angle) * sin(this->twist),
                         this->length * cos(angle)};
    D[1] = vector<float>{sin(angle), cos(angle) * cos(this->twist), -cos(angle) * sin(this->twist),
                         this->length * sin(angle)};
    D[2] = vector<float>{0, sin(this->twist), cos(this->twist), this->offset};
    D[3] = vector<float>{0, 0, 0, 1};

    if (print) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                cout << D[i][j] << ' ';
            cout << endl;
        }
    }

    return D;
}

Link::Link(string name, float twist, float length, float offset, RevoluteJoint *joint) {
    this->twist = twist;
    this->length = length;
    this->offset = offset;
    this->joint = joint;
    this->name = name;
}
