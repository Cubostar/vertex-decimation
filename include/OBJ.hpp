#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <Geometry.hpp>

#include <iostream>
#include <vector>

class OBJ {
    public:
    OBJ(std::string filepath);

    ~OBJ();

    // Removes a vertex from the object model.
    void removeVertex();

    private:
    // Finds indices of triangles containing vertex.
    std::vector<int> getTriangles(int vidx);

    // Removes specific vertex from object model.
    void removeVertex(int i);

    Geometry m_geometry;
};

#endif