#ifndef INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_LINK_H
#define INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_LINK_H

#include "Joint.h"

class Link {
private:
    float twist;
    float length;
    float offset;
    RevoluteJoint *joint;
    string name;

public:
    Link(string name, float twist, float length, float offset, RevoluteJoint *joint);

    ~Link() = default;

    vector<vector<float>> get_displacement_matrix(bool print);

};


#endif //INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_LINK_H
