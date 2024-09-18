#ifndef MOLELIST
#define MOLELIST

#include "Molecule.h"

class MoleculeList
{
    private:
        std::vector<Molecule> allMolecules {};
        std::vector<bool> renderMolecule {};

    public:
        MoleculeList();
        void addMolecule(Molecule mol);
        void renderMolecules();
        void addAtomtoMolecule(int molPos, Atom atom);
};


#endif