
#include "Simulation.h"

Simulation::Simulation()
{
    _window = nullptr;
    _screenwidth = 1024;
    _screenheight = 720;
}
Simulation::~Simulation()
{
}

void Simulation::run()
{
    initSystems();
}

void Simulation::initSystems()
{
    // Initialise SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow("Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               _screenwidth, _screenheight, SDL_WINDOW_OPENGL);
}
