#include <iostream>
#include <cmath>
//#include "bond3D.cpp"
#include "angle3D.cpp"

struct torsion3D
{
    bond3D bond1 {};
    bond3D bond2 {};
    bond3D bond3 {};

    //angle3D angle1 {bond1, bond2};
    //angle3D angle2 {bond2, bond3};

    bond3D orthBond1 {
        ((bond1.y*bond2.z) - (bond1.z*bond2.y)),
        -((bond1.x*bond2.z) - (bond1.z*bond2.x)),
        ((bond1.x*bond2.y) - (bond1.y*bond2.x))
        };
    
    bond3D orthBond2 {
        ((bond2.y*bond3.z) - (bond2.z*bond3.y)),
        -((bond2.x*bond3.z) - (bond2.z*bond3.x)),
        ((bond2.x*bond3.y) - (bond2.y*bond3.x))
        };
    
    angle3D orthAngle {orthBond1, orthBond2};

    double radToAng {3.141592/180};
    double torsion {
        std::acos(orthAngle.dotProduct/(orthBond1.length * orthBond2.length)) * (180/3.141592)
    };
};
