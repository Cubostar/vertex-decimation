#include "OBJ.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include "glm/glm/gtx/transform.hpp"
#include "glm/glm/gtx/string_cast.hpp"
#include <algorithm>

OBJ::OBJ(std::string filepath) {
    std::ifstream inOBJ;

    inOBJ.open(filepath);

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
                float x_val, y_val, z_val;

                while (stream >> token) {
                    if (token[0] == 'v') {
                        continue;
                    } else {
                        if (!x) {
                            x_val = std::stof(token);
                            x = true;
                        } else if (!y) {
                            y_val = std::stof(token);
                            y = true;
                        } else if (!z) {
                            z_val = std::stof(token);
                            z = true;
                        } else {
                            continue;
                        }
                    }
                }

                m_geometry.AddVertex(x_val, y_val, z_val);

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
                        } else {
                            continue;
                        }
                    }
                }

                m_geometry.MakeTriangle(t.i1, t.i2, t.i3);
            } else {
                continue;
            }
        }
    }

    // Compute normal vectors, areas, and centroids of triangles
    m_geometry.Gen();

    /*
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

void OBJ::removeVertex() {
    // Compute distance to averaged plane for each vertex
    std::vector<float> distances;
    for (int i = 0; i < m_VertexList.size(); i++) {
        Vertex v = m_VertexList.at(i);
        // Get indices of triangles containing vertex
        std::vector<int> tidxs = getTriangles(i);
        // If the vertex is in no triangles, it's already been removed so we ignore it
        if (tidxs.size() == 0) {
            distances.push_back(std::numeric_limits<float>::infinity());
            continue;
        }

        // Compute area-weighted average normal and point to define average plane
        glm::vec3 navg(0.0f, 0.0f, 0.0f);
        glm::vec3 pavg(0.0f, 0.0f, 0.0f);
        float a = 0;
        for (int tidx : tidxs) {
            Triangle t = m_TriangleList.at(tidx);
            a += t.a;

            navg += t.a * glm::vec3(t.nx, t.ny, t.nz);
            pavg += t.a * glm::vec3(t.cx, t.cy, t.cz);
        }
        
        navg /= a;
        pavg /= a;

        glm::vec3 vvec(v.x, v.y, v.z);
        float d = (glm::dot(vvec, navg) - glm::dot(pavg, navg)) / glm::length(navg);
        distances.push_back(std::abs(d));
    }

    // Find index of vertex with shortest distance
    float shortest = std::numeric_limits<float>::infinity();
    int vidx = 0;

    for (int i = 0; i < distances.size(); i++) {
        if (distances.at(i) <= shortest) {
            vidx = i;
            shortest = distances.at(i);
        }
    }

    removeVertex(vidx);
}

void OBJ::removeVertex(int vidx) {
    // Get indices of triangles containing vertex (comes sorted)
    std::vector<int> tidxs = getTriangles(vidx);

    // Remove triangles
    int count = 0;
    std::vector<Triangle> removed;
    for (int tidx : tidxs) {
        removed.push_back(m_TriangleList.at(tidx - count));
        m_TriangleList.erase(m_TriangleList.begin() + tidx - count);
        count += 1;
    }

    // Get other vertices of triangles
    std::vector<int> retriangulate;
    for (Triangle t : removed) {
        if (t.v1 != vidx && std::find(retriangulate.begin(), retriangulate.end(), t.v1) == retriangulate.end()) {
            retriangulate.push_back(t.v1);
        } else if (t.v2 != vidx && std::find(retriangulate.begin(), retriangulate.end(), t.v2) == retriangulate.end()) {
            retriangulate.push_back(t.v2);
        } else if (t.v3 != vidx && std::find(retriangulate.begin(), retriangulate.end(), t.v3) == retriangulate.end()) {
            retriangulate.push_back(t.v3);
        } else {
            continue;
        }
    }

    // Retriangulate!
    std::sort(retriangulate.begin(), retriangulate.end());
    std::vector<Triangle> newTriangles;
    for (int i = 1; i < retriangulate.size() - 1; i++) {
        Triangle t;
        t.v1 = retriangulate.at(0);
        t.v2 = retriangulate.at(i);
        t.v3 = retriangulate.at(i + 1);

        newTriangles.push_back(t);
    }

    // Compute normal vectors, areas, and centroids of triangles
    for (int i = 0; i < newTriangles.size(); i++) {
        Triangle t = newTriangles.at(i);

        Vertex v1 = m_VertexList.at(t.v1);
        Vertex v2 = m_VertexList.at(t.v2);
        Vertex v3 = m_VertexList.at(t.v3);

        glm::vec3 vert1(v1.x, v1.y, v1.z);
        glm::vec3 vert2(v2.x, v2.y, v2.z);
        glm::vec3 vert3(v3.x, v3.y, v3.z);

        glm::vec3 c = glm::cross(vert2 - vert1, vert3 - vert1);
        glm::vec3 cnorm = glm::normalize(c);

        newTriangles.at(i).nx = cnorm.x;
        newTriangles.at(i).ny = cnorm.y;
        newTriangles.at(i).nz = cnorm.z;
        newTriangles.at(i).a = glm::length(c) / 2;

        glm::vec3 centroid = (vert1 + vert2 + vert3) / 3.0f;
        newTriangles.at(i).cx = centroid.x;
        newTriangles.at(i).cy = centroid.y;
        newTriangles.at(i).cz = centroid.z;
    }

    // Add new triangles
    for (Triangle t : newTriangles) {
        m_TriangleList.push_back(t);
    }
}

std::vector<int> OBJ::getTriangles(int vidx) {
    std::vector<int> tidxs;
    for (int i = 0; i < m_TriangleList.size(); i++) {
        Triangle t = m_TriangleList.at(i);
        if (vidx == t.v1 || vidx == t.v2 || vidx == t.v3) {
            tidxs.push_back(i);
        }
    }
    return tidxs;
}

OBJ::~OBJ() {

}