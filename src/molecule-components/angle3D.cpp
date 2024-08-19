#include <iostream>
#include <cmath>
#include "bond3D.cpp"

struct angle3D
{
    bond3D bond1 {};
    bond3D bond2 {};

    double dotProduct {
        (bond1.x*bond2.x)+
        (bond1.y*bond2.y)+
        (bond1.z*bond2.z)
    };

    double angle {
        std::acos(dotProduct/(bond1.length * bond2.length)) * (180/3.141592)
    };
};
