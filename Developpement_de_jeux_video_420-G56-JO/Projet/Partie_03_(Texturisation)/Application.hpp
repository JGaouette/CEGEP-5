/// @file Application.hpp
/// @brief Application
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#pragma once

#include <map>
#include "GLContext.hpp"
#include "Event.hpp"
#include "texture.hpp"
#include "font.hpp"
#include "Chrono.hpp"

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
        int fps = 0 ;
        bool isUp = true;
        Texture* texture = new Texture("img/shrek.png");
        Font* font = new Font("font/Norse.ttf", 48);
        Chrono* chrono = new Chrono();
        chrono->startTimer();

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
            glContext.drawRect(texture, 0, 0, 700, 500);
            glContext.drawText(font, "Shrek is love!", {255, 0, 0, 255}, 0, 0);

            glContext.refresh(); 
        }
    }
};

Application Application::instance;
