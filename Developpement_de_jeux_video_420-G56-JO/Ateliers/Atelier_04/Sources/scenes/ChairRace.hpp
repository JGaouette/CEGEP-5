/// @file ChairRace.hpp
/// @brief Scène de course de chaise.
/// @authors Nikolas D'Amato

#pragma once

#include "../Chrono.hpp"
#include "../Matrix44d.hpp"
#include "../elements/2d/DefaultBar.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/TextButton.hpp"
#include "../elements/2d/TimerLabel.hpp"
#include "Scene.hpp"

// Types d'événement personnalisé
#define ON_LAP_DONE 2
#define START_COUTDOWN 3
#define RACE_STARTED 4
#define RACE_FINISHED 5
#define GIVE_BOOST 6

using namespace std;

/// @class ChairRace
/// @brief Scène de course de chaise.
class ChairRace : public Scene {
private:
    Matrix44d orthographic;   ///< Matrice orthographique.
    Label *lap;               ///< Label de la manche.
    DefaultBar *boost;        ///< Barre de boost.
    TimerLabel *time;         ///< Label du temps à ne pas dépasser.
    Chrono chrono;            ///< Chronomètre pour la progression.
    TextButton *btnStart;     ///< Bouton pour commencer la course.
    Label *countdown;         ///< Label du compte à rebours.
    int lapCount;             ///< Nombre de manche.
    int counter;              ///< Compteur pour le compte à rebours.
    bool startedCountdown;    ///< Booléen pour savoir si la course a commencé.
    bool shiftIsPressed;      ///< Booléen pour savoir si la touche shift est appuyé.

public:
    ChairRace() {
        lapCount = 0;
        counter = 3;
        startedCountdown = false;
        shiftIsPressed = false;
    }

    /// @brief Chargement de la scène.
    void load() override {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        orthographic.loadOrthographic(size.x, size.y);

        // Resources
        ResourcesManager::addResource("font-medium", new TTFont(DEFAULT_FONT, 32));
        ResourcesManager::addResource("font-big", new TTFont("Side-Love.ttf", 100));

        // Ajout des éléments de la scène.
        lap = new Label({size.x - 190.0, 10}, "LAP: 1/3", "font-medium", COLOR_WHITE);
        elements2D.push_back(lap);

        time = new TimerLabel({size.x - 190.0, 50}, 60.0, "TIME: ", "font-medium");
        time->stop();
        elements2D.push_back(time);

        boost = new DefaultBar({size.x * 0.85 - size.y * 0.05, size.y * 0.90}, {size.x * 0.15, size.y * 0.05}, 100.0, 70.0, COLOR_YELLOW, COLOR_RED);
        elements2D.push_back(boost);

        countdown = new Label({size.x / 2.0, size.y * 0.4}, "3", "font-big", COLOR_WHITE);
        countdown->setAnchor(MIDDLE_CENTER);
        elements2D.push_back(countdown);

        btnStart = new TextButton({size.x / 2.0, size.y / 2.0}, {size.x * 0.15, size.y * 0.05}, "START", "font-medium", COLOR_WHITE);
        btnStart->setAnchor(MIDDLE_CENTER);
        btnStart->setAction(startCountdown);
        bindEvent(SDL_MOUSEBUTTONUP, btnStart);
        elements2D.push_back(btnStart);

        bindEvent(SDL_USEREVENT, this);
        bindEvent(SDL_KEYDOWN, this);
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
        ResourcesManager::removeResource("font-big", true);
        ResourcesManager::removeResource("font-medium", true);
    }

    /// @brief Notification de la scène.
    void notification() {
        if ((Event::getKeyMod() & KMOD_SHIFT) && Event::getType() == SDL_KEYDOWN) {
            shiftIsPressed = true;
        }
        else {
            shiftIsPressed = false;
        }

        switch (Event::getCustomCode()) {
            case ON_LAP_DONE: {
                lapCount++;
                if (lapCount > 3) {
                    lap->setText("FINISH");
                    raceFinished();
                }
                else {
                    lap->setText("LAP: " + to_string(lapCount) + "/3");
                }
                break;
            }

            case START_COUTDOWN: {
                unbindEvent(SDL_MOUSEBUTTONUP, btnStart);
                delete btnStart;
                elements2D.remove(btnStart);

                startedCountdown = true;
                break;
            }

            case RACE_STARTED: {
                time->resume();
                bindEvent(SDL_KEYDOWN, this);
                bindEvent(SDL_KEYUP, this);
                break;
            }

            case RACE_FINISHED: {
                time->stop();
                shiftIsPressed = false;
                unbindEvent(SDL_KEYDOWN, this);
                unbindEvent(SDL_KEYUP, this);
                break;
            }

            case GIVE_BOOST: {
                boost->setValue(boost->getValue() + 50.0);
                break;
            }
        }
    }

    /// @brief Mise à jour de la scène.
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double &deltaTime) {
        if (!startedCountdown) {
            if (boost->getValue() > 0) {
                if (shiftIsPressed) {
                    if (chrono.getDelta() > 0.1) {
                        boost->removeValue(1);
                        chrono.reset();
                    }
                }
                else {
                    chrono.reset();
                }
            }
        }
        else {
            upadteCountdown();
        }

        if (time->getRemainingTime() <= 0) {
            lap->setText("YOU LOSE");

            raceFinished();
        }
    }

    /// @brief Affichage de la scène.
    void handleDraw() override {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(orthographic.elements);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        for (auto element: elements2D) {
            element->draw();
        }
    }

    /// @brief Démarre le compte à rebours.
    void upadteCountdown() {
        if (chrono.getDelta() > 1.0) {
            if (counter > 0) {
                countdown->setText(to_string(counter));
                counter--;
            }
            else if (counter == 0) {
                counter--;
                countdown->setText("GO!");
            }
            else {
                counter--;
                delete countdown;
                elements2D.remove(countdown);
                startedCountdown = false;
                raceStarted();
            }
            chrono.reset();
        }
    }

    static void onLapDone() {
        Event::pushCustomEvent(ON_LAP_DONE);
    }

    static void startCountdown() {
        Event::pushCustomEvent(START_COUTDOWN);
    }

    static void raceStarted() {
        Event::pushCustomEvent(RACE_STARTED);
    }

    static void raceFinished() {
        Event::pushCustomEvent(RACE_FINISHED);
    }

    static void giveBoost() {
        Event::pushCustomEvent(GIVE_BOOST);
    }
};
