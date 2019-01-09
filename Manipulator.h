//
// Created by somal on 08.01.19.
//

#ifndef INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_MANIPULATOR_H
#define INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_MANIPULATOR_H

#include <vector>
#include "Link.h"
#include "Connection.h"

class Manipulator {
private:
    vector<Link> *links;
    Connection *connection;

public:
    Manipulator(vector<Link> *links, Connection *connection);

    ~Manipulator() = default;

    vector<float> get_end_effector_pos();
};


#endif //INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_MANIPULATOR_H
