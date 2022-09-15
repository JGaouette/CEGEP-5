/// @file Event.hpp
/// @brief Gestionnaire d'information d'évènements
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#pragma once
#include <SDL2/SDL.h>

/// @class Event
/// @brief Classe permettaant d'obtenir l'informations d'évènements
class Event {
private:
    static SDL_Event sdlEvent; ///< Conteneur d'informations de l'évènement
public:
    /// @brief Obtention des informations du prochain évènement 
    /// @return Le nombre d'évènements restant dans la file 
    static int poll() {
        return SDL_PollEvent(&sdlEvent);
    }

    /// @brief Obtention du type d'évènement
    /// @return Type de l'évènement
    static unsigned int getType() {
        return sdlEvent.type;
    }

    /// @brief Obtention du type d'évènement de fenêtre
    /// @return Type de l'évènement
    static unsigned int getWindowEventType() {
        return sdlEvent.window.event;
    }

    
    /// @brief Obtention de l'identifiant de fenêtre
    /// @return Identifiant
    static unsigned int getWindowId() {
        return sdlEvent.window.windowID;
    }
};

SDL_Event Event::sdlEvent; //= SDL_Event();