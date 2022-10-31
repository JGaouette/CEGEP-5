/// @file MioPostQuart.hpp
/// @brief Scène de base de message MioPostQuart.
/// @authors Marc-Antoine Gagnon

#pragma once

#include "../elements/2d/HintBox.hpp"
#include "../elements/2d/Image.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/FPSCounter.hpp"
#include "../elements/2d/TextButton.hpp"
#include "../elements/2d/DefaultBar.hpp"
#include "../elements/2d/ReachBar.hpp"
#include "../elements/2d/ImageCounter.hpp"
#include "../Matrix44d.hpp"
#include "Scene.hpp"
#include <string>

#define ON_BUTTON_CLICK 1

/// @class Mio
/// @brief Scène de postQuart qui contient tous les éléments graphiques.
class MioPostQuart : public Scene {
private:
    Matrix44d orthographic;   ///< Matrice orthographique.
    Image *image;             ///< Image de fond.
    Label *texte;             ///< Label pour afficher du texte
    TextButton *Button;       ///< Bouton pour aller à la scène suivante.
    string from;              ///< Qui envoye le mio.
    string to;                ///< Qui reçoit le mio.
    string date;              ///< À quelle date le mio à été envoyé.
    int nbClients;            ///< Nombre de clients aidés pendant la journée
    int nbRepairs;            ///< Nombre de réparations effectuées pendant la journée
    int ptsCAI;               ///< Nombre de points CAI du joueur
    int ptsCAIRequis;         ///< Nombre de points CAI requis pour passer la journée
    int ptsCAIMax;            ///< Nombre de points CAI maximum de la journée
    ReachBar *caiMeter;       ///< ReachBar qui montre les points CAI accumulés pendant la journée
    DefaultBar *expBar;       ///< DefaultBar qui montre l'expérience du niveau actuel du joueur
    ImageCounter *imgCounter; ///< ImageCounter utilisé pour montrer le nombre de personnes aidées / machines réparées par le joueur

public:
    MioPostQuart() {
        from = "Philippe Girard";
        to = "Toi";
        date = "Un jour en 2030";
        nbClients = 1;
        nbRepairs = 1;
        ptsCAI = 500;
        ptsCAIRequis = 600;
        ptsCAIMax = 1000;
    }

    /// @brief Change le texte qui doit être affiché dans la scène
    /// @param from Indique qui envoye le mio
    /// @param to Indique qui reçoit le mio
    /// @param date Indique à quelle date le mio à été envoyé
    /// @param nbClients Nombre de clients aidés pendant la journée
    /// @param nbRepairs Nombre de réparations effectuées pendant la journée
    /// @param ptsCAI Nombre de points CAI du joueur
    /// @param ptsCAIRequis Nombre de points CAI requis pour passer la journée
    /// @param ptsCAIMax Nombre de points CAI maximum de la journée
    void setMioPostQuart(const string &from, const string &to, const string &date, const int &nbClients, const int &nbRepairs, const int &ptsCAI, const int &ptsCAIRequis, const int &ptsCAIMax) {
        this->from = from;
        this->to = to;
        this->date = date;
        this->nbClients = nbClients;
        this->nbRepairs = nbRepairs;
        this->ptsCAI = ptsCAI;
        this->ptsCAIRequis = ptsCAIRequis;
        this->ptsCAIMax = ptsCAIMax;
    }

    /// @brief Chargement de la scène.
    void load() override {

        double MARGIN_X = size.x * 0.17; ///< Marge horizontale de la scène.
        double IMAGE_SIZE = size.y * 0.07; ///< Taille des images de counters

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
        ResourcesManager::addResource("gopher", new Texture("gopher.png"));

        // Image background mio
        image = new Image({0, 0}, {(double)size.x, (double)size.y}, "mio");
        elements2D.push_back(image);

        // De, À, Date mio
        texte = new Label({size.x * 0.22, size.y * 0.12}, from, "font-small", COLOR_MIO_TEXT);
        elements2D.push_back(texte);
        texte = new Label({size.x * 0.22, size.y * 0.19}, to, "font-small", COLOR_MIO_TEXT);
        elements2D.push_back(texte);
        texte = new Label({size.x * 0.22, size.y * 0.255}, date, "font-small", COLOR_MIO_TEXT);
        elements2D.push_back(texte);
        
        // Titre mio
        texte = new Label({MARGIN_X, size.y * 0.33}, "Bilan Semaine 1", "font", DEFAULT_COLOR);
        elements2D.push_back(texte);

        // Texte mio
        HintBox *hintbox = new HintBox({size.x * 0.165, size.y * 0.41}, "Mes espions m'on informé que tu avais aidé " + to_string(nbClients) + " personne(s) et réparé " + to_string(nbRepairs) + " machine(s) aujourd'hui.\nCe qui te donne un total de " + to_string(ptsCAI) + " points CAI.", "font-small", COLOR_MIO_TEXT, DEFAULT_BACKGROUND_COLOR);
        elements2D.push_back(hintbox);

        // Counters
        imgCounter = new ImageCounter("gopher", {MARGIN_X, size.y * 0.55}, {IMAGE_SIZE, IMAGE_SIZE}, "font-small", nbClients, COLOR_WHITE);
        elements2D.push_back(imgCounter);
        imgCounter = new ImageCounter("gopher", {size.x * 0.27, size.y * 0.55}, {IMAGE_SIZE, IMAGE_SIZE}, "font-small", nbRepairs, COLOR_WHITE);
        elements2D.push_back(imgCounter);

        // Label des barres
        texte = new Label({size.x * 0.42, size.y * 0.55}, "CAI:", "font");
        elements2D.push_back(texte);
        texte = new Label({size.x * 0.35, size.y * 0.65}, to_string(ptsCAI) + " points CAI = " + to_string(ptsCAI * 5) + " points d'expérience", "font-small", COLOR_MIO_TEXT);
        elements2D.push_back(texte);
        texte = new Label({size.x * 0.51, size.y * 0.75}, "Stagiaire 4", "font-small");
        elements2D.push_back(texte);
        
        // Barres
        caiMeter = new ReachBar({size.x * 0.50, size.y * 0.55}, {size.x * 0.45, size.y * 0.06}, ptsCAIMax, ptsCAI, ptsCAIRequis, COLOR_WHITE, COLOR_RED, COLOR_BLUE);
        elements2D.push_back(caiMeter);
        expBar = new DefaultBar({size.x * 0.33, size.y * 0.80}, {size.x * 0.45, size.y * 0.06}, 20000, 16500, COLOR_WHITE, COLOR_MIO_BUTTON);
        elements2D.push_back(expBar);
        texte = new Label({size.x * 0.333, size.y * 0.81}, to_string(16500) + " / " + to_string(20000), "font-small", COLOR_BLACK);
        elements2D.push_back(texte);

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
        ResourcesManager::removeResource("gopher", true);
    }

    /// @brief Notification de la scène.
    void notification() {
        switch (Event::getCustomCode()) {
            case ON_BUTTON_CLICK:
                Application::getInstance().swapScene("GameOver");
                break;
        }
        
    }

    /// @brief Mise à jour de la scène.
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double &deltaTime) {}

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
