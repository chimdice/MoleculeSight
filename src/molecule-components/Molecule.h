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
#include "../utility/MatrixTransform.cpp"


class Molecule
{
    private:
        std::vector<Atom> atoms {};
        std::map<std::string, Atom> atomName {};
        std::vector<Matrix4> atomTransformations {};

        std::map<int,std::vector<int>> bondInfo {};
        std::map<int,std::vector<bond3D>> bondNetwork {};

        int mass {};

        std::vector<std::vector<float>> atomsVertexData {};
        std::vector<std::vector<int>> atomsVertexIndex {};
        std::vector<float> atomsVertexSize {};
        std::vector<float> atomsIndexSize {};

    
    public:
        Molecule (std::vector<Atom> &atomList);
        void printMass ();
        void isBonded (int pos1, int pos2);
        void bondLength(int pos1, int pos2);
        void bondAngle(int pos1, int pos2, int pos3);
        void torsionAngle(int pos1, int pos2, int pos3, int pos4);


        // std::string getSequence ()
        // {
        //     return sequence;
        // }

        int getMass ()
        {
            return mass;
        }

        std::vector<std::vector<float>> fillAtomsVertexData ()
        {
            std::vector<std::vector<float>> vector {};
            for (std::vector<float>& data: atomsVertexData){
                vector.push_back(data);
            }
            return vector;
        }

        std::vector<std::vector<int>> fillAtomsIndexData ()
        {
            std::vector<std::vector<int>> vector {};
            for (std::vector<int>& data: atomsVertexIndex){
                vector.push_back(data);
            }
            return vector;
        }

        void fillAtomsVertexSize (std::vector<float> vector)
        {
            for (float& data: atomsVertexSize){
                vector.push_back(data);
            }
        }

        void fillAtomsIndexSize (std::vector<float> vector)
        {
            for (float& data: atomsIndexSize){
                vector.push_back(data);
            }
        }

        
};

#endif
