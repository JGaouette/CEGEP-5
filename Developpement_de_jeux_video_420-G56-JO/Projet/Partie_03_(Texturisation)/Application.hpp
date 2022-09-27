/// @file Application.hpp
/// @brief Application
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#pragma once

#include <map>
#include "GLContext.hpp"
#include "Event.hpp"
#include "texture.hpp"


using namespace std;

/// @class Application
/// @brief Classe permettant de gérer l'application
class Application {
private:
    static Application instance;
    GLContext glContext; ///< Contexte OpenGL
public:
    Application() {
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();
    }

    ~Application() {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    static Application& getInstance() {
        return instance;
    }

    void start() {
        bool isUp = true;
        Texture* texture = new Texture("img/shrek.png");
        Font* font = new Font("font/Norse.ttf", 24);

        while(isUp){

            // Gestion des évènements

            while(Event::poll()){
                switch(Event::getType()) {
                case SDL_QUIT:
                    isUp = false;
                    break;
                }
            }
            
            // Mise à jour de l'affichage

            glContext.clear();
            glContext.draw(); // Gestion de l'affichage
            glContext.drawRect(texture, 0, 0, 100, 100);
            glContext.drawText(font, "Hello World!", {255, 0, 0, 255}, 0, 0);
            glContext.refresh(); 
        }
    }
};

Application Application::instance;
