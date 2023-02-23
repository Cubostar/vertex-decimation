#include "Geometry.hpp"
#include <assert.h>
#include <iostream>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/glm.hpp"

// Constructor
Geometry::Geometry(){

}

// Destructor
Geometry::~Geometry(){

}


// Adds a vertex.
// Will also add a and a normal
void Geometry::AddVertex(float x, float y, float z){
	// Add vertex to vertex list
	m_vertices.push_back(ThreeVec(x, y, z));
	
	// Add empty list of triangle indices to list of indices of triangles with shared vertex
	m_sharedTriangles.push_back(std::vector<unsigned int>());
}

// Retrieves a pointer to our data.
float* Geometry::GetBufferDataPtr(){
	return m_bufferData.data();
}

// Retrieves the size of our data 
unsigned int Geometry::GetBufferDataSize(){
	return m_bufferData.size();
}

// Retrieves the number of bytes of our data
unsigned int Geometry::GetBufferSizeInBytes(){
	return m_bufferData.size()*sizeof(float);
}

// Generate data to send to vertex buffer object
void Geometry::Gen(){
	for(int i = 0; i < m_vertices.size(); ++i) {
		m_bufferData.push_back(m_vertices[i].x);
		m_bufferData.push_back(m_vertices[i].y);
		m_bufferData.push_back(m_vertices[i].z);
	}
}

// Creates a triangle from three indices
void Geometry::MakeTriangle(unsigned int vert0, unsigned int vert1, unsigned int vert2) {
	// Add triangle to list of triangles
	m_triangles.push_back(Triangle(m_vertices[vert0], m_vertices[vert1], m_vertices[vert2], vert0, vert1, vert2));

	// Update list of triangles sharing vertex
	m_sharedTriangles[vert0].push_back(m_triangles.size()+1);
	m_sharedTriangles[vert1].push_back(m_triangles.size()+1);
	m_sharedTriangles[vert2].push_back(m_triangles.size()+1);
}

// Retrieves the number of indices that we have.
unsigned int Geometry::GetIndicesSize(){
	return m_triangles.size() * 3;
}

// Removes a vertex and retriangulates hole (Schroeder et al 1992)
void RemoveVertex() {

}

// Retrieves the number of vertices that we have.
unsigned int Geometry::GetVerticesSize() {
	return m_vertices.size();
}

// Retrieves a pointer to the indices that we have
unsigned int* Geometry::GetIndicesDataPtr(){
	std::vector<unsigned int> indices;
	for (int i = 0; i < m_triangles.size(); ++i) {
		indices.push_back(m_triangles[i].i1);
		indices.push_back(m_triangles[i].i2);
		indices.push_back(m_triangles[i].i3);
	}
	return indices.data();
}
