#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>
enum class SimState
{
    ON,
    OFF
};

class Simulation
{
public:
    Simulation();
    ~Simulation();

    void run();

private:
    SDL_Window *_window;
    int _screen_width;
    int _screen_height;
    SimState _sim_state;

    void initSystems();
    void simLoop();
    void processInput();
    void draw();
};