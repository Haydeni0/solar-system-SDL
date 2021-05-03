
#include "Simulation.h"

void fatalError(std::string error_string)
{ // Function to print a fatal error and quit,
    // Move to another file eventually
    std::cout << error_string << "\n";
    std::cout << "Enter any key to quit...";
    std::cin.get();
    SDL_Quit();
}

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
    simLoop();
}

void Simulation::initSystems()
{
    // Initialise SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create window
    _window = SDL_CreateWindow("Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               _screen_width, _screen_height, SDL_WINDOW_OPENGL);
    if (_window == nullptr)
        fatalError("SDL window could not be created");

    SDL_GLContext gl_context{SDL_GL_CreateContext(_window)};
    if (gl_context == nullptr)
        fatalError("SDL_GL context could not be created");
    
    GLenum error{glewInit()};
    if (error != GLEW_OK)
        fatalError("Could not initialise glew");

    // Tell SDL we want to double buffer (smoother video)
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Set background colour (when GL_COLOR_BUFFER_BIT is called)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Simulation::simLoop()
{
    // Start the simulation loop running
    _sim_state = SimState::ON;
    while (_sim_state == SimState::ON)
    {
        processInput();
        draw();
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

void Simulation::draw()
{
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER);

    // Swap the two buffers that we have
    SDL_GL_SwapWindow(_window);

}
