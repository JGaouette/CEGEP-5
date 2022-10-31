///@file Objectives.hpp
///@brief Classe pour les objectifs, fait pour le jeu du terminal
///@authors Ulric Richer

#pragma once

#include <string>

using namespace std;

#define OBJECTIVE_CREATE 0
#define OBJECTIVE_DELETE 1
#define OBJECTIVE_MOVE 2
#define OBJECTIVE_ZIP 3


///@class Objective
///@brief Classe représentant un objectif
class Objective {
private:
    string contenu; ///< Contenu de l'objectif, dit ce qui doit être fait
    bool complete; ///< Indique si l'objectif est complété ou non
    unsigned int action; ///< Action que l'objectif demande, nécessaire pour les vérifications
    string cible; ///< Cible de l'action de l'objectif, mettre le chemin complet, si un dossier, ne pas mettre de '/' à la fin
    bool isFileOrFolder; ///< Indique si l'action est pour un fichier ou un dossier
public:

    Objective(unsigned int action = OBJECTIVE_CREATE, string cible = "C:/Users/Patate/Desktop/machin.txt"){
        this->action = action;
        this->cible = cible;
        this->isFileOrFolder = (cible[cible.size()-4] == '.');
        contenu = "";
        complete = false;
        
        switch (action){
            case OBJECTIVE_CREATE:
                contenu += "Créer le ";
            break;
            case OBJECTIVE_DELETE:
                contenu += "Supprimer le ";
            break;
            case OBJECTIVE_MOVE:
                contenu += "Déplacer le ";
            break;
            case OBJECTIVE_ZIP:
                contenu += "Compresser le ";
            break;
        }

        contenu += (isFileOrFolder) ? "fichier " : "dossier ";

        contenu += cible.substr(cible.find_last_of("/")+1);
        
        contenu += " dans le dossier ";
        contenu += cible.substr(0, cible.find_last_of("/")+1);

    }

    Objective(string cible = "C:/Users/Patate/Desktop/machin.txt"){
        srand(time(NULL));
        this->action = rand() % 4;
        this->cible = cible;
        contenu = "";
        complete = false;
        this->isFileOrFolder = (cible[cible.size()-4] == '.');
        
        switch (action){
            case OBJECTIVE_CREATE:
                contenu += "Créer le ";
            break;
            case OBJECTIVE_DELETE:
                contenu += "Supprimer le ";
            break;
            case OBJECTIVE_MOVE:
                contenu += "Déplacer le ";
            break;
            case OBJECTIVE_ZIP:
                contenu += "Compresser le ";
            break;
        }

        contenu += (isFileOrFolder) ? "fichier " : "dossier ";

        contenu += cible.substr(cible.find_last_of("/")+1);
        
        contenu += " dans le dossier ";
        contenu += cible.substr(0, cible.find_last_of("/")+1);
    }


    string getContenu(){
        return contenu;
    }

    bool getComplete(){
        return complete;
    }

    void setComplete(bool newComplete){
        complete = newComplete;
    }

};