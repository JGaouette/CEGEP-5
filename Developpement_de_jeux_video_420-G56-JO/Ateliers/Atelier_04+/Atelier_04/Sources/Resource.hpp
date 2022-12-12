/// @file Resource.hpp
/// @brief Les ressources (TTFont et Texture).
/// @author Louis-Félix Veillette <2038026@etu.cegep-lanaudiere.qc.ca>

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

class Resource {
protected:
    Resource() {
    }

public:
    virtual ~Resource() {
    }
};
