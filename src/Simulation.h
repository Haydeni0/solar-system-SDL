/*
Where all the actual simulation happens
*/
#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>

#include "sprite.h"
#include "GLSLProgram.h"
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
    SDL_Window *_window{nullptr};
    int _screen_width;
    int _screen_height;
    SimState _sim_state;
    Sprite _sprite;

    void initSystems();
    void initShaders();
    void simLoop();
    void processInput();
    void draw();

    GLSLProgram _colour_program;
};