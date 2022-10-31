/// @file MainMenu.hpp
/// @brief Menu principal du jeu
/// @authors Louis-Félix Veillette, Thomas Laporte

#pragma once

#define ON_SAVED_CLICK 1
#define ON_OPTIONS_CLICK 2
#define ON_TEST_CLICK 3

#include "../Application.hpp"
#include "../elements/2d/Image.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/TextButton.hpp"
#include "Scene.hpp"

/// @class MainMenu
/// @brief Scène du menu principal
class MainMenu : public Scene {
private:
    Matrix44d orthographic;   ///< Matrice de projection orthographique

    Image *imageLogoCAI;    ///< Image du logo du CAI
    Image *imageTechInfo;   ///< Image des TechInfo

    Label *labCAI;        ///< Label du CAI
    Label *labSubTitle;   ///< Label du sous-titre

    TextButton *btnPlay;      ///< Bouton de jeu
    TextButton *btnOptions;   ///< Bouton d'options
    TextButton *btnQuit;      ///< Bouton de quitter
    TextButton *btnTest;      ///< Bouton de test

public:
    /// @brief Constructeur du menu principal
    void load() {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        orthographic.loadOrthographic(size.x, size.y);

        ResourcesManager::addResource("imageCAI", new Texture("LogoCAI.png"));
        ResourcesManager::addResource("techInfo", new Texture("Tech_info.png"));
        ResourcesManager::addResource("fontCai", new TTFont("Times New Roman.ttf", size.x * 0.21));
        ResourcesManager::addResource("font", new TTFont("Segoe_UI.ttf", size.x * 0.0296));

        imageLogoCAI = new Image({0, 0}, {(double)(size.x * 0.37), (double)(size.y * 0.69)}, "imageCAI");
        elements2D.push_back(imageLogoCAI);

        imageTechInfo = new Image({size.x * 0.10, size.y * 0.65}, {size.x * 0.17, size.y * 0.31}, "techInfo");
        elements2D.push_back(imageTechInfo);

        labCAI = new Label({size.x * 0.42, 0}, "C.A.I.", "fontCai");
        elements2D.push_back(labCAI);

        labSubTitle = new Label({size.x * 0.41, size.y * 0.38}, "- Dernier maitre du soutien informatique -", "font");
        elements2D.push_back(labSubTitle);

        btnPlay = new TextButton({size.x * 0.41, size.y * 0.48}, {size.x * 0.54, size.y * 0.125}, "Jouer", "font", COLOR_WHITE, COLOR_GRAY, COLOR_DARK_GRAY);
        btnPlay->setAction(savedFiles);
        bindEvent(SDL_MOUSEBUTTONUP, btnPlay);
        bindEvent(SDL_MOUSEMOTION, btnPlay);
        elements2D.push_back(btnPlay);

        btnOptions = new TextButton({size.x * 0.41, size.y * 0.666}, {size.x * 0.54, size.y * 0.125}, "Options", "font", COLOR_WHITE, COLOR_GRAY, COLOR_DARK_GRAY);
        btnOptions->setAction(options);
        bindEvent(SDL_MOUSEBUTTONUP, btnOptions);
        bindEvent(SDL_MOUSEMOTION, btnOptions);
        elements2D.push_back(btnOptions);

        btnQuit = new TextButton({size.x * 0.41, size.y * 0.847}, {size.x * 0.54, size.y * 0.125}, "Quitter", "font", COLOR_WHITE, COLOR_GRAY, COLOR_DARK_GRAY);
        btnQuit->setAction(quit);
        bindEvent(SDL_MOUSEBUTTONUP, btnQuit);
        bindEvent(SDL_MOUSEMOTION, btnQuit);
        elements2D.push_back(btnQuit);

        btnTest = new TextButton({size.x - 10.0, size.y * 0.0138}, {size.x * 0.058, size.y * 0.0347}, "Test", DEFAULT_FONT);
        btnTest->setAnchor(TOP_RIGHT);
        btnTest->setAction(test);
        bindEvent(SDL_MOUSEBUTTONUP, btnTest);
        elements2D.push_back(btnTest);
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
        ResourcesManager::removeResource("imageCAI", true);
        ResourcesManager::removeResource("techInfo", true);
        ResourcesManager::removeResource("fontCai", true);
        ResourcesManager::removeResource("font", true);
    }

    /// @brief Notification de la scène.
    void notification() {
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

        for (auto element: elements2D) {
            element->draw();
        }
    }

    /// @brief Gestion de l'événement du clique sur le bouton "Jouer".
    static void savedFiles() {
        Application::getInstance().swapScene(SCENE_SAVE);
    }

    /// @brief Gestion de l'événement du clique sur le bouton "Options".
    static void options() {
        Application::getInstance().swapScene(SCENE_OPTIONS);
    }

    /// @brief Gestion de l'événement du clique sur le bouton "Quitter".
    static void quit() {
        Event::pushQuitEvent();
    }

    /// @brief Gestion de l'événement du clique sur le bouton "Test".
    static void test() {
        Application::getInstance().swapScene(SCENE_TEST);
    }
};
