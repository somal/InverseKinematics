#include <array>

using namespace std;

class RevoluteJoint {
private:
    float angle;
    float min_limit;
    float max_limit;
    string name;
public:
    RevoluteJoint(string name, float init_angle, float min_limit, float max_limit);

    ~RevoluteJoint() = default;

    float get_angle() { return angle; };

    void set_angle(float angle);

};
