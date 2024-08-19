#include <iostream>
#include <vector>
#include "Atom.h"
#include "Molecule.h"
#include "Molecule.cpp"


int main ()
{
    //Hydrogen Atom
    Atom h1(1, 1, 1, .37, 1, 0, 0, 0);
    Atom h2(1, 1, 1, .37, 1, 0.7, 0, 0);
    Atom h3(1, 1, 1, .37, 1, 0.7, 0.7, 0);
    Atom h4(1, 1, 1, .37, 1, 0.7, 0.7, 0.7);


    //H2 molecule
    std::vector<Atom> H2Atoms {h1, h2, h3, h4};
    Molecule H2 (H2Atoms);
    H2.printMass();
    H2.bondLength(0,2);
    H2.bondLength(0,1);
    H2.bondLength(1,2);
    H2.bondAngle(0, 1, 2);
    H2.torsionAngle(0, 1, 2, 3);
    return 0;
}
