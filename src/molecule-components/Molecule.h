#ifndef MOLECULE_H
#define MOLECULE_H

#include <iostream>
#include <vector>
#include <map>
#include "Atom.h"
//#include "bond3D.cpp"
//#include "angle3D.cpp"
#include "torsion3D.cpp"
#include "../shapes/Sphere.h"
#include "../shapes/Sphere.cpp"


class Molecule
{
    private:
        std::vector<Atom> atoms {};
        std::map<std::string, Atom> atomName {};

        std::map<int,std::vector<int>> bondInfo {};
        std::map<int,std::vector<bond3D>> bondNetwork {};

        int mass {};

        std::vector<float> sphereVertex {};
        std::vector<int> sphereVertexIndex {};
        std::vector<float> sphereColor {};

    
    public:
        Molecule (std::vector<Atom> &atomList);
        void printMass ();
        void isBonded (int pos1, int pos2);
        void bondLength(int pos1, int pos2);
        void bondAngle(int pos1, int pos2, int pos3);
        void torsionAngle(int pos1, int pos2, int pos3, int pos4);
        void renderMolecule();


        // std::string getSequence ()
        // {
        //     return sequence;
        // }

        int getMass ()
        {
            return mass;
        }

};

#endif
