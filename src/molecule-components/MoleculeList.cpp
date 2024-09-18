#include "MoleculeList.h"

MoleculeList::MoleculeList()
{

}

void MoleculeList::addMolecule(Molecule mol)
{
    allMolecules.push_back(mol);
    renderMolecule.push_back(true);
}

 void MoleculeList::renderMolecules()
 {
    for (int i = 0; i < allMolecules.size(); i++)
    {
        if (renderMolecule[i]) {
            allMolecules[i].render();
        }
    }
 }

 void MoleculeList::addAtomtoMolecule(int molPos, Atom atom)
 {
    if (molPos < allMolecules.size()) {
        allMolecules[molPos].AddAtom(atom);
    }
 }