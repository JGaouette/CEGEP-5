/// @file Renderer.hpp
/// @brief Gestionnaire de rendu 2D
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#pragma once
#include <SDL2/SDL.h>
#include "Window.hpp"

/// @class Renderer
/// @brief Gestionnaire de rendu 2D
class Renderer : public Window {
private:
    SDL_Renderer* sdlRenderer; ///< Gestionnaire de rendu
public:
    /// @brief 
    /// @param title Titre de la fenêtre
    /// @param x  Position sur l'axe des x
    /// @param y Position sur l'axe des y
    /// @param width Largeur
    /// @param height Hauteur
    /// @param windowFlags Indicateurs de la fenêtre
    /// @param rendererFlags Indicateurs du gestion de rendu
    Renderer(const char* title = "", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 640, int height = 480, unsigned int windowFlags = 0, unsigned int rendererFlags = 0) : Window(title, x, y, width, height, windowFlags){
        sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, rendererFlags);
    }

    ~Renderer(){
        SDL_DestroyRenderer(sdlRenderer);
    }

    /// @brief Vider le contenu
    void clear(){
        SDL_RenderClear(sdlRenderer);
    }

    /// @brief Rafraîchir la fenêtre
    void refresh(){
        SDL_RenderPresent(sdlRenderer);
    }
};