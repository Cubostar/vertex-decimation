// Support Code written by Michael D. Shah
// Last Updated: 1/21/17
// Please do not redistribute without asking permission.


#include "SDLGraphicsProgram.hpp"
#include "OBJModel.hpp"
#include <vector>
#include <iostream>
#include <string>

int main(int argc, char** argv){

	if(argc < 2){
        std::cout << "Please specify a .obj model" << std::endl;
        return 0;
    }

	std::string modelFilepath(argv[1]);

	OBJModel obj(modelFilepath);

	// Create an instance of an object for a SDLGraphicsProgram
	SDLGraphicsProgram mySDLGraphicsProgram(1280, 720, obj);
	// Print out some useful information
	mySDLGraphicsProgram.getOpenGLVersionInfo();
	// Run our program forever
	mySDLGraphicsProgram.loop();
	// When our program ends, it will exit scope, the
	// destructor will then be called and clean up the program.
	return 0;
}
