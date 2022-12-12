/// @file ImageButton.hpp
/// @brief Contrôle visuel: Bouton avec image
/// @author Jean-Philippe Miguel-Gagnon, Isabelle Provost

#pragma once

#include <string>

#include "../../Event.hpp"
#include "../../ResourcesManager.hpp"
#include "Button.hpp"

/// @class ImageButton
/// @brief Contrôle visuel avec une image qui peut déclencher une action.
class ImageButton : public Button {
public:
    /// @param position Position du bouton.
    /// @param size Taille du bouton.
    /// @param texture Texture du bouton.
    /// @param bgColor Couleur de fond du bouton, par défaut transparent.
    ImageButton(const Vector3d &position, const Vector3d &size, const string &texture) : Button(position, size) {
        this->texture = ResourcesManager::getResource<Texture>(texture);
    }

    ~ImageButton() {}

    /// @brief Affichage du bouton.
    void draw() {
        Rectangle::drawTexture(position, size, *texture, anchor);
    }

    /// @brief Fonction qui notifie l'observateur.
    void notification() {
        const SDL_Point mousePosition = Event::getMousePosition();
        Vector3d actualPos = AnchorUtils::getPosition(position, size, anchor);

        if (mousePosition.x >= actualPos.x && mousePosition.x <= actualPos.x + size.x && mousePosition.y >= actualPos.y && mousePosition.y <= actualPos.y + size.y) {
            if (enabled && action && Event::getType() == SDL_MOUSEBUTTONUP && Event::getMouseButton() == SDL_BUTTON_LEFT) {
                action();
            }                
        }
    }

    void setTexture(const string &texture) {
        this->texture = ResourcesManager::getResource<Texture>(texture);
    }
};
