/// @file PaperBall.hpp
/// @brief Scène du jeu de balle de papier.
/// @author Jérémy Gaouette


#pragma once

#include "../Matrix44d.hpp"
#include "../SaveFile.hpp"
#include "../elements/2d/Division.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/SaveSlot.hpp"
#include "../elements/2d/TextButton.hpp"
#include <list>
#include "Scene.hpp"

#define OUT_OF_BALL 1

#define CHARGE_TIME 50 ///< Temps de chargement de la balle

/// @class PaperBall
/// @brief Scène du jeu de balle de papier.
class PaperBall : public Scene {
private:
    Matrix44d orthographic; ///< Matrice de projection.

    TimerLabel *timer; ///< Chronomètre pour le jeu de boulette de papier.
    ReachBar *forceBar; ///< Barre de progression pour le jeu de boulette de papier.
    list<Image*> paperBalls; ///< Liste des boulettes de papier.

    bool increasing; ///< Indique si la barre de force gagne en valeur ou perd en valeur.
    bool isActivated; ///< Indique si la barre de force est activée.


public:
    /// @brief Chargement de la scène.
    void load() override {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        orthographic.loadOrthographic(size.x, size.y);

        increasing = true;
        isActivated = false;

        //Affichage du titre
        TTFont *titleFont = new TTFont(DEFAULT_FONT, size.y * 0.05);
        ResourcesManager::addResource("titleFont", titleFont);       
        Label *title = new Label({size.x / 2.0, size.y * 0.05}, "Boulette de papier", "titleFont", COLOR_WHITE); ///< Titre de la scène.
        title->setAnchor(TOP_CENTER);
        elements2D.push_back(title);

        //Affichage des boules de papier
        ResourcesManager::addResource("paperBall", new Texture("PaperBall.png")); 
        
        Image *paperBall1 = new Image({15, 15}, {50, 50}, "paperBall");
        paperBalls.push_back(paperBall1);
        Image *paperBall2 = new Image({65, 15}, {50, 50}, "paperBall");
        paperBalls.push_back(paperBall2);
        Image *paperBall3 = new Image({115, 15}, {50, 50}, "paperBall");
        paperBalls.push_back(paperBall3);
        Image *paperBall4 = new Image({165, 15}, {50, 50}, "paperBall");
        paperBalls.push_back(paperBall4);
        Image *paperBall5 = new Image({215, 15}, {50, 50}, "paperBall");        
        paperBalls.push_back(paperBall5);

        // Affichage du chronomètre.
        TTFont *timerFont = new TTFont(DEFAULT_FONT, size.y * 0.04); 
        ResourcesManager::addResource("timerFont", timerFont);       
        timer = new TimerLabel({(double)(size.x - 25), 25}, 60.0, "Temps restant: ", "timerFont", COLOR_WHITE);
        timer->setAnchor(TOP_RIGHT);
        elements2D.push_back(timer);

        Vector3d forceBarPosition = {size.x * 0.1, size.y * 0.9};
        Vector3d forceBarSize = {size.x * 0.8, size.y * 0.05};

        forceBar = new ReachBar(forceBarPosition, forceBarSize, 100, 0, 30);
        forceBar->setOutlineWidth(5.0);

        bindEvent(SDL_MOUSEBUTTONDOWN, this);
        bindEvent(SDL_MOUSEBUTTONUP, this);
        bindEvent(SDL_USEREVENT, this);
    }

    /// @brief Déchargementde la scène.
    void unload(){
        // Events
        clearEvents();

        // Drawables 2D
        auto itElements2D = elements2D.begin();
        auto endElements2D = elements2D.end();
        while (itElements2D != endElements2D) {
            delete *itElements2D;
            itElements2D = elements2D.erase(itElements2D);
        }

        // Paper balls
        auto itPaperBalls = paperBalls.begin();
        auto endPaperBalls = paperBalls.end();
        while (itPaperBalls != endPaperBalls) {
            delete *itPaperBalls;
            itPaperBalls = paperBalls.erase(itPaperBalls);
        }

        // Resources
        ResourcesManager::removeResource("titleFont", true);
        ResourcesManager::removeResource("timerFont", true);
        ResourcesManager::removeResource("paperBall", true);
    }

    /// @brief Notification de la scène
    void notification(){
        // Affiche la barre de progression au clic gauche maintenu.
        if (!paperBalls.empty()) {
            if (Event::getType() == SDL_MOUSEBUTTONDOWN && Event::getMouseButton() == SDL_BUTTON_LEFT) {
                elements2D.push_back(forceBar);
                isActivated = true;
            } 
        
            if (Event::getType() == SDL_MOUSEBUTTONUP && Event::getMouseButton() == SDL_BUTTON_LEFT) {
                forceBar->setValue(0);
                elements2D.remove(forceBar);
                isActivated = false;
                removePaperBall();
            }
        }

        switch(Event::getCustomCode()){
            case OUT_OF_BALL:
                    Label *label = new Label({size.x / 2.0, size.y / 2.0}, "Out of balls!", "titleFont", COLOR_WHITE);
                    label->setAnchor(MIDDLE_CENTER);
                    elements2D.push_back(label);

                    timer->stop();
                break;

        }
    }

    /// @brief Mise à jour de la scène
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double& deltaTime) override {
        if(isActivated){
            if(increasing) {
                forceBar->addValue(CHARGE_TIME * deltaTime);
                
                if (forceBar->getValue() == forceBar->getMaxValue()) {
                    increasing = false;
                }
            } else {
                forceBar->removeValue(CHARGE_TIME * deltaTime);

                if (forceBar->getValue() <= 0) {
                    increasing = true;
                }
            }
        }
    }

    /// @brief Retirer une boulette de papier.
    void removePaperBall(){
        if(!paperBalls.empty()){
            paperBalls.pop_back();
            
            if(paperBalls.empty()){
                Event::pushCustomEvent(OUT_OF_BALL);
            }
        }
    }

    /// @brief Affichage de la scène.
    void handleDraw() override {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(orthographic.elements);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        for (auto ball : paperBalls) {
            ball->draw();
        }

        for (auto element: elements2D) {
            element->draw();
        }
    }
};
