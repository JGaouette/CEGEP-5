/// @file Application.hpp
/// @brief Classe principale de l'application.
/// @authors Raphael Rail <@answr42Hub>, Isabelle Provost <@IsabelleProvost>, Jérémie Perreault <@JeremiePerreault>, Eugène-Emmanuel Dubuc <@EugeneEmmanuelDubuc>, Olivier Savoie <@OlivierSavoie>, Gabriel Dufresne <@GabrielDufresne>, Raphael Sincerny <@RaphaelSincerny>

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <stack>
#include <string>

#include "Chrono.hpp"
#include "Constants.hpp"
#include "Event.hpp"
#include "GLContext.hpp"
#include "ResourcesManager.hpp"
#include "elements/2d/FPSCounter.hpp"
#include "scenes/Scene.hpp"

/// @class Application
/// @brief Gestion de l'application.
class Application {
private:
    stack<Scene *> scenes;            ///< Scènes actives.
    map<string, Scene *> mapScenes;   ///< Collection de scènes.
    GLContext *glContext;             ///< Contexte OpenGL.
    string nextScene;                 ///< Nom de la prochaine scène.

    static Application instance;   ///< Instance de l'application.

public:
    Application() {
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();

        glContext = new GLContext();
    }

    ~Application() {
        delete glContext;

        ResourcesManager::free();

        for (auto mapScene: mapScenes) {
            delete mapScene.second;
        }

        while (!scenes.empty()) {
            scenes.pop();
        }

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    /// @brief Démarrage de l'application.
    void start() {
        bool isUp = true;
        while (isUp) {
            while (Event::poll()) {
                unsigned int eventType = Event::getType();
                switch (eventType) {
                    case SDL_QUIT:
                        isUp = false;
                        break;

                    case SDL_WINDOWEVENT:
                        if (Event::getWindowEventType() == SDL_WINDOWEVENT_RESIZED) {
                            if (!scenes.empty()) {
                                // TODO: Peut-être pas unload la scène au complet pour éviter de recharger les ressources.
                                scenes.top()->unload();
                                scenes.top()->load();
                            }
                        }
                        break;

                    default:
                        if (!scenes.empty()) {
                            scenes.top()->handleEvent(eventType);
                        }
                }
            }

            // Changement de scène
            if (!nextScene.empty()) {
                if (!scenes.empty()) {
                    popScene();
                }
                pushScene(mapScenes[nextScene]);
                nextScene = "";
            }

            glContext->clear();
            scenes.top()->handleUpdate(0.001);   // TODO: Passé un vrai delta temps comme argument.
            scenes.top()->handleDraw();
            glContext->refresh();
        }
    }

    /// @brief Obtention de l'instance de l'application.
    /// @return Instance de l'application.
    static Application &getInstance() {
        return instance;
    }

    int setVSync(bool enabled) {
        return SDL_GL_SetSwapInterval(enabled ? 1 : 0);
    }

    /// @brief Change la taille en plein écran
    /// @param enabled Rend la fenêtre en plein écran ou non.
    void setFullScreen(bool enabled) {
        glContext->setFullScreen(enabled);
    }

    /// @brief Obtention de la largeur de la fenêtre.
    void setResolution(int width, int height) {
        for (auto mapScene: mapScenes) {
            mapScene.second->setSize({width, height});
        }
        glContext->setResolution(width, height);
    }

    /// @brief Swap de la scène courante.
    /// @param scene Nom de la scène à afficher.
    void swapScene(const string &name) {
        nextScene = name;
    }

    /// @brief Pop de la scène courante.
    void popScene() {
        scenes.top()->unload();
        scenes.pop();
    }

    /// @brief Push d'une scène.
    /// @param scene Scène à afficher.
    void pushScene(Scene *scene) {
        scene->load();
        scenes.push(scene);
    }

    /// @brief Ajout d'une scène.
    /// @param scene Scène à ajouter.
    void addScene(string name, Scene *scene) {
        scene->setSize(glContext->getSize());
        mapScenes[name] = scene;
    }

    /// @brief Suppression d'une scène.
    /// @param scene Scène à supprimer.
    void removeScene(string name) {
        delete mapScenes[name];
        mapScenes.erase(name);
    }
};

Application Application::instance;