/// @file TextButton.hpp
/// @brief Contrôle visuel: Bouton avec text
/// @author Jean-Philippe Miguel-Gagnon, Isabelle Provost

#pragma once

#include <string>

#include "../../ResourcesManager.hpp"
#include "Button.hpp"

/// @class TextButton
/// @brief Contrôle visuel avec un texte qui peut déclencher une action.
class TextButton : public Button {
private:
    bool over;
    SDL_Color bgColor;   ///< Couleur de fond du bouton.
    SDL_Color ovColor;   ///< Couleur de survol du bouton.
    Label *textLabel;    ///< Label pour le texte.

public:
    /// @brief Constructeur d'un bouton avec un texte.
    /// @param position Position du bouton.
    /// @param size Taille du bouton. Elle est minimalement la taille du texte + padding.
    /// @param font Police du texte.
    /// @param text Texte du bouton.
    /// @param fgColor Couleur du texte, par défaut blanc.
    /// @param bgColor Couleur du bouton, par défaut gris.
    /// @param ovColor Couleur de survol, par défaut couleur du bouton.
    /// @param paddingX Marge intérieure sur l'axe des x, par défaut 20.
    /// @param paddingY Marge intérieure sur l'axe des y, par défaut 10.
    TextButton(const Vector3d &position, const Vector3d &size, const string &text = "Button", const string &font = DEFAULT_FONT, const SDL_Color &fgColor = COLOR_WHITE, const SDL_Color &bgColor = COLOR_DARK_GRAY, const SDL_Color &ovColor = { 0, 0, 0, 0 })
        : Button(position, size) {
        this->bgColor = bgColor;
        this->ovColor = ovColor.a ? ovColor : bgColor;
        over = false;

        textLabel = new Label(AnchorUtils::getCenterPosition(position, size, anchor), text, font, fgColor);
        textLabel->setAnchor(MIDDLE_CENTER);
    }

    ~TextButton() {
        delete texture;
    }

    /// @brief Réaction aux événement du bouton.
    virtual void notification() {
        const SDL_Point mousePosition = Event::getMousePosition();
        Vector3d actualPos = AnchorUtils::getPosition(position, size, anchor);

        if (mousePosition.x >= actualPos.x && mousePosition.x <= actualPos.x + size.x && mousePosition.y >= actualPos.y && mousePosition.y <= actualPos.y + size.y) {
            if (enabled && ovColor.a && Event::getType() == SDL_MOUSEMOTION) {
                over = true;
            }
            else if (enabled && action && Event::getType() == SDL_MOUSEBUTTONUP && Event::getMouseButton() == SDL_BUTTON_LEFT) {
                action();
            }                
        }
        else {
            over = false;
        }
    }

    void draw() {
        Rectangle::drawColor(position, size, over ? ovColor : bgColor, anchor);   // Arrière-plan
        textLabel->draw();
    }

    /// @brief Défini la couleur du bouton.
    /// @param color La nouvelle couleur.
    void setButtonColor(const SDL_Color &color) {
        bgColor = color;
    }

    /// @brief Défini la couleur du texte.
    /// @param color La nouvelle couleur.
    /// @note Ceci nécessite un regeneration du texte.
    void setTextColor(const SDL_Color &color) {
        textLabel->setColor(color);
    }

    /// @brief Défini le texte.
    /// @param value Le nouveau texte.
    /// @note Ceci nécessite un regeneration de la texture. La taille va aussi être changée par rapport au texte.
    void setText(const string &value) {
        textLabel->setText(value);
    }

    void setAnchor(const Anchor &anchor) {
        Button::setAnchor(anchor);
        textLabel->setPosition(AnchorUtils::getCenterPosition(position, size, anchor));
    }

    void setPosition(const Vector3d &position) {
        Button::setPosition(position);
        textLabel->setPosition(AnchorUtils::getCenterPosition(position, size, anchor));
    }
};
