/// @file Application.hpp
/// @brief Application
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#pragma once

#include <map>
#include <string>
#include "GLContext.hpp"
#include "Event.hpp"
#include "Texture.hpp"
#include "TTFont.hpp"
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
        int actualFps = 0 ;
        bool isUp = true;
        Texture* shrekTexture = new Texture("img/shrek.png");
        
        TTFont* font = new TTFont("font/Norse.ttf", 48);
        SDL_Surface* srfShrek = font->renderText("Shrek is love <3", {255, 0, 0, 255});
        Texture* shrekIsLloveTexture = new Texture(srfShrek);
        
        SDL_Surface* srfFPS = font->renderText("FPS: 0", {255, 0, 0, 255});
        Texture* fpsTexture = new Texture(srfFPS);

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
            
            glContext.clear();
            glContext.drawingParameters(); // Gestion de l'affichage
            glContext.drawRect(shrekTexture, 0, 0, 700, 500);
            glContext.drawText(shrekIsLloveTexture, 0, 0);
            
            if(chrono->delta() >= 1){
                chrono->reset();
                actualFps = fps;
                fps = 0;

                srfFPS = font->renderText(("FPS: " + to_string(actualFps)).c_str(), {255, 0, 0, 255});
                delete fpsTexture;
                fpsTexture = new Texture(srfFPS);
            }

            glContext.drawFPS(fpsTexture);

            glContext.refresh(); 
            fps++;
        }
    }
};

Application Application::instance;
