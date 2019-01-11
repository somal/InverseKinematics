#include <iostream>
#include <random>
#include "Joint.h"

using namespace std;

RevoluteJoint::RevoluteJoint(string joint_name, float init_angle, float min_limit, float max_limit) {
    this->name = joint_name;
    this->min_limit = min_limit;
    this->max_limit = max_limit;
    this->set_angle(init_angle);
}

void RevoluteJoint::set_angle(float angle) {
    if (this->min_limit <= angle && angle <= this->max_limit) {
        this->angle = angle;
    }
//    else std::cout << "Joint " + this->get_name() + " can't move on " << angle << std::endl;
}

float RevoluteJoint::get_angle() {
    return angle;
}

void RevoluteJoint::turn_on_the_angle(float angle) {
    this->set_angle(this->angle + angle);
}

string RevoluteJoint::get_name() {
    return this->name;
}

void RevoluteJoint::set_random_angle() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(this->min_limit, this->max_limit);
    this->set_angle(dist(mt));
}
