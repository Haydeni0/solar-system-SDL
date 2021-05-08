/*
*/
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "simulation.h"

#include <fstream>

#define GLEW_STATIC // For building glew

int main(int argc, char **argv)
{
	Simulation mainSim;
	// std::ifstream shader_file("src/shaders/colourShading.vert");
	// auto a = shader_file.fail();
	// std::string line;
	// std::getline(shader_file, line);
	mainSim.run();

	return 0;
}
