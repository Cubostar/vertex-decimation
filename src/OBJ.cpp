#include "OBJ.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

OBJ::OBJ() {
}

OBJ::OBJ(std::string fileName) {
    std::ifstream inOBJ;
    inOBJ.open(fileName);

    if (inOBJ.is_open()) {
        std::string line;

        while(getline(inOBJ, line)) {

            // Parse line containing vertex data
            if ((line.rfind("v", 0) == 0) && (line.rfind("vn", 0) == std::string::npos)) {
                std::stringstream stream(line);
                std::string token;
                bool x, y, z;
                x = false;
                y = false;
                z = false;
                Vertex v;

                while (stream >> token) {
                    if (token[0] == 'v') {
                        continue;
                    } else {
                        if (!x) {
                            v.x = std::stof(token);
                            x = true;
                        } else if (!y) {
                            v.y = std::stof(token);
                            y = true;
                        } else if (!z) {
                            v.z = std::stof(token);
                            z = true;
                        }
                    }
                }

                m_geometry.AddVertex(v.x, v.y, v.z, 0, 0);

            // Parse line containing triangle data
            } else if (line.rfind("f") == 0) {
                std::stringstream stream(line);
                std::string token;
                bool i1, i2, i3;
                i1 = false;
                i2 = false;
                i3 = false;
                Triangle t;

                while (stream >> token) {
                    if (token[0] == 'f') {
                        continue;
                    } else {
                        int pos = token.find('/');
                        if (!i1) {
                            t.i1 = std::stoi(token.substr(0, pos)) - 1;
                            i1 = true;
                        } else if (!i2) {
                            t.i2 = std::stoi(token.substr(0, pos)) - 1;
                            i2 = true;
                        } else if (!i3) {
                            t.i3 = std::stoi(token.substr(0, pos)) - 1;
                            i3 = true;
                        }
                    }
                }

                m_geometry.MakeTriangle(t.i1, t.i2, t.i3);
            } else {
                continue;
            }
        }
    }

    m_geometry.Gen();

    /*
    // Compute normal vectors, areas, and centroids of triangles
    for (int i = 0; i < m_TriangleList.size(); i++) {
        Triangle t = m_TriangleList.at(i);

        Vertex v1 = m_VertexList.at(t.v1);
        Vertex v2 = m_VertexList.at(t.v2);
        Vertex v3 = m_VertexList.at(t.v3);

        glm::vec3 vert1(v1.x, v1.y, v1.z);
        glm::vec3 vert2(v2.x, v2.y, v2.z);
        glm::vec3 vert3(v3.x, v3.y, v3.z);

        glm::vec3 c = glm::cross(vert2 - vert1, vert3 - vert1);
        glm::vec3 cnorm = glm::normalize(c);

        m_TriangleList.at(i).nx = cnorm.x;
        m_TriangleList.at(i).ny = cnorm.y;
        m_TriangleList.at(i).nz = cnorm.z;
        m_TriangleList.at(i).a = glm::length(c) / 2;

        glm::vec3 centroid = (vert1 + vert2 + vert3) / 3.0f;
        m_TriangleList.at(i).cx = centroid.x;
        m_TriangleList.at(i).cy = centroid.y;
        m_TriangleList.at(i).cz = centroid.z;
    }
    */

    std::cout << "Number of vertices: " << m_geometry.GetVerticesSize() << std::endl;
    std::cout << "Number of triangles: " << m_geometry.GetIndicesSize() / 3 << std::endl;
}

OBJ::~OBJ() {
}