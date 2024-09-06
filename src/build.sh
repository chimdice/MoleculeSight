CC=g++
CPPFLAGS="-I../Include"
LDFLAGS=`pkg-config --libs glew`
LDFLAGS="$LDFLAGS -lglut"

$CC graphics.cpp ./utility/Camera.cpp ./utility/MatrixTransform.cpp  ./shapes/Sphere.cpp ./shapes/Mesh.cpp ./molecule-components/Molecule.cpp ./molecule-components/Atom.cpp $CPPFLAGS $LDFLAGS -o main

./main