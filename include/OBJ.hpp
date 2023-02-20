#ifndef OBJMODEL_H
#define OBJMODEL_H
#include <iostream>
#include <vector>

struct Triangle {
    unsigned int v1, v2, v3;
    float nx, ny, nz, cx, cy, cz, a;
};

struct Vertex {
    float x, y, z;

    // Tests if two VertexData are equal
	bool operator== (const Vertex &rhs){
		if( (x == rhs.x) && (y == rhs.y) && (z == rhs.z)){
			return true;
		}
		return false;
	}

    bool operator> (const Vertex &rhs) {
        if (x != rhs.x) {
            return (rhs.x > x);
        } else if (y != rhs.y) {
            return (rhs.y > y);
        } else {
            return rhs.z > z;
        }
    }

    bool operator< (const Vertex &rhs) {
        if (x != rhs.x) {
            return (rhs.x < x);
        } else if (y != rhs.y) {
            return (rhs.y < y);
        } else {
            return rhs.z < z;
        }
    }
};

class OBJ {
    public:
    OBJ(std::string filepath);

    ~OBJ();

    inline std::vector<Triangle> getTriangleList() const { return m_TriangleList; };

    inline std::vector<Vertex> getVertexList() const { return m_VertexList; };

    // Removes a vertex from the object model.
    void removeVertex();

    private:
    // Finds indices of triangles containing vertex.
    std::vector<int> getTriangles(int vidx);

    // Removes specific vertex from object model.
    void removeVertex(int i);

    std::vector<Triangle> m_TriangleList;
    std::vector<Vertex> m_VertexList;
    std::vector<Vertex> m_VertexNormalList;
    std::vector<std::vector<float>> m_Graph;

};

#endif