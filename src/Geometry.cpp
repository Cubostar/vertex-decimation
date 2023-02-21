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
	m_vertices.push_back(ThreeVec(x, y, z));
	// Push back placeholders for m_normals
	m_normals.push_back(ThreeVec());
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

// Create all data
// The idea here is that we are pshing all of our data from
// each individual vertex into a single vector.
// This makes it relatively easy to then fill in a buffer
// with the corresponding vertices
void Geometry::Gen(){
	for(int i =0; i < m_vertices.size()/3; ++i){
	// First vertex
		// vertices
		m_bufferData.push_back(m_vertices[i*3+ 0]);
		m_bufferData.push_back(m_vertices[i*3+ 1]);
		m_bufferData.push_back(m_vertices[i*3+ 2]);
		// m_normals
		m_bufferData.push_back(m_normals[i*3+0]);
		m_bufferData.push_back(m_normals[i*3+1]);
		m_bufferData.push_back(m_normals[i*3+2]);
	}
}

// The big trick here, is that when we make a triangle
// We also need to update our m_normals, tangents, and bi-tangents.
void Geometry::MakeTriangle(unsigned int vert0, unsigned int vert1, unsigned int vert2){
	m_triangles.push_back(Triangle(m_vertices[vert0], m_vertices[vert1], m_vertices[vert2], vert0, vert1, vert2));

	/*
	// Look up the actual vertex positions
	glm::vec3 pos0(m_vertices[vert0*3 +0], m_vertices[vert0*3 + 1], m_vertices[vert0*3 + 2]); 
	glm::vec3 pos1(m_vertices[vert1*3 +0], m_vertices[vert1*3 + 1], m_vertices[vert1*3 + 2]); 
	glm::vec3 pos2(m_vertices[vert2*3 +0], m_vertices[vert2*3 + 1], m_vertices[vert2*3 + 2]); 

	// Now create an edge
	// With two edges
	// This section is inspired by: https://learnopengl.com/Advanced-Lighting/Normal-Mapping
	glm::vec3 edge0 = pos1 - pos0;
	glm::vec3 edge1 = pos2 - pos0;
	
	// Compute a normal
	// For now we sort of 'cheat' since this is a quad the 'z' axis points straight out
	// TODO: Change this
    glm::vec3 normal1{m_normals[vert0*3+0] ,m_normals[vert0*3+1], m_normals[vert0*3+2]};
    glm::vec3 normal2{m_normals[vert1*3+0] ,m_normals[vert1*3+1], m_normals[vert1*3+2]};
    glm::vec3 normal3{m_normals[vert2*3+0] ,m_normals[vert2*3+1], m_normals[vert2*3+2]};


	m_normals[vert0*3+0] = 0.0f;	m_normals[vert0*3+1] = 0.0f;	m_normals[vert0*3+2] = 1.0f;	
	m_normals[vert1*3+0] = 0.0f;	m_normals[vert1*3+1] = 0.0f;	m_normals[vert1*3+2] = 1.0f;	
	m_normals[vert2*3+0] = 0.0f;	m_normals[vert2*3+1] = 0.0f;	m_normals[vert2*3+2] = 1.0f;	
	*/
}

// Retrieves the number of indices that we have.
unsigned int Geometry::GetIndicesSize(){
	return m_triangles.size();
}

// Retrieves the number of vertices that we have.
unsigned int Geometry::GetVerticesSize() {
	return m_vertices.size();
}

// Retrieves a pointer to the indices that we have
unsigned int* Geometry::GetIndicesDataPtr(){
	return m_triangles.data();
}
