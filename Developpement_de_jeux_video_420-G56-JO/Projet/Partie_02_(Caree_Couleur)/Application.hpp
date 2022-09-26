/// @file Application.hpp
/// @brief Application
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#include <map>

#include "GLContext.hpp"
#include "Event.hpp"

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
    }

    ~Application() {
        SDL_Quit();
    }

    static Application& getInstance() {
        return instance;
    }

    void start() {
        bool isUp = true;

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
            glContext.refresh();
        }
    }
};

Application Application::instance;
