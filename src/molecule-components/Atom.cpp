#include "Atom.h"

Atom::Atom (int protons, int electrons, int maxNumBonds, double radius, double mass, double x, double y, double z)
{
    this->numProtons = protons;
    this->numElectrons = electrons;
    this->maxNumBonds = maxNumBonds;
    this->atomicRadius = radius;
    this->xPosition = x;
    this->yPosition = y;
    this->zPosition = z;
    this->mass = mass;
}

void Atom::printCoordinates ()
{
    std::cout << "x position is " << xPosition <<" y position is " << yPosition <<", and z position is " << zPosition << ". \n";
};

void Atom::printParticles ()
{
    std::cout << numProtons <<" protons and " << numElectrons <<" electrons. \n";
};

void Atom::printMass ()
{
    std::cout << mass << " a.u. \n";
};