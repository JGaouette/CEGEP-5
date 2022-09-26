/// @file Window.hpp
/// @bief Fenêtre du système d'exploitation
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_ttf.h"


/// @class Window
/// @brief Classe représentant une fenêtre du système d'exploitation
class Window {
protected:
    SDL_Window* sdlWindow; ///< Fenêtre

public:
    /// @brief 
    /// @param title Titre de la fenêtre
    /// @param x  Position sur l'axe des x
    /// @param y Position sur l'axe des y
    /// @param width Largeur
    /// @param height Hauteur
    /// @param flags Indicateurs
    Window(const char* title = "", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 640, int height = 480, unsigned int flags = 0){
        sdlWindow = SDL_CreateWindow(title, x, y, width, height, flags);
    }

    virtual ~Window(){
        SDL_DestroyWindow(sdlWindow);
    }   

    /// @brief Obtention de l'identifiant de la fenêtre
    /// @return Identifiant
    unsigned int getId(){
        return SDL_GetWindowID(sdlWindow);
    }

    /// @brief Vider le contenu
    virtual void clear() = 0;
    /// @brief Rafraîchir la fenêtre
    virtual void refresh() = 0;
};
