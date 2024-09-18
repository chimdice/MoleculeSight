CC=g++
CPPFLAGS="-I../Include"
LDFLAGS=`pkg-config --libs glew`
LDFLAGS="$LDFLAGS -lglut"

$CC graphics.cpp ./utility/Camera.cpp ./utility/MatrixTransform.cpp  ./shapes/Sphere.cpp ./shapes/Cylinder.cpp ./shapes/Mesh.cpp ./molecule-components/Molecule.cpp ./molecule-components/MoleculeList.cpp ./molecule-components/Atom.cpp ./imgui/imgui.cpp ./imgui/imgui_tables.cpp ./imgui/imgui_widgets.cpp  ./imgui/imgui_draw.cpp ./imgui/imgui_impl_glut.cpp ./imgui/imgui_impl_opengl3.cpp $CPPFLAGS $LDFLAGS -o main

./main