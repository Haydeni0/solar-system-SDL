#include "errors.h"

void fatalError(std::string error_string)
{ // Function to print a fatal error and quit,
    // Move to another file eventually
    std::cout << error_string << "\n";
    std::cout << "Enter any key to quit...";
    std::cin.get();
    SDL_Quit();
}