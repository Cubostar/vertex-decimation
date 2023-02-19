/** @file Geometry.hpp
 *  @brief Organizes vertex and triangle information.
 *  
 *  More...
 *
 *  @author Mike
 *  @bug No known bugs.
 */

#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>

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

struct Triangle {
    unsigned int i1, i2, i3;
};

// Purpose of this class is to store vertice and triangle information
class Geometry{
public:
	// Constructor
	Geometry();
	// Destructor
	~Geometry();
	
	// Functions for working with individual vertices
	unsigned int GetBufferSizeInBytes();
    // Retrieve the Buffer Data Size
	unsigned int GetBufferDataSize();
	// Retrieve the Buffer Data Pointer
	float* GetBufferDataPtr();
	// Adds a vertex and associated texture coordinate.
	void AddVertex(float x, float y, float z, float s, float t);
	// Allows for adding one index at a time manually if 
	// you know which vertices are needed to make a triangle.
	void AddIndex(unsigned int i);
    // Gen pushes all attributes into a single vector
	void Gen();
	// Functions for working with Indices
	// Creates a triangle from 3 indices
	// When a triangle is made, the tangents and bi-tangents are also
	// computed
	void MakeTriangle(unsigned int vert0, unsigned int vert1, unsigned int vert2);  
    // Retrieve how many indices there are
	unsigned int GetIndicesSize();
	// Retrive how many vertices there are
	unsigned int GetVerticesSize();
    // Retrieve the pointer to the indices
	unsigned int* GetIndicesDataPtr();

private:
	// m_bufferData stores all of the vertexPositons, coordinates, normals, etc.
	// This is all of the information that should be sent to the vertex Buffer Object
	std::vector<float> m_bufferData;

    // Individual components of 
	std::vector<float> m_vertexPositions;
	std::vector<float> m_textureCoords;
	std::vector<float> m_normals;
	std::vector<float> m_tangents;
	std::vector<float> m_biTangents;

	// The indices for a indexed-triangle mesh
	std::vector<unsigned int> m_indices;
};





#endif
