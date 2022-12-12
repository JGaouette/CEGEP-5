/// @file Drawable2d.hpp
/// @brief Contrôles visuels.
/// @author Thomas Laporte

#pragma once

#include "../../Observer.hpp"

/// @class Drawable2d
/// @brief Contrôles visuels.
class Drawable2d : public Observer {
public:
    Vector3d position; ///< Position.
    Anchor anchor; ///< Ancrage.
    string name; ///< Nom.

    virtual ~Drawable2d() {}

    /// @brief Notification de l'observateur.
    virtual void notification() = 0;

    /// @brief Affichage du contrôle.
    virtual void draw() = 0;

    /// @brief Détermine la position du contrôle visuel.
    virtual void setPosition(const Vector3d& position) {
        this->position = position;
    }

    /// @brief Détermine l'ancrage du contrôle visuel.
    virtual void setAnchor(Anchor anchor) {
        this->anchor = anchor;
    }
};
