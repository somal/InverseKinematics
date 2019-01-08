//
// Created by somal on 08.01.19.
//

#include "Connection.h"
#include "iostream"

using namespace std;

template<std::size_t N>
int mult(float A[N][N], float B[N][N]) {
    static_assert(N > 1, "N must be greater than 1");

    float C[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int num = 0;
            for (int k = 0; k < N; k++) {
                num += A[i][k] * B[k][j];
            }
            C[i][j] = num;
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

int Connection::open() {}

int Connection::close() {}

int Connection::send(std::vector<unsigned char> &data) {
    if (data.size() != 12) {
        throw std::invalid_argument("Data should defined by 12 bytes");
    }
    this->data = data;
}

int Connection::receive(std::vector<unsigned char> &data) {
    data = this->data;
}


