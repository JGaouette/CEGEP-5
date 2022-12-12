/// @file ButtonSequence.hpp
/// @brief Élément graphique 2d pour la réparation complexe qui est de cliquer sur une séquence de boutons.
/// @author Eugène-Emmanuël Dubuc, Jérémy Perreault

// TODO : Add documentation, gerer les majuscules, mettre des carre derriere les labels
#pragma once

#include <queue>
#include <string>

using namespace std;

/// @brief Classe pour les séquences de boutons
class ButtonSequence : public Drawable2d,
                       public IEventElement {
private:
    Label *label;                       ///< Label de l'élément.
    vector<Label *> sequenceVector;       ///< List de labels pour la séquence
    queue<char> sequence;               ///< Séquence de boutons
    queue<char> sequenceOrigin;        ///< Séquence de boutons originale
    Vector3d size;                      ///< Taille de l'élément.
    unsigned int spacing; ///< Espacement entre les labels
    unsigned int sequenceCounter;   ///< Compteur de la séquence
    unsigned int sequenceSize;      ///< Taille de la séquence

public:
    /// @brief Création d'une instance de ButtonSequence.
    /// @param position Position de l'élément.
    /// @param sequenceChar Séquence de boutons.
    ButtonSequence(Vector3d position = {0, 0}, string sequenceChar = "QWERTY") {
        sequenceCounter = 0;
        sequenceSize = 0;
        spacing = 0;

        this->position = position;
        for (int i = 0; i < sequenceChar.size(); i++) {
            string t(1, sequenceChar[i]);
            if (i != 0) {
                size = label->getSize();
                spacing += size.x;
            }
            label = new Label({position.x + (i * 10 + spacing), position.y}, t, "Side-Love.ttf", COLOR_WHITE);
            sequenceVector.push_back(label);
            sequence.push(sequenceChar[i]);
            sequenceOrigin.push(sequenceChar[i]);
        }
        sequenceSize = sequence.size();

    }

    /// @brief Destructeur
    ~ButtonSequence() {
        for (auto &it: sequenceVector) {
            delete it;
        }
    }

    /// @brief Met à jour la séquence
    void update(unsigned int index) {
        sequenceVector[index]->setColor(COLOR_GREEN);
    }

    /// @brief Réinitialise la séquence
    void reset() {
        for (auto &i: sequenceVector) {
            i->setColor(COLOR_WHITE);
        }
        sequenceCounter = 0;
        sequence = sequenceOrigin;
    }

    /// @brief Dessine l'élément.
    void draw() {
        Rectangle::drawColor({position.x - 10, position.y}, {(double)(((sequenceSize + 1) * 10 + spacing)) + 10, size.y}, COLOR_BLUE_REPAIR);
        for (auto &i: sequenceVector) {
            i->draw();
        }
    }

    /// @brief Notifie que l'élément a été cliqué.
    void notification() override {
        if (Event::getKey() == tolower(sequence.front())) {
            update(sequenceCounter++);
            sequence.pop();
            if (sequence.empty()) {
                if (action) {
                    action();
                }
            }
        }
        else {
            reset();
        }
    }

    /// @brief Détermine l'ancrage de la séquence.
    void setAnchor(Anchor anchor) {
        this->anchor = anchor;
    }
};