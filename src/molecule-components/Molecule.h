#ifndef MOLECULE_H
#define MOLECULE_H

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include "Atom.h"
//#include "bond3D.cpp"
//#include "angle3D.cpp"
#include "torsion3D.cpp"
#include "../shapes/Sphere.h"
#include "../shapes/Cylinder.h"
#include "../utility/MatrixTransform.h"
#include "../Math3d.h"

class Molecule
{
    private:
        std::vector<Atom> atoms {};
        std::map<std::string, Atom> atomName {};
        std::vector<Matrix4> atomTransformations {};
        std::vector<Matrix4> bondTransformations {};

        std::map<int,std::vector<int>> bondInfo {};
        std::map<int,std::vector<bond3D>> bondNetwork {};

        int mass {};

        std::vector<std::vector<float>> atomsVertexData {};
        std::vector<std::vector<int>> atomsVertexIndex {};
        std::vector<float> atomsVertexSize {};
        std::vector<float> atomsIndexSize {};

        Sphere sphere {1.0f, 20, 20, 0};
        Cylinder cyl {1.0f, 1.0f, 10, 0};
        Matrix4 cylModelTest {1.0f};

    
    public:
        Molecule (std::vector<Atom> &atomList);
        void printMass ();
        void isBonded (int pos1, int pos2);
        void bondLength(int pos1, int pos2);
        void bondAngle(int pos1, int pos2, int pos3);
        void torsionAngle(int pos1, int pos2, int pos3, int pos4);
        void render();

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
