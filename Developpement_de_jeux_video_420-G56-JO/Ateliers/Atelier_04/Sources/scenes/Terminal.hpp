///@file Terminal.hpp
///@brief Scène du jeu en ligne de commandes
///@authors Raphaël Sincerny, Ulric Richer

#pragma once

#include <list>
#include <string>

#include "Scene.hpp"
#include "../elements/2d/HintBox.hpp"
#include "../elements/2d/TextBox.hpp"
#include "../elements/2d/TextButton.hpp"
#include "../elements/2d/TimerLabel.hpp"
#include "../Objectives.hpp"
#include "../Matrix44d.hpp"
#include "../Folder.hpp"

#define ON_TOGGLE_OBJECTIVES 1

///@class Terminal
///@brief Classe représentant la scène du jeu en ligne de commandes

class Terminal : public Scene {
private:
    Matrix44d orthographic; ///< Matrice de projection orthographique.
    HintBox *hintBoxObjectives;
    TextBox *terminalTextBox;
    TimerLabel *terminalTimer;
    TextButton *btnHideObjective;
    Label *terminalTitre;
    list<string*> *terminalLogs;
    list<Objective*> *terminalObjectifs;
    list<Folder*> *folders;
    bool objectivesToggled;


public:

///@brief Chargement de la scène.
    void load() override {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        orthographic.loadOrthographic(size.x, size.y);

        ResourcesManager::addResource("terminalfont", new TTFont("decterm.ttf", 24));

        //TODO: detecter quand textbox fait enter/perd focus
        //TODO: ajouter contenu du textbox au logs
        
        //TextBox pour entrer une commande
        terminalTextBox = new TextBox({100, 400}, "eeee", "terminalfont", COLOR_GREEN, 100);
        bindEvent(SDL_KEYDOWN, terminalTextBox);
        bindEvent(SDL_MOUSEBUTTONDOWN, terminalTextBox);
        elements2D.push_back(terminalTextBox);
        

        //Timer pour le temps du minijeu
        terminalTimer = new TimerLabel({200, 40}, 300.0, "Temps: ", "terminalfont", COLOR_GREEN);
        elements2D.push_back(terminalTimer);

        //Bouton pour montrer et cacher les objectifs
        btnHideObjective = new TextButton({400, 60}, {20, 20}, "-", "terminalfont", COLOR_BLACK, COLOR_GREEN, COLOR_DARK_GRAY);
        btnHideObjective->setAction([]() {
            Event::pushCustomEvent(ON_TOGGLE_OBJECTIVES);
        });
        bindEvent(SDL_MOUSEBUTTONUP, btnHideObjective);
        elements2D.push_back(btnHideObjective);

        //Titre du minijeu
        terminalTitre = new Label({200, 10}, "Titre du jeu", "terminalfont", COLOR_GREEN);
        elements2D.push_back(terminalTitre);

        //Logs des 20 dernières commandes
        terminalLogs = new list<string*>;

        //Liste des objectifs, le bool indique s'il sont complétés
        terminalObjectifs = new list<Objective*>;

        //Ajout pour tester
        terminalObjectifs->push_back(new Objective(OBJECTIVE_CREATE, "C:/Users/test/demo.txt"));
        terminalObjectifs->push_back(new Objective(OBJECTIVE_CREATE, "C:/Users/test/patate"));
        terminalObjectifs->push_back(new Objective(OBJECTIVE_DELETE, "C:/Users/test/demo2.txt"));

        //TODO: garnir les objectifs

        string txtObjectif = "";
        
        for (auto elem : *terminalObjectifs){
            txtObjectif += elem->getContenu() + "\n";
        }

        txtObjectif.replace(txtObjectif.length()-1,1,"");

        //HintBox des objectifs
        hintBoxObjectives = new HintBox({400, 80}, txtObjectif, "terminalfont", COLOR_GREEN, DEFAULT_BACKGROUND_COLOR);
        elements2D.push_back(hintBoxObjectives);
        objectivesToggled = false;

        bindEvent(SDL_USEREVENT, this);

    }

    ///@brief Déchargement de la scène.
    void unload(){
        clearEvents();
        for (int i = 0; i < terminalLogs->size(); i++){
            delete terminalLogs->front();
            terminalLogs->pop_front();
        }

        for (int i = 0; i < terminalObjectifs->size(); i++){
            delete terminalObjectifs->front();
            terminalObjectifs->pop_front();
        }

        auto itElements2D = elements2D.begin();
        auto endElements2D = elements2D.end();
        while (itElements2D != endElements2D) {
            delete *itElements2D;
            itElements2D = elements2D.erase(itElements2D);
        }

        ResourcesManager::removeResource("terminalfont", true);
    }    

    ///@brief Notification de la scène.
    void notification() {
        //TODO: quand textbox aura réglé problème d'event, updater les logs ici
        switch (Event::getKey()){
            case SDL_SCANCODE_RETURN:{
                terminalTitre->setText("enter1");
                break;
            }
            case 0:{
                terminalTitre->setText("enter2");
                break;
            }
            case '\n':{
                terminalTitre->setText("enter3");
                break;
            }
            case 'r':{
                terminalTitre->setText("r");
                break;
            }
            case 'R':{
                terminalTitre->setText("R");
                break;
            }
            default:{
                terminalTitre->setText(string(1, Event::getKey()));
                break;
            }
        }
        switch (Event::getCustomCode()) {
            case ON_TOGGLE_OBJECTIVES:

                if(!objectivesToggled) {
                    elements2D.remove(hintBoxObjectives);
                    objectivesToggled = true;
                    btnHideObjective->setText("+");
                }
                else {
                    elements2D.push_back(hintBoxObjectives);
                    objectivesToggled = false;
                    btnHideObjective->setText("-");
                }

            break;
        }
    }

    ///@brief Affichage de la scène.
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

    /// @brief Mise à jour de la scène.
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double &deltaTime) {
    }

    static void textEntry(){
    }

};