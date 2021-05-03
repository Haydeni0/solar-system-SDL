
#include "Simulation.h"

Simulation::Simulation()
{
    _window = nullptr;
    _screen_width = 1024;
    _screen_height = 720;
}
Simulation::~Simulation()
{
}

void Simulation::run()
{
    initSystems();
    runLoop();
}

void Simulation::initSystems()
{
    // Initialise SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow("Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               _screen_width, _screen_height, SDL_WINDOW_OPENGL);
}

void Simulation::runLoop()
{
    _sim_state = SimState::ON;
    while (_sim_state == SimState::ON)
    {
        processInput();
    }
}

void Simulation::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            _sim_state = SimState::OFF;
            break;
        case SDL_MOUSEMOTION:
            {
                std::cout << "x: " << event.motion.x << ", y: " << event.motion.y << "\n";
            }

        default:
            break;
        }
    }
}
