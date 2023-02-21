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
#include "glm/glm/gtx/transform.hpp"

struct Triangle {
	ThreeVec v1, v2, v3;
	unsigned int i1, i2, i3;

	ThreeVec normal;
	ThreeVec centroid;
	float area;

	Triangle(ThreeVec v1, ThreeVec v2, ThreeVec v3, unsigned int i1, unsigned int i2, unsigned int i3) {
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
		this->i1 = i1;
		this->i2 = i2;
		this->i3 = i3;

		// Compute normal (not normalized)
		glm::vec3 u = v2.toGLM() - v1.toGLM();
		glm::vec3 v = v3.toGLM() - v1.toGLM();


		// Compute centroid

		// Compute area
	}
};

struct ThreeVec {
    float x, y, z;

	ThreeVec() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	ThreeVec(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	glm::vec3 toGLM() {
		return glm::vec3(x, y, z);
	}

    // Comparing ThreeVecs 
	// (why we have ThreeVecs instead of Vec3s)
	bool operator== (const ThreeVec &rhs){
		if( (x == rhs.x) && (y == rhs.y) && (z == rhs.z)){
			return true;
		}
		return false;
	}

    bool operator> (const ThreeVec &rhs) {
        if (x != rhs.x) {
            return (rhs.x > x);
        } else if (y != rhs.y) {
            return (rhs.y > y);
        } else {
            return rhs.z > z;
        }
    }

    bool operator< (const ThreeVec &rhs) {
        if (x != rhs.x) {
            return (rhs.x < x);
        } else if (y != rhs.y) {
            return (rhs.y < y);
        } else {
            return rhs.z < z;
        }
    }
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
	// Add a new vertex 
	void AddVertex(float x, float y, float z);
    // Gen pushes all attributes into a single vector
	void Gen();
	// Functions for working with Indices
	// Creates a triangle from 3 indices
	void MakeTriangle(unsigned int vert0, unsigned int vert1, unsigned int vert2);  
    // Retrieve how many indices there are
	unsigned int GetIndicesSize();
	// Retrive how many vertices there are
	unsigned int GetVerticesSize();
    // Retrieve the pointer to the indices
	unsigned int* GetIndicesDataPtr();

private:
	// m_bufferData stores all of the vertexPositions, normals, etc.
	// This is all of the information that should be sent to the vertex Buffer Object
	std::vector<float> m_bufferData;

    // Individual components of 
	std::vector<ThreeVec> m_vertices;
	std::vector<ThreeVec> m_normals;

	// The indices for a indexed-triangle mesh
	std::vector<Triangle> m_triangles;
};





#endif
