//
// Created by somal on 10.01.19.
//

#include <cmath>
#include <vector>
#include <cassert>

#include "Vector.h"

using namespace std;

Vector *Vector::float_multiplication(Vector *vector, float f) {
    return new Vector(vector->x * f, vector->y * f, vector->z * f);
}

float Vector::scalar_product(Vector *vector1, Vector *vector2) {
    return vector1->x * vector2->x +
           vector1->y * vector2->y +
           vector1->z * vector2->z;
}

Vector::Vector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vector::get_length() {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector *Vector::cross_product(Vector *vector1, Vector *vector2) {
    return new Vector((vector1->y * vector2->z - vector1->z * vector2->y),
                      (vector1->x * vector2->z - vector1->z * vector2->x),
                      (vector1->x * vector2->y - vector1->x * vector2->y));
}

Vector::Vector(std::vector<float> pt_start, std::vector<float> pt_end) {
    assert(pt_start.size() == 3);
    assert(pt_end.size() == 3);

    this->x = pt_end[0] - pt_start[0];
    this->y = pt_end[1] - pt_start[1];
    this->z = pt_end[2] - pt_start[2];
}


