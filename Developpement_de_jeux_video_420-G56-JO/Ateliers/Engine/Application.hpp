/// @file Application.hpp
/// @brief Application
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#include <map>
#include "Window.hpp"
#include "Event.hpp"

using namespace std;

/// @class Application
/// @brief Classe permettant de gérer l'application
class Application {
private:
    map<unsigned int, Window*> windows; ///< Fenêtre de l'application

public:
    Application() {
        SDL_Init(SDL_INIT_EVERYTHING);
    }

    ~Application() {
        for (auto it : windows)
            delete it.second;
        windows.clear();

        SDL_Quit();
    }

    void addWindow(Window* window){
        windows[window->getId()] = window;
    }

    void start() {
        while(windows.size()){

            // Gestion des évènements

            while(Event::poll()){
                switch(Event::getType()) {
                    case SDL_WINDOWEVENT:
                        switch (Event::getWindowEventType()){
                            case SDL_WINDOWEVENT_CLOSE:
                                delete windows[Event::getWindowId()];
                                windows.erase(Event::getWindowId());
                            break;
                        }
                    break;
                }
            }
            

            //Gestion des mises à jour
            for (auto it : windows){
                it.second->clear();

                //Gestion de l'affichage

                it.second->refresh();
            }
        }
    }

};
