#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "simulation.h"

#define GLEW_STATIC // For building glew

int main(int argc, char** argv)
{
	Simulation mainSim;
    mainSim.run();

	return 0;
}
