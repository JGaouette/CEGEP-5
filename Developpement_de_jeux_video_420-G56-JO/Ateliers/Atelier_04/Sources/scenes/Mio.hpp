/// @file Mio.hpp
/// @brief Scène de base de message mio.
/// @authors Marc-Antoine Gagnon

#pragma once

#include "../Matrix44d.hpp"
#include "../elements/2d/FPSCounter.hpp"
#include "../elements/2d/HintBox.hpp"
#include "../elements/2d/Image.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/TextButton.hpp"
#include "Scene.hpp"
#include <string>

#define ON_BUTTON_CLICK 1

/// @class Mio
/// @brief Scène de pré quart qui contient tous les éléments graphiques.
class Mio : public Scene {
private:
    Matrix44d orthographic; ///< Matrice orthographique.
    Label *texte;           ///< Texte à afficher dans un label
    Image *image;           ///< Image de fond.
    TextButton *Button;     ///< Bouton pour aller à la scène suivante.
    string from;            ///< Qui envoye le mio.
    string to;              ///< Qui reçoit le mio.
    string date;            ///< À quelle date le mio à été envoyé.
    string title;           ///< Titre du mio.
    string mio;             ///< Contenu du mio.
    string redirect;        ///< Titre de la scène suivante.

public:
    Mio() {
        from = "Philippe Girard";
        to = "Toi";
        date = "Un jour en 2030";
        title = "Introduction au CAI";
        mio = "Bonjour à toi nouveau technicien officiel du CAI. Comme tu le sais, tous les techniciens ont\ndisparus mystérieusement alors les élèves de la technique informatique doivent prendre la\nrelève avec le CAI. Du devras donc faire 15 quarts de bénévolat au cours de la session\n(1 par semaine) dans la bibliothèque.\n \nPendant tes quarts, tu devras aider les personnes dans le besoin et réparer les machines\nendommagées (imprimantes, router, poste de travail, etc.) L'administration compte\nsur nous et nous accorde un budget de 5$ pour mener à bien cette mission, mais si vous\nne faites pas assez bien votre travail, elle n'hésitera pas à vous remplacer par les SIM.\n \nMoi et la Gopher comptons sur toi. Bonne chance et bonne journée, Philippe.";
        redirect = SCENE_MENU;
    }

    /// @brief Change le texte qui doit être affiché dans la scène
    /// @param from Indique qui envoye le mio
    /// @param to Indique qui reçoit le mio
    /// @param date Indique à quelle date le mio à été envoyé
    /// @param title Texte du titre à afficher
    /// @param mio Texte du mio à afficher
    /// @param redirectTo Scène vers laquelle le mio va rediriger
    void setMio(const string &from, const string &to, const string &date, const string &title, const string &mio, const string &redirectTo) {
        this->from = from;
        this->to = to;
        this->date = date;
        this->title = title;
        this->mio = mio;
        this->redirect = redirectTo;
    }

    /// @brief Chargement de la scène.
    void load() override {
        /// TODO: Activation des interrupteurs nécessaires.
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        /// TODO: Chargement des matrices de projection nécessaires.
        orthographic.loadOrthographic(size.x, size.y);

        // Resources
        ResourcesManager::addResource("font", new TTFont("Times New Roman.ttf", size.y * 0.06));
        ResourcesManager::addResource("font-small", new TTFont("Times New Roman.ttf", size.y * 0.04));

        ResourcesManager::addResource("mio", new Texture("Mio.png"));
        
        // Image background mio
        image = new Image({0, 0}, {(double) size.x, (double) size.y}, "mio");
        elements2D.push_back(image);

        // De, À, Date mio
        texte = new Label({size.x * 0.22, size.y * 0.12}, from, "font-small", COLOR_MIO_TEXT);
        elements2D.push_back(texte);
        texte = new Label({size.x * 0.22, size.y * 0.19}, to, "font-small", COLOR_MIO_TEXT);
        elements2D.push_back(texte);
        texte = new Label({size.x * 0.22, size.y * 0.255}, date, "font-small", COLOR_MIO_TEXT);
        elements2D.push_back(texte);

        // Titre mio
        texte = new Label({size.x * 0.17, size.y * 0.33}, title, "font");
        elements2D.push_back(texte);

        // Texte mio
        HintBox *hintbox = new HintBox({size.x * 0.165, size.y * 0.41}, mio, "font-small", COLOR_MIO_TEXT, DEFAULT_BACKGROUND_COLOR);
        elements2D.push_back(hintbox);

        // Button
        Button = new TextButton({size.x * 0.863, size.y * 0.012}, {size.x * 0.13, size.y * 0.085}, "Suivant", "font", COLOR_WHITE, COLOR_MIO_BUTTON, COLOR_MIO_HOVER_BUTTON);
        Button->setAction(next);
        bindEvent(SDL_MOUSEBUTTONUP, Button);
        bindEvent(SDL_MOUSEMOTION, Button);
        elements2D.push_back(Button);

        bindEvent(SDL_USEREVENT, this);
    }

    /// @brief Déchargement de la scène
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
        ResourcesManager::removeResource("font-small", true);
        ResourcesManager::removeResource("mio", true);
    }

    /// @brief Notification de la scène.
    void notification() {
        switch (Event::getCustomCode()) {
            case ON_BUTTON_CLICK:
                Application::getInstance().swapScene(this->redirect);
                break;
        }
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

    /// @brief Définit l'event du bouton suivant
    static void next() {
        Event::pushCustomEvent(ON_BUTTON_CLICK);
    }
};
