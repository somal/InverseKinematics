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

    vector<float> get_link_pos(int index);

    vector<Link> *get_links();

    Connection *get_connection();

    vector<float> *get_all_angles();

    void update_angles(vector<float> angles);
};


#endif //INC_2NDTEST_MASTERSSCHOLARSHIPINROBOTICS_SOKOLOVMAXIM_MANIPULATOR_H
