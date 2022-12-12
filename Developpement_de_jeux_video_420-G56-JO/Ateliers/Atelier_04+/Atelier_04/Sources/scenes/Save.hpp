/// @file Save.hpp
/// @brief Scène de sauvegarde.
/// @author Jean-Philippe Miguel-Gagnon

#pragma once

#include "../Matrix44d.hpp"
#include "../SaveFile.hpp"
#include "../elements/2d/Division.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/SaveSlot.hpp"
#include "../elements/2d/TextButton.hpp"
#include "Mio.hpp"
#include "MioPostQuart.hpp"
#include "Scene.hpp"

#define ON_SAVE_ONE_CLICK 1
#define ON_SAVE_TWO_CLICK 2
#define ON_SAVE_THREE_CLICK 3
#define ON_RETURN_CLICK 4
#define ON_LAUNCH_CLICK 5
#define ON_DELETE_CLICK 6

/// @class Save
/// @brief Scène de sauvegarde.
class Save : public Scene {
private:
    Matrix44d orthographic;   ///< Matrice de projection orthographique.

    TextButton *startButton;    ///< Bouton de lancement de la partie.
    TextButton *deleteButton;   ///< Bouton de suppression de la partie.
    TextButton *backButton;     ///< Bouton de retour au menu principal.

    SaveSlot *saveSlotOne;     ///< Slot de sauvegarde 1.
    SaveSlot *saveSlotTwo;     ///< Slot de sauvegarde 2.
    SaveSlot *saveSlotThree;   ///< Slot de sauvegarde 3.

    SaveFile *saveFileOne;     ///< Fichier de sauvegarde 1.
    SaveFile *saveFileTwo;     ///< Fichier de sauvegarde 2.
    SaveFile *saveFileThree;   ///< Fichier de sauvegarde 3.

    unsigned int saveSelected;   ///< Slot de sauvegarde sélectionné.

public:
    /// @brief Chargement de la scène.
    void load() override {
        /// Constantes de grandeurs.
        TTFont *titleFont = new TTFont(DEFAULT_FONT, size.x * 0.05);           ///< Police du titre.
        SDL_Point titleSize = titleFont->getSize("Démarrer une sauvegarde");   ///< Taille du titre.

        TTFont *buttonFont = new TTFont(DEFAULT_FONT, size.x * 0.02);   ///< Police des boutons.
        SDL_Point buttonTextSize = buttonFont->getSize("Lancer");
        SDL_Point buttonTextSize2 = buttonFont->getSize("Supprimer");
        SDL_Point buttonTextSize3 = buttonFont->getSize("Retour");
        if (buttonTextSize2.x > buttonTextSize.x) {
            buttonTextSize.x = buttonTextSize2.x;
        }
        if (buttonTextSize3.x > buttonTextSize.x) {
            buttonTextSize.x = buttonTextSize3.x;
        }

        double margin = size.x * 0.04;                  ///< Marge extérieure.
        double buttonMargin = size.y * 0.02;            ///< Marge entre les boutons.
        double buttonHeight = buttonTextSize.y * 1.1;   ///< Hauteur des boutons.
        double saveSlotMargin = size.x * 0.02;          ///< Marge entre les slots de sauvegarde.

        Vector3d divButtonPos = Vector3d(margin, size.y - margin);                                  ///< Position de la division de boutons.
        Vector3d divButtonSize = Vector3d(size.x - margin * 2, buttonHeight * 2 + buttonMargin);    ///< Taille de la division de boutons.
        Vector3d buttonSize = Vector3d(size.x - margin * 2, buttonHeight);                          ///< Taille du bouton principal.
        Vector3d halfButtonSize = Vector3d(divButtonSize.x / 2 - buttonMargin / 2, buttonSize.y);   ///< Taille des boutons secondaires.

        Vector3d divSaveSlotPos = Vector3d(margin, margin + titleSize.y + saveSlotMargin);                                                      ///< Position de la division des slots de sauvegarde.
        Vector3d divSaveSlotSize = Vector3d(size.x - margin * 2, size.y - margin * 2 - titleSize.y - (saveSlotMargin * 2) - divButtonSize.y);   ///< Taille de la division des slots de sauvegarde.
        Vector3d saveSlotSize = Vector3d((divSaveSlotSize.x - saveSlotMargin) / 3.0, divSaveSlotSize.y);                                        ///< Taille des slots de sauvegarde.

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        orthographic.loadOrthographic(size.x, size.y);

        // Resources
        ResourcesManager::addResource("titleFont-big", titleFont);
        ResourcesManager::addResource("buttonFont", buttonFont);

        // Constantes

        // Labels
        Label *title = new Label({margin, margin}, "Démarrer une sauvegarde", "titleFont-big");
        elements2D.push_back(title);

        // Boutons
        Division *buttonDiv = new Division(divButtonPos, divButtonSize);
        buttonDiv->setAnchor(BOTTOM_LEFT);

        startButton = new TextButton({}, buttonSize, "Lancer", "buttonFont", COLOR_WHITE, COLOR_DARK_GRAY);
        startButton->setEnabled(false);
        startButton->setAction([]() {
            Event::pushCustomEvent(ON_LAUNCH_CLICK);
        });
        bindEvent(SDL_MOUSEBUTTONUP, startButton);
        bindEvent(SDL_MOUSEMOTION, startButton);

        deleteButton = new TextButton({0, divButtonSize.y}, halfButtonSize, "Supprimer", "buttonFont", COLOR_WHITE, COLOR_DARK_GRAY);
        deleteButton->setAnchor(BOTTOM_LEFT);
        deleteButton->setEnabled(false);
        bindEvent(SDL_MOUSEBUTTONUP, deleteButton);
        bindEvent(SDL_MOUSEMOTION, deleteButton);

        backButton = new TextButton(divButtonSize, halfButtonSize, "Retour", "buttonFont", COLOR_WHITE, COLOR_PRIMARY, COLOR_DARK_GRAY);
        backButton->setAnchor(BOTTOM_RIGHT);
        bindEvent(SDL_MOUSEBUTTONUP, backButton);
        bindEvent(SDL_MOUSEMOTION, backButton);
        backButton->setAction(backToMainMenu);

        buttonDiv->add("start", startButton);
        buttonDiv->add("delete", deleteButton);
        buttonDiv->add("back", backButton);
        elements2D.push_back(buttonDiv);

        // Sauvegardes
        saveSelected = -1;

        saveFileOne = new SaveFile("Benjamin", true);     // temporary
        saveFileTwo = new SaveFile("Jean-Philippe", true);     // temporary
        saveFileThree = new SaveFile("none", false);   // temporary

        Division *saveDiv = new Division(divSaveSlotPos, divSaveSlotSize);

        saveSlotOne = new SaveSlot({}, saveSlotSize, *saveFileOne, "buttonFont");
        saveSlotOne->setAction([]() {
            Event::pushCustomEvent(ON_SAVE_ONE_CLICK);
        });
        bindEvent(SDL_MOUSEBUTTONUP, saveSlotOne);

        saveSlotTwo = new SaveSlot({divSaveSlotSize.x / 2}, saveSlotSize, *saveFileTwo, "buttonFont");
        saveSlotTwo->setAnchor(TOP_CENTER);
        saveSlotTwo->setAction([]() {
            Event::pushCustomEvent(ON_SAVE_TWO_CLICK);
        });
        bindEvent(SDL_MOUSEBUTTONUP, saveSlotTwo);

        saveSlotThree = new SaveSlot({divSaveSlotSize.x}, saveSlotSize, *saveFileThree, "buttonFont");
        saveSlotThree->setAnchor(TOP_RIGHT);
        saveSlotThree->setAction([]() {
            Event::pushCustomEvent(ON_SAVE_THREE_CLICK);
        });
        bindEvent(SDL_MOUSEBUTTONUP, saveSlotThree);

        saveDiv->add("save1", saveSlotOne);
        saveDiv->add("save2", saveSlotTwo);
        saveDiv->add("save3", saveSlotThree);
        elements2D.push_back(saveDiv);

        bindEvent(SDL_USEREVENT, this);
    }

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
        ResourcesManager::removeResource("titleFont-big", true);
        ResourcesManager::removeResource("buttonFont", true);
    }

    /// @brief Notification de la scène.
    void notification() {
        switch (Event::getCustomCode()) {
            case ON_SAVE_ONE_CLICK:
                enableSave(0);
                break;
            case ON_SAVE_TWO_CLICK:
                enableSave(1);
                break;
            case ON_SAVE_THREE_CLICK:
                enableSave(2);
                break;
            case ON_LAUNCH_CLICK:
                    // Récupération de la sauvegarde
                    SaveFile *saveFile;
                    switch (saveSelected) {
                        case 0:
                            saveFile = saveFileOne;
                            break;
                        case 1:
                            saveFile = saveFileTwo;
                            break;
                        case 2:
                            saveFile = saveFileThree;
                            break;
                        default:
                            return;
                    }

                    // Vérifier si la sauvegarde existe
                    if (saveFile->getExists()) {
                        // Charger la sauvegarde
                        Mio *preQuart = new Mio();
                        preQuart->setMio("Philippe Girard", "Toi", "Un jour en 2030", "CAI semaine 1", "Bonjour à toi cher technicien du CAI, cette semaine on s'attend à une hausse de personnes\nà la bibliothèque qui feront leur travaux. Attend toi à devoir aider plus de personnes.\nOn a aussi reçu une nouvelle imprimante mais elle nous fait défaut et devra surement être\nréparé. N'hésite pas a regarder un tutoriel en ligne pour savoir comment la réparer.\n \nBonne chance et bonne journée, Philippe.", "Quart");
                        Application::getInstance().removeScene(SCENE_MIO);
                        Application::getInstance().addScene(SCENE_MIO, preQuart);
                        Application::getInstance().swapScene(SCENE_MIO);
                    } else {
                        // Créer une nouvelle sauvegarde
                        Application::getInstance().swapScene(SCENE_MENU);
                    }
        }
    }

    void enableSave(unsigned int save) {
        saveSelected = save;

        switch (save) {
            case 0:
                saveSlotOne->setButtonColor(COLOR_GREEN);
                saveSlotTwo->setButtonColor(COLOR_DARK_GRAY);
                saveSlotThree->setButtonColor(COLOR_DARK_GRAY);
                break;
            case 1:
                saveSlotOne->setButtonColor(COLOR_DARK_GRAY);
                saveSlotTwo->setButtonColor(COLOR_GREEN);
                saveSlotThree->setButtonColor(COLOR_DARK_GRAY);
                break;
            case 2:
                saveSlotOne->setButtonColor(COLOR_DARK_GRAY);
                saveSlotTwo->setButtonColor(COLOR_DARK_GRAY);
                saveSlotThree->setButtonColor(COLOR_GREEN);
                break;
            default:
                disableSave();
                return;
        }

        startButton->setEnabled(true);
        startButton->setButtonColor(COLOR_PRIMARY);

        deleteButton->setEnabled(true);
        deleteButton->setButtonColor(COLOR_PRIMARY);
    }

    void disableSave() {
        saveSelected = -1;

        startButton->setEnabled(false);
        startButton->setButtonColor(COLOR_DARK_GRAY);

        deleteButton->setEnabled(false);
        deleteButton->setButtonColor(COLOR_DARK_GRAY);
    }

    /// @brief Mise à jour de la scène.
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double &deltaTime) {
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

    static void backToMainMenu() {
        Application::getInstance().swapScene(SCENE_MENU);
    }
};
