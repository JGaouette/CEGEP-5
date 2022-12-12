/// @file QuickFixHoldButton.hpp
/// @brief Élément graphique 2d pour la réparation simple qui est de maintenir un bouton enfoncé.
/// @author Nikolas D'Amato

#pragma once

#include "DefaultBar.hpp"
#include "Drawable2d.hpp"
#include "Label.hpp"
#include "../../Chrono.hpp"

/// @class QuickFixHoldButton
/// @brief Élément graphique 2d pour la réparation simple qui est de maintenir un bouton enfoncé.
class QuickFixHoldButton : public Drawable2d,
                           public IEventElement {
private:
    Label *label; ///< Label de l'élément.
    DefaultBar *bar; ///< Barre de progression.
    bool isFixed; ///< Si la réparation est terminée.
    Vector3d size; ///< Taille de l'élément.
    Chrono chrono; ///< Chronomètre pour la progression.

public:
    /// @brief Création d'une instance de QuickFixHoldButton.
    /// @param position Position de l'élément.
    /// @param duration Durée de la réparation (10 =~ 1 Seconde).
    QuickFixHoldButton(Vector3d position = {0, 0}, float duration = 100) {
        this->position = position;
        size = {320, 50};
        label = new Label({position.x + size.x / 2, position.y}, "Garde E enfoncé pour réparer", "Side-Love.ttf", COLOR_BLACK);
        label->setAnchor(TOP_CENTER);
        bar = new DefaultBar({position.x + 5, position.y + 35}, {size.x - 10, 10}, duration, 0, COLOR_WHITE, COLOR_BLUE);
        isFixed = false;
        anchor = TOP_LEFT;
        action = nullptr;
        chrono.reset();
    }

    ~QuickFixHoldButton() {
        delete label;
        delete bar;
    }

    /// @brief Déclenchement de l'action quand la réparation est terminée.
    void onFinished(void (*action)()) {
        this->action = action;
    }

    /// @brief Met à jour le bouton.
    void increase() {
        bar->addValue(1);

        if (bar->getValue() >= bar->getMaxValue()) {
            isFixed = true;
            label->setText("Réparation terminée");
            if (action != nullptr) {
                action();
            }
        }
    }

    /// @brief Met à jour le bouton.
    void reset() {
        bar->setValue(0);
    }

    /// @brief Dessine la réparation simple.
    void draw() {
        Rectangle::drawColor(position, size, COLOR_DARK_GRAY, anchor);
        label->draw();
        bar->draw();
    }

    /// @brief Notifie le bouton que la touche E est enfoncée.
    void notification() {
        if (!isFixed) {
            if (bar->getValue() == 0) {
                chrono.reset();
                increase();
            }
            
            if ((Event::getKey() == 'e' || Event::getKey() == 'E') && Event::getType() == SDL_KEYDOWN) {
                if (chrono.getDelta() >= 0.1) {
                    increase();
                    chrono.reset();
                }
            } else {
                reset();
            }
        }
    }

    /// @brief Donne si la reparation est terminée.
    bool getIsFixed() {
        return isFixed;
    }

    /// @brief Assigne une nouvelle position au bouton.
    /// @param position Nouvelle position.
    void setPosition(const Vector3d &position) {
        label->position = position;
        bar->position = (position + Vector3d(0, 50));
    }

    void setAnchor(Anchor anchor) {
        this->anchor = anchor;
        label->setAnchor(anchor);
        bar->setAnchor(anchor);
    }
};