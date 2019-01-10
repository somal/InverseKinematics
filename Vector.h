#ifndef INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_VECTOR_H
#define INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_VECTOR_H


class Vector {
private:
    float x;
    float y;
    float z;
public:
    Vector(float x, float y, float z);

    ~Vector() = default;

    float get_length();

    static float scalar_product(Vector *vector1, Vector *vector2);

    static Vector *vector_product(Vector *vector1, Vector *vector2);

    static Vector *float_multiplication(Vector *vector, float f);
};


#endif //INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_VECTOR_H
