//
// Created by somal on 10.01.19.
//

#include "Vector.h"


Vector *Vector::float_multiplication(Vector *vector, float f) {
    return new Vector(vector->x * f, vector->y * f, vector->z * f);
}

float Vector::cross_product(Vector *vector1, Vector *vector2) {
    return vector1->x * vector2->x +
           vector1->y * vector2->y +
           vector1->z * vector2->z;
}

Vector::Vector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
