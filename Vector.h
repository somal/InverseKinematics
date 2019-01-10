#ifndef INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_VECTOR_H
#define INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_VECTOR_H

#include <vector>

using namespace std;

class Vector {
private:
    float x;
    float y;
    float z;
public:
    Vector(float x, float y, float z);

    Vector(std::vector<float> pt_start, std::vector<float> pt_end);

    ~Vector() = default;

    float get_length();

    static float scalar_product(Vector *vector1, Vector *vector2);

    static Vector *cross_product(Vector *vector1, Vector *vector2);

    static Vector *float_multiplication(Vector *vector, float f);
};


#endif //INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_VECTOR_H
