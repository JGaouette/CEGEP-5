/// @file NewGame.hpp
/// @brief Scène pour lancer une Nouvelle Partie
/// @authors Gabriel Dufresne

#pragma once

#include "../elements/2d/TextBox.hpp"
#include "../elements/2d/TextButton.hpp"
#include "../elements/2d/Label.hpp"
#include "../Matrix44d.hpp"
#include "Scene.hpp"
#define ON_BUTTON_CLICK 1

/// @class NewGame
/// @brief Scène pour lancer une Nouvelle Partie
class NewGame : public Scene {
private:
    Matrix44d matrix;
    TextButton *startButton;
    TextButton *returnButton;
    TextBox *text;
    Label *title;
public:

    /// @brief Chargement de la scène.
   void load() override {

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // font
        TTFont *titleFont = new TTFont(DEFAULT_FONT, size.x * 0.05);
        TTFont *textFont = new TTFont(DEFAULT_FONT, size.x * 0.02);

        //resource
        ResourcesManager::addResource("font-big", textFont);
        ResourcesManager::addResource("titleFont-big", titleFont);

        //matrice de projection
        matrix.loadOrthographic(size.x, size.y);

        //label
        title = new Label({size.x * 0.33, size.y *0.05}, "Nouvelle partie ", "titleFont-big");
        elements2D.push_back(title);

        //bouton start
        startButton = new TextButton({size.x * 0.55, size.y * 0.85}, {size.x * 0.4, size.y * 0.075}, "Lancer la partie", "font-big", COLOR_WHITE, COLOR_DARK_GRAY);
        startButton->setEnabled(true);
        startButton->setAction(next);
        bindEvent(SDL_MOUSEBUTTONUP, startButton);
        elements2D.push_back(startButton);

        //bouton retour
        returnButton = new TextButton({size.x * 0.05, size.y * 0.85}, {size.x * 0.4, size.y * 0.075}, "Retour", "font-big", COLOR_WHITE, COLOR_DARK_GRAY);
        returnButton->setEnabled(true);
        returnButton->setAction(back);
        bindEvent(SDL_MOUSEBUTTONUP, returnButton);
        elements2D.push_back(returnButton);

        //textBox
        text = new TextBox({size.x * 0.31, size.y * 0.4}, "nom de la sauvegarde", "font-big");
        text->setText("nom de la partie");
        bindEvent(SDL_MOUSEBUTTONDOWN, text);
        bindEvent(SDL_KEYDOWN, text);
        elements2D.push_back(text);
    }

    /// @brief Déchargement de la scène.
    void unload() override{
        // Events
        clearEvents();

        // Drawables 2D
        auto itElements2D = elements2D.begin();
        auto endElements2D = elements2D.end();
        while (itElements2D != endElements2D) {
            delete *itElements2D;
            itElements2D = elements2D.erase(itElements2D);
        }

        //resources
        ResourcesManager::removeResource("font-big", true);
        ResourcesManager::removeResource("titleFont-big", true);
    }
    
    /// @brief Notification de la scène.
    void notification() override{

    }

     /// @brief Mise à jour de la scène.
    void handleUpdate(const double& deltaTime) override{

    }

    /// @brief Affichage de la scène.
    void handleDraw() override{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(matrix.elements);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        for (auto element: elements2D) {
            element->draw();
        }
    }

    static void back(){
        Application::getInstance().swapScene(SCENE_SAVE);
    }
    static void next(){
        Application::getInstance().swapScene(SCENE_MIO);
    }
};