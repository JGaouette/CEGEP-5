/// @file OptionMenu.hpp
/// @brief Menu d'options du jeu
/// @authors Louis-Félix Veillette

#pragma once

#define ON_BACK_CLICK 1
#define ON_APPLY_CLICK 2

#include "../Application.hpp"
#include "../elements/2d/Image.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/TextButton.hpp"
#include "../elements/2d/CheckBox.hpp"
#include "../elements/2d/RadioButtonGroup.hpp"
#include "Scene.hpp"

/// @class MainMenu
/// @brief Scène du menu principal
class OptionMenu : public Scene {
private:
    Matrix44d orthographic;   ///< Matrice de projection orthographique

    Label *title;              ///< Titre du menu
    Label *labVSync;          ///< Label de VSync
    Label *labFullScreen;     ///< Label de plein écran
    Label *labResolution1;     ///< Label de résolution
    Label *labResolution2;     ///< Label de résolution
    Label *labResolution3;     ///< Label de résolution

    CheckBox *fullscreen;     ///< Bouton pour activer le plein écran
    CheckBox *vsync;          ///< Bouton pour activer le vsync
    CheckBox *chResolution1;       ///< Bouton pour activer la résolution 1920x1080
    CheckBox *chResolution2;       ///< Bouton pour activer la résolution 1280x720
    CheckBox *chResolution3;       ///< Bouton pour activer la résolution 853x480
    RadioButtonGroup *resolution;   ///< Groupe de checkbox pour choisir la résolution

    TextButton *back;         ///< Bouton pour revenir au menu principal
    TextButton *apply;        ///< Bouton pour appliquer les changements

public:
    /// @brief Constructeur du menu d'options
    void load() {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        bindEvent(SDL_USEREVENT, this);

        orthographic.loadOrthographic(size.x, size.y);

        ResourcesManager::addResource("fontTitle", new TTFont("Segoe_UI.ttf", size.x * 0.078));
        ResourcesManager::addResource("font", new TTFont("Segoe_UI.ttf", size.x * 0.032));

        title = new Label({size.x * 0.35, 0}, "Options", "fontTitle", COLOR_WHITE);
        elements2D.push_back(title);

        vsync = new CheckBox({size.x * 0.0195, size.y * 0.243}, {size.x * 0.039, size.x * 0.039}, false);
        bindEvent(SDL_MOUSEBUTTONDOWN, vsync);
        elements2D.push_back(vsync);
        labVSync = new Label({size.x * 0.078, size.y * 0.229}, "VSync", "font", COLOR_WHITE);
        elements2D.push_back(labVSync);

        fullscreen = new CheckBox({size.x * 0.0195, size.y * 0.347}, {size.x * 0.039, size.x * 0.039}, false);
        bindEvent(SDL_MOUSEBUTTONDOWN, fullscreen);
        elements2D.push_back(fullscreen);
        labFullScreen = new Label({size.x * 0.078, size.y * 0.33}, "Plein écran", "font", COLOR_WHITE);
        elements2D.push_back(labFullScreen);

        chResolution1 = new CheckBox({size.x * 0.0195, size.y * 0.4513}, {size.x * 0.039, size.x * 0.039}, false);
        elements2D.push_back(chResolution1);
        labResolution1 = new Label({size.x * 0.078, size.y * 0.43}, "1920x1080", "font", COLOR_WHITE);
        elements2D.push_back(labResolution1);

        chResolution2 = new CheckBox({size.x * 0.0195, size.y * 0.55}, {size.x * 0.039, size.x * 0.039}, true);
        elements2D.push_back(chResolution2);
        labResolution2 = new Label({size.x * 0.078, size.y * 0.5416}, "1280x720", "font", COLOR_WHITE);
        elements2D.push_back(labResolution2);

        chResolution3 = new CheckBox({size.x * 0.0195, size.y * 0.66}, {size.x * 0.039, size.x * 0.039}, false);
        elements2D.push_back(chResolution3);
        labResolution3 = new Label({size.x * 0.078, size.y * 0.652}, "853x480", "font", COLOR_WHITE);
        elements2D.push_back(labResolution3);


        resolution = new RadioButtonGroup();
        resolution->addToGroup("1920x1080", chResolution1);
        resolution->addToGroup("1280x720", chResolution2);
        resolution->addToGroup("853x480", chResolution3);
        bindEvent(SDL_MOUSEBUTTONUP, resolution);

        back = new TextButton({size.x * 0.019, size.y * 0.83}, {size.x * 0.468, size.y * 0.1041}, "Retour", "font", COLOR_WHITE, COLOR_GRAY, COLOR_DARK_GRAY);
        back->setAction(onBackClick);
        bindEvent(SDL_MOUSEBUTTONUP, back);
        bindEvent(SDL_MOUSEMOTION, back);
        elements2D.push_back(back);
        
        apply = new TextButton({size.x * 0.507, size.y * 0.83}, {size.x * 0.468, size.y * 0.1041}, "Appliquer", "font", COLOR_WHITE, COLOR_GRAY, COLOR_DARK_GRAY);
        apply->setAction(onApplyClick);
        bindEvent(SDL_MOUSEBUTTONUP, apply);
        bindEvent(SDL_MOUSEMOTION, apply);
        elements2D.push_back(apply);

    }

    /// @brief Destructeur du menu principal
    void unload() {
        clearEvents();

        auto itElements2D = elements2D.begin();
        auto endElements2D = elements2D.end();
        while (itElements2D != endElements2D) {
            delete *itElements2D;
            itElements2D = elements2D.erase(itElements2D);
        }
        ResourcesManager::removeResource("fontTitle");
        ResourcesManager::removeResource("font");

    }

    /// @brief Notification de la scène.
    void notification() {
        switch (Event::getCustomCode()) {
            case ON_APPLY_CLICK:
                if (vsync->isChecked()) {
                    Application::getInstance().setVSync(true);
                }
                else {
                    Application::getInstance().setVSync(false);
                }
                if (fullscreen->isChecked()) {
                    Application::getInstance().setFullScreen(true);
                }
                else {
                    Application::getInstance().setFullScreen(false);
                }
                if (resolution->getSelectedValue() == "1920x1080") {
                    Application::getInstance().setResolution(1920, 1080);
                    setSize({1920, 1080});
                }
                else if (resolution->getSelectedValue() == "1280x720") {
                    Application::getInstance().setResolution(1280, 720);
                    setSize({1280, 720});
                }
                else if (resolution->getSelectedValue() == "853x480") {
                    Application::getInstance().setResolution(853, 480);
                    setSize({853, 480});
                }
                Application::getInstance().swapScene("Options");
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

        for (auto element: elements2D) {
            element->draw();
        }
    }

    static void onBackClick() {
        Application::getInstance().swapScene(SCENE_MENU);
    }
    static void onApplyClick() {
        Event::pushCustomEvent(ON_APPLY_CLICK);
    }
};
