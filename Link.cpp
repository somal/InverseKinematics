//
// Created by somal on 08.01.19.
//

#include "Link.h"

int Link::get_DH_matrix() {
    return 0;
}

Link::Link(string name, float twist, float length, float offset, RevoluteJoint *joint) {
    this->twist = twist;
    this->length = length;
    this->offset = offset;
    this->joint = joint;
    this->name = name;
}
