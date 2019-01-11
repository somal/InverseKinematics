#include <cmath>
#include <iostream>
#include "vector"

#include "Link.h"

void print_matrix(vector<vector<float>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
}

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
        print_matrix(D);
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

RevoluteJoint *Link::get_joint() {
    return this->joint;
}
