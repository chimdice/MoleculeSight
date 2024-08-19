#include <iostream>
#include <cmath>

struct bond3D
{
    double x {};
    double y {};
    double z {};
    double length={sqrt(pow(x,2)+pow(y,2)+pow(z,2))};
};

