#ifndef ATOM_H
#define ATOM_H

#include <iostream>

class Atom
{
    private:
        int numProtons {};
        int numElectrons {};
        int mass {};
        int maxNumBonds {};

        double atomicRadius {};
        double xPosition {};
        double yPosition {};
        double zPosition {};
    
    public:
        Atom (int protons, int electrons, int maxNumBonds, double radius, double mass, double x, double y, double z);

        void printCoordinates ();
        void printParticles ();
        void printMass ();


        int getProtons ()
        {
            return numProtons;
        }
        int getElectrons ()
        {
            return numElectrons;
        }
       int getMaxNumBonds ()
       {
         return maxNumBonds;
       }
        double getRadius ()
        {
            return atomicRadius;
        }
        double getXPosition ()
        {
            return xPosition;
        }
        double getYPosition ()
        {
            return yPosition;
        }
        double getZPosition ()
        {
            return zPosition;
        }
        int getMass ()
        {
            return mass;
        }

};

#endif