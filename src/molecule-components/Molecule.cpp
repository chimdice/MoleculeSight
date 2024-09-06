#include "Molecule.h"

Molecule::Molecule (std::vector<Atom> &atomList)
{
    //atoms
    this->atoms = atomList;

    //mass
    int tempMass = {0};
    for (Atom atom: atomList)
    {
        tempMass += atom.getMass();
    }
    this->mass = tempMass;

    //bonds
    unsigned long numAtoms {atomList.size()};
    std::map<int, std::vector<int>> tempBondInfo {};
    std::map<int, std::vector<bond3D>> tempBondNetwork {};
    for (int i = 0; i < numAtoms; i++)
    {
        std::vector<bond3D> vector1 {};
        std::vector<int> vector2 {};

        //create sphere transformation
        Matrix4 atomModel {1.0f};
        Vector3f atomTranslate {atoms[i].getXPosition(),atoms[i].getYPosition(), atoms[i].getZPosition()};
        Vector3f atomScale {atoms[i].getRadius()};
        MatrixTransform modelTransfrom {atomModel};
        modelTransfrom.translate(atomTranslate);
        modelTransfrom.scale(atomScale);
        Matrix4 atomModelFinal = modelTransfrom.getMatrix();
        atomTransformations.push_back(atomModelFinal);
        sphere.addNumInstances();

        for (int j = 0; j < numAtoms; j++)
        {
            double xDiff {atoms[i].getXPosition() - atoms[j].getXPosition()};
            double yDiff {atoms[i].getYPosition() - atoms[j].getYPosition()};
            double zDiff {atoms[i].getZPosition() - atoms[j].getZPosition()};
            double nucelusDiff {atoms[i].getRadius() + atoms[j].getRadius()};
            double bondLength {sqrt(pow(xDiff,2)+pow(yDiff,2)+pow(zDiff,2))};

            if ((bondLength <= 1.2*nucelusDiff)&&(bondLength > 0))
            {
                bond3D bondVector {xDiff, yDiff, zDiff};
                vector1.push_back(bondVector);
                vector2.push_back(j);
            }
        }

        tempBondNetwork[i] = vector1;
        tempBondInfo[i] = vector2;
    }
    this->bondInfo = tempBondInfo;
    this->bondNetwork = tempBondNetwork;
};

void Molecule::printMass ()
{
    std::cout<< mass << " a.u. \n";
};

void Molecule::isBonded (int pos1, int pos2)
{
    std::vector<int> tempVector {bondInfo[pos1]};
    std::binary_search(tempVector.begin(),tempVector.end(), pos2) ?
    std::cout << "bond exsists \n":
    std::cout << "no bond exsists \n";
}

void Molecule::bondLength(int pos1, int pos2)
{
    std::vector<int> tempVector {bondInfo[pos1]};
    auto it = std::find(tempVector.begin(),tempVector.end(), pos2);
    if (it != tempVector.end()) {
        int idx {std::distance(tempVector.begin(), it)};
        bond3D bond {bondNetwork[pos1][idx]};
        std::cout<< "bond length is " << bond.length << '\n';
    } else {
        std::cout << "no bond exsists \n";
    }
}

void Molecule::bondAngle(int pos1, int pos2, int pos3)
{
    std::vector<int> tempVector {bondInfo[pos2]};
    auto it1 = std::find(tempVector.begin(),tempVector.end(), pos1);
    auto it2 = std::find(tempVector.begin(),tempVector.end(), pos3);

    bool isBond1 {it1 != tempVector.end()};
    bool isBond2 {it2 != tempVector.end()};

    if (isBond1 && isBond2) {
        int idx1 {std::distance(tempVector.begin(), it1)};
        int idx2 {std::distance(tempVector.begin(), it2)};

        bond3D bond1 {bondNetwork[pos2][idx1]};
        bond3D bond2 {bondNetwork[pos2][idx2]};

        angle3D angle {bond1, bond2};
        std::cout<< "angle between bonds is " << angle.angle << '\n';
    } else {
        std::cout<< "no angle exisits \n";
    }
}

void Molecule::torsionAngle(int pos1, int pos2, int pos3, int pos4)
{
    std::vector<int> tempVector1 {bondInfo[pos2]};
    std::vector<int> tempVector2 {bondInfo[pos3]};

    auto it1 = std::find(tempVector1.begin(),tempVector1.end(), pos1);
    auto it2 = std::find(tempVector1.begin(),tempVector1.end(), pos3);
    auto it3 = std::find(tempVector2.begin(),tempVector2.end(), pos4);

    bool isBond1 {it1 != tempVector1.end()};
    bool isBond2 {it2 != tempVector1.end()};
    bool isBond3 {it3 != tempVector2.end()};

    if (isBond1 && isBond2 && isBond3) {
        int idx1 {std::distance(tempVector1.begin(), it1)};
        int idx2 {std::distance(tempVector1.begin(), it2)};
        int idx3 {std::distance(tempVector2.begin(), it3)};


        bond3D bond1 {bondNetwork[pos2][idx1]};
        bond3D bond2 {bondNetwork[pos2][idx2]};
        bond3D bond3 {bondNetwork[pos3][idx3]};

        torsion3D torsion {bond1, bond2, bond3};
        std::cout<< "torsion angle between bonds is " << torsion.torsion <<'\n';
    } else {
        std::cout<< "no torsion angle exisits \n";
    }
}

void Molecule::render()
{
    // for(Matrix4& mat:atomTransformations) {
    //     sphere.addModelTransformation(mat);
    // }
    // sphere.fillModelVector();
    // sphere.draw();
    // sphere.prepareVbo();
    // sphere.render();

    cyl.addModelTransformation(cylModelTest);
    cyl.fillModelVector();
    cyl.draw();
    cyl.prepareVbo();
    cyl.render();
}