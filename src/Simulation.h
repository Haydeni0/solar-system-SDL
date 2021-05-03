#pragma once
#include <SDL2/SDL.h>

class Simulation
{
public:
    Simulation();
    ~Simulation();

    void run();

    void initSystems();

private:
    SDL_Window *_window;
    int _screenwidth;
    int _screenheight;
};