/// @file Quart.hpp
/// @brief Quart de travail
/// @authors Thomas Laporte et Marc-Antoine Gagnon

#pragma once

#include "../Application.hpp"
#include "../Rectangle.hpp"
#include "../Anchor.hpp"
#include "../elements/2d/Image.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/DefaultBar.hpp"
#include "../elements/2d/ReachBar.hpp"
#include "../elements/2d/ImageCounter.hpp"
#include "../elements/2d/TimerLabel.hpp"
#include "Scene.hpp"

#define SHIFT_OVER 1
#define CLIENT_UP 2
#define REPAIR_UP 3

#define HUD_HEIGHT (size.y * 0.01)
#define HUD_HEIGHT_BAR (size.y * 0.02)
#define COUNTER_IMAGE_HEIGHT (size.y * 0.08)

/// @class Quart
/// @brief Scène du quart de travail
class Quart : public Scene {
private:
    Matrix44d orthographic;   ///< Matrice de projection orthographique.
    TimerLabel *timerLabel;   ///< Temps restant.
    Image *image;             ///< Image à afficher.
    Label *texte;             ///< Texte à afficher.
    ReachBar *caiMeter;       ///< ReachBar qui montre les points CAI accumulés pendant la journée
    DefaultBar *smellBar;     ///< DefaultBar qui montre l'expérience du niveau actuel du joueur
    ImageCounter *imgCounterClients; ///< ImageCounter utilisé pour montrer le nombre de personnes aidées
    ImageCounter *imgCounterRepairs; ///< ImageCounter utilisé pour montrer le nombre machines réparées par le joueur
    Anchor anchor;            ///< Ancrage de la barre d'infos.
    int nbClients;            ///< Nombre de clients aidés pendant la journée
    int nbRepairs;            ///< Nombre de réparations effectuées pendant la journée
    int ptsCAI;               ///< Nombre de points CAI du joueur
    int ptsCAIRequis;         ///< Nombre de points CAI requis pour passer la journée
    int ptsCAIMax;            ///< Nombre de points CAI maximum de la journée
    double time;              ///< Temps du quart en secondes

public:
    Quart() {
        nbClients = 0;
        nbRepairs = 0;
        ptsCAI = 0;
        ptsCAIRequis = 600;
        ptsCAIMax = 1000;
        time = 180.0;
    }

    /// @brief Change les paramètres du shift
    /// @param ptsCAIRequis Nombre de points CAI requis pour passer la journée
    /// @param ptsCAIMax Nombre de points CAI maximum de la journée
    /// @param time Temps donné au joueur pour accomplir son travail
    void setQuart(const int &ptsCAIRequis, const int &ptsCAIMax, const double &time) {
        this->ptsCAIRequis = ptsCAIRequis;
        this->ptsCAIMax = ptsCAIMax;
        this->time = time;
    }

    // @brief Chargement de la scène.
    void load() {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        orthographic.loadOrthographic(size.x, size.y);

        ResourcesManager::addResource("font", new TTFont("Times New Roman.ttf", size.y * 0.06));
        ResourcesManager::addResource("font-small", new TTFont("Times New Roman.ttf", size.y * 0.04));

        ResourcesManager::addResource("imageSmellsGood", new Texture("SmellsGood.png"));
        ResourcesManager::addResource("imageSmellsBad", new Texture("SmellsBad.png"));
        ResourcesManager::addResource("clients", new Texture("HappyClient.png"));
        ResourcesManager::addResource("repairs", new Texture("Repair.png"));

        // Counters
        imgCounterClients = new ImageCounter("clients", {size.x * 0.01, HUD_HEIGHT}, {COUNTER_IMAGE_HEIGHT, COUNTER_IMAGE_HEIGHT}, "font-small", nbClients, COLOR_BLACK);
        elements2D.push_back(imgCounterClients);
        imgCounterRepairs = new ImageCounter("repairs", {size.x * 0.11, HUD_HEIGHT}, {COUNTER_IMAGE_HEIGHT, COUNTER_IMAGE_HEIGHT}, "font-small", nbRepairs, COLOR_BLACK);
        elements2D.push_back(imgCounterRepairs);

        // Label barre cai
        texte = new Label({size.x * 0.21, size.y * 0.015}, "CAI:", "font", COLOR_BLACK);
        elements2D.push_back(texte);
        
        // barre cai
        caiMeter = new ReachBar({size.x * 0.28, HUD_HEIGHT_BAR}, {size.x * 0.20, size.y * 0.06}, ptsCAIMax, ptsCAI, ptsCAIRequis, COLOR_WHITE, COLOR_RED, COLOR_BLUE);
        elements2D.push_back(caiMeter);

        // images barre d'odeur
        image = new Image({size.x * 0.76, 0}, {size.x * 0.05, size.y * 0.1}, "imageSmellsGood");
        elements2D.push_back(image);
        image = new Image({size.x * 0.51, 0}, {size.x * 0.05, size.y * 0.1}, "imageSmellsBad");
        elements2D.push_back(image);

        // barre d'odeur
        smellBar = new DefaultBar({size.x * 0.56, HUD_HEIGHT_BAR}, {size.x * 0.20, size.y * 0.06}, 100, 70, COLOR_WHITE);
        elements2D.push_back(smellBar);

        // TimerLabel qui affiche le temps restant du shift
        timerLabel = new TimerLabel({size.x * 0.99, size.y * 0.015}, time, "Temps: ", "font", COLOR_BLACK);
        timerLabel->setAction(onShiftOver);
        timerLabel->setAnchor(TOP_RIGHT);
        elements2D.push_back(timerLabel);

        bindEvent(SDL_USEREVENT, this);
    }

    /// @brief Destructeur du menu principal
    void unload() {
        clearEvents();

        // Drawables 2D
        auto itElements2D = elements2D.begin();
        auto endElements2D = elements2D.end();
        while (itElements2D != endElements2D) {
            delete *itElements2D;
            itElements2D = elements2D.erase(itElements2D);
        }

        // Resources
        ResourcesManager::removeResource("imageSmellsGood", true);
        ResourcesManager::removeResource("imageSmellsBad", true);
        ResourcesManager::removeResource("font", true);
        ResourcesManager::removeResource("font-small", true);
        ResourcesManager::removeResource("clients", true);
        ResourcesManager::removeResource("repairs", true);
    }

    /// @brief Notification de la scène.
    void notification() {
        switch (Event::getCustomCode()) {
            // Indique que le shift est terminé
            case SHIFT_OVER:
            {
                MioPostQuart *postQuart = new MioPostQuart();
                postQuart->setMioPostQuart("Philippe Girard", "Toi", "Un jour en 2030", nbClients, nbRepairs, ptsCAI, ptsCAIRequis, ptsCAIMax);
                Application::getInstance().removeScene(SCENE_POST_QUART);
                Application::getInstance().addScene(SCENE_POST_QUART, postQuart);
                Application::getInstance().swapScene(SCENE_POST_QUART);
                break;
            }
            case CLIENT_UP:
            {
                nbClients++;
                imgCounterClients->increase(1);
                break;
            }
            case REPAIR_UP:
                nbRepairs++;
                imgCounterRepairs->increase(1);
                break;
        }
    }

    /// @brief Mise à jour de la scène.
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double &deltaTime) {
    }

    /// @brief Affichage de la scène.
    void handleDraw() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(orthographic.elements);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // Dessiner la barre 'HUD
        Rectangle::drawColor({0, 0}, {(double)size.x, size.y * 0.1}, {102, 190, 255, 255});

        for (auto element: elements2D) {
            element->draw();
        }
    }

    /// @brief Change le temps du chronomètre.
    /// @param time Nouveau temps du chronomètre.
    void changeTimeHUD(double time) {
        timerLabel->set(time);
    }

    /// @brief Indique que le shift est terminé.
    static void onShiftOver() {
        Event::pushCustomEvent(SHIFT_OVER);
    }

    /// @brief Incrémente le nombre de clients.
    static void clientUp() {
        Event::pushCustomEvent(CLIENT_UP);
    }

    /// @brief Incrémente le nombre de réparations.
    static void repairUp() {
        Event::pushCustomEvent(REPAIR_UP);
    }
};
