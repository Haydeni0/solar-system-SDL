#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "Simulation.h"

int main(int argc, char** argv)
{
	Simulation mainSim;
    mainSim.run();

	return 0;
}


