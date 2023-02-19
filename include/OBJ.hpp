#ifndef OBJ_HPP
#define OBJ_HPP

#include "Object.hpp"

class OBJ : public Object {
public:
    // OBJ Default constructor
    OBJ();
    // Construct OBJ from .obj file
    OBJ(std::string fileName);
    // OBJ Destructor
    ~OBJ();
};

#endif