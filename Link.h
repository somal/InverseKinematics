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

    int get_DH_matrix();

};


#endif //INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_LINK_H
