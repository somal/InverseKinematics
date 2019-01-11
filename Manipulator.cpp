#include <iostream>
#include "Manipulator.h"

Manipulator::Manipulator(vector<Link> *links, Connection *connection) {
    this->links = links;
    this->connection = connection;
}

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

vector<float> Manipulator::get_link_pos(int index) {
    auto links = *(this->links);
    vector<vector<float>> common_displacement_matrix = links[0].get_displacement_matrix(false);
    for (int i = 1; i <= index; i++) {
        vector<vector<float>> matrix = links[i].get_displacement_matrix(false);
        common_displacement_matrix = matrix_multiplication(common_displacement_matrix,
                                                           links[i].get_displacement_matrix(false));
    }


    auto res = vector<float>{common_displacement_matrix[0][3],
                             common_displacement_matrix[1][3],
                             common_displacement_matrix[2][3]};
    return res;
}


vector<float> Manipulator::get_end_effector_pos() {
    return this->get_link_pos(static_cast<int>(this->links->size() - 1));
}

vector<Link> *Manipulator::get_links() {
    return this->links;
}

Connection *Manipulator::get_connection() {
    return this->connection;
}

vector<float> *Manipulator::get_all_angles() {
    auto res = new vector<float>();
    auto links = *(this->get_links());
    for (int i = 1; i < this->links->size(); i++) {
        auto joint = links[i].get_joint();
        res->push_back(joint->get_angle());
    }
    return res;
}

void Manipulator::update_angles(vector<float> angles) {
    auto links = *(this->get_links());
    for (int i = 1; i < this->links->size(); i++) {
        auto joint = links[i].get_joint();
        joint->set_angle(angles[i - 1]);
    }
}

