#ifndef INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_LINK_H
#define INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_LINK_H

#include "Joint.h"

class Link {
protected:
    float twist;
    float length;
    float offset;
    RevoluteJoint *joint;

public:
    Link(float twist, float length, float offset, RevoluteJoint *joint) {
        this->twist = twist;
        this->length = length;
        this->offset = offset;
        this->joint = joint;

    }

    ~Link() = default;

    virtual void get_DH_matrix()= 0;

};


#endif //INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_LINK_H
