#include <iostream>
#include "Joint.h"

using namespace std;

RevoluteJoint::RevoluteJoint(string joint_name, float init_angle, float min_limit, float max_limit) {
    this->name = joint_name;
    this->angle = init_angle;
    this->min_limit = min_limit;
    this->max_limit = max_limit;
}

void RevoluteJoint::set_angle(float angle) {
    if (this->min_limit <= angle && angle <= this->max_limit) {
        this->angle = angle;
    } else std::cout << "Joint " + this->name + " can't move on " << angle << std::endl;
}
