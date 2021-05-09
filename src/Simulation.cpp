#include "simulation.h"
#include "errors.h"

Simulation::Simulation()
{
    _screen_width = 1024;
    _screen_height = 720;
}

Simulation::~Simulation()
{
}

void Simulation::run()
{
    initSystems();
    _sprite.init(-1, -1, 2, 2);
    simLoop();
}

void Simulation::initSystems()
{
    // Initialise SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Open an SDL window
    _window = SDL_CreateWindow("Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               _screen_width, _screen_height, SDL_WINDOW_OPENGL);
    if (_window == nullptr)
        fatalError("SDL window could not be created");

    // Set up OpenGL context
    SDL_GLContext gl_context{SDL_GL_CreateContext(_window)};
    if (gl_context == nullptr)
        fatalError("SDL_GL context could not be created");

    // Set up glew (optional but recommended)
    GLenum error{glewInit()};
    if (error != GLEW_OK)
        fatalError("Could not initialise glew");

    // Tell SDL we want a double buffered window (smoother, no flickering)
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Set background colour (when GL_COLOR_BUFFER_BIT is called)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    initShaders();
}

void Simulation::initShaders()
{
    _colour_program.compileShaders("src/shaders/colourShading.vert", "src/shaders/colourShading.frag");
    // Add the attribute defined in the vertex shader file (use the same names as the variables in the glsl file)
    _colour_program.addAttribute("vertex_position");
    _colour_program.addAttribute("vertex_colour");
    _colour_program.linkShaders();
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

    _colour_program.use();

    // Draw the sprite
    _sprite.draw();

    _colour_program.unuse();

    // Swap the two buffers that we have
    SDL_GL_SwapWindow(_window);
}
