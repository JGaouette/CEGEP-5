/// @file NetworkArchitecture.hpp
/// @brief Scène du jeu "Architecture réseau".
/// @authors Isabelle Provost

#pragma once

#include "../Matrix44d.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/TimerLabel.hpp"
#include "Scene.hpp"
#include "../Application.hpp"

#define GAME_OVER 1
#define WINNER 2
#define SWAP 3

/// @class NetworkArchitecture
/// @brief Scène du jeu "Architecture réseau".
class NetworkArchitecture : public Scene {
private:
    Matrix44d orthographic; ///< Matrice de projection orthogonale (2D).
    TimerLabel *timerLabel; ///< Temps restant.
    Label *endMessage; ///< Message de fin de partie.
    SDL_Point timerSize; ///< Taille du timer.
    Vector3d labelSize; ///< Taille du message de fin de partie.

public:
    /// @brief Chargement de la scène.
    void load() override {
        // Activation des interrupteurs nécessaires
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Resources
        ResourcesManager::addResource("font", new TTFont(DEFAULT_FONT, DEFAULT_FONT_SIZE));
        ResourcesManager::addResource("font-big", new TTFont(DEFAULT_FONT, 100));

        // Chargement des matrices de projection nécessaires
        orthographic.loadOrthographic(size.x, size.y);

        // Calculer la taille du timer
        timerSize = ResourcesManager::getResource<TTFont>("font")->getSize("Temps restant: 0:00");

        // TimerLabel
        timerLabel = new TimerLabel({(double)(size.x / 2) - (double)(timerSize.x / 2), 0}, 30.0, "Temps restant: ", DEFAULT_FONT, COLOR_BLACK);
        timerLabel->setAction(onGameOver);
        elements2D.push_back(timerLabel);

        bindEvent(SDL_USEREVENT, this);
    }

    /// @brief Déchargement de la scène.
    void unload() {
        // Events
        clearEvents();

        // Drawables 2D
        auto itElements2D = elements2D.begin();
        auto endElements2D = elements2D.end();
        while (itElements2D != endElements2D) {
            delete *itElements2D;
            itElements2D = elements2D.erase(itElements2D);
        }

        // Resources
        ResourcesManager::removeResource("font", true);
        ResourcesManager::removeResource("font-big", true);
    }    

    /// @brief Notification de la scène.
    void notification() {
        switch (Event::getCustomCode()) {
            // Indique que le joueur a perdu
            case GAME_OVER:
                endMessage = new Label({0, 0}, "DÉFAITE", "font-big", COLOR_WHITE);
                labelSize = endMessage->getSize();
                endMessage->setPosition({((double)size.x / 2) - (labelSize.x / 2), ((double)size.y / 2) - (labelSize.y / 2)});
                elements2D.push_back(endMessage);
                Event::pushCustomEvent(SWAP);
                break;
            // Indique que le joueur a gagné et lui donne des points
            /// TODO: Donner des points.
            case WINNER:
                endMessage = new Label({0, 0}, "VICTOIRE", "font-big", COLOR_WHITE);
                labelSize = endMessage->getSize();
                endMessage->setPosition({((double)size.x / 2) - (labelSize.x / 2), ((double)size.y / 2) - (labelSize.y / 2)});
                elements2D.push_back(endMessage);
                Event::pushCustomEvent(SWAP);
                break;
            // Retourne dans le local
            case SWAP:
                delay(1000);
                Application::getInstance().swapScene(SCENE_QUART);
                break;
        }
    }

    /// @brief Mise à jour de la scène.
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double &deltaTime) {
    }

    /// @brief Affichage de la scène.
    void handleDraw() override {
        // Affichage 2D
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(orthographic.elements);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Barre en haut de l'écran
        Rectangle::drawColor({0, 0}, {(double)size.x, (double)timerSize.y}, {102, 190, 255, 255});
        
        // Drawables 2D
        for (auto element: elements2D) {
            element->draw();
        }
    }

    /// @brief Change le temps du chronomètre.
    /// @param time Nouveau temps du chronomètre.
    void changeTime(double time) {
        timerLabel->set(time);
    }

    /// @brief Indique que le joueur a perdu.
    static void onGameOver() {
        Event::pushCustomEvent(GAME_OVER);
    }

    /// @brief Indique que le joueur a gagné.
    static void onWin() {
        Event::pushCustomEvent(WINNER);
    }
};
