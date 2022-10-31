/// @file TimerLabel.hpp
/// @brief Classe pour l'affichage du temps restant.
/// @authors Jérémy Gaouette

#pragma once

#include "Label.hpp"
#include "../../Timer.hpp"

#include <string>

using namespace std;

/// @Class TimerLabel
/// @brief Chaîne de charactères représentant le timer
class TimerLabel : public Timer, public Drawable2d {
private:
    Label *label;       ///< Affichage du minuteur
    string prefix;      ///< Préfixe du minuteur

    /// @brief Mets à jour le text du chronomètre
    void updateLabel() {
        label->setText(prefix + Timer::format(getRemainingTime()));
    }

public:
    /// @brief Constructeur du text de minuteur.
    TimerLabel(const Vector3d& position = {0, 0}, double time = 300.0, const string& prefix = "", const string& fontName = DEFAULT_FONT, const SDL_Color& color = COLOR_WHITE) : Timer(time) {
        this->label = new Label(position, prefix + Timer::format(getRemainingTime()), fontName, color);
        this->prefix = prefix;
    }

    /// @brief Affichage du minuteur.
    void draw() {
        updateLabel();
        label->draw();
    }

    /// @brief Fonction qui notifie l'observateur.
    void notification() {
    }

    /// @brief Définir un nouveau préfix.
    void setPrefix(const string& prefix) {
        this->prefix = prefix;
    }

    /// @brief Défini un nouvel ancrage.
    void setAnchor(Anchor anchor) {
        label->setAnchor(anchor);
    }
};