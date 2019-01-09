//
// Created by somal on 08.01.19.
//

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

vector<float> Manipulator::get_end_effector_pos() {
    auto links = *(this->links);
    vector<vector<float>> common_displacement_matrix = links[0].get_displacement_matrix(false);
    for (int i = 1; i < links.size(); i++) {
        vector<vector<float>> matrix = links[i].get_displacement_matrix(false);
        common_displacement_matrix = matrix_multiplication(common_displacement_matrix,
                                                           links[i].get_displacement_matrix(false));
    }


    auto res = vector<float>{common_displacement_matrix[0][3],
                             common_displacement_matrix[1][3],
                             common_displacement_matrix[2][3]};
    return res;
}