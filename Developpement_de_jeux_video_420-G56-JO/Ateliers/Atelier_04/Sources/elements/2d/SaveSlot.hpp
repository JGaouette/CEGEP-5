/// @file SaveSlot.hpp
/// @brief Classe pour afficher une sauvegarde.
/// @author Jean-Philippe Miguel-Gagnon

#pragma once

#include "../../SaveFile.hpp"
#include "Button.hpp"
#include "Label.hpp"

/// @class SaveSlot
/// @brief Classe pour afficher une sauvegarde.
class SaveSlot : public Button {
private:
    TTFont *font;        ///< Police d'écriture.
    Label *title;        ///< Label pour le titre de la sauvegarde.
    Label *details;         ///< Label pour les détails de la sauvegarde.
    SDL_Color bgColor;   ///< Couleur de fond.

public:
    /// @brief Constructeur.
    /// @param position Position du slot.
    /// @param size Taille du slot.
    /// @param saveFile Fichier de sauvegarde.
    /// @param fgColor Couleur du texte, par défaut blanc.
    /// @param bgColor Couleur de fond, par défaut gris foncé.
    SaveSlot(const Vector3d &position, const Vector3d &size, const SaveFile &saveFile, const string &fontName = DEFAULT_FONT, const SDL_Color &fgColor = COLOR_WHITE, const SDL_Color &bgColor = COLOR_DARK_GRAY)
        : Button(position, size) {
        this->bgColor = bgColor;

        if (saveFile.getExists()) {
            title = new Label({}, saveFile.getName(), fontName, fgColor);
            details = new Label({}, "Détails", fontName, fgColor);
        }
        else {
            title = new Label({}, "Aucune", fontName, fgColor);
            details = new Label({}, "Créer une sauvegarde", fontName, fgColor);
        }

        title->setAnchor(TOP_CENTER);
        details->setAnchor(TOP_CENTER);

        setLabelPositions();
    }

    ~SaveSlot() {
        delete title;
        delete details;
    }

    /// @brief Dessine le slot.
    void draw() {
        Rectangle::drawColor(position, size, bgColor, anchor);
        title->draw();
        Vector3d linePos = AnchorUtils::getPosition(position, size, anchor);
        Rectangle::drawLine({linePos.x, title->position.y + title->getSize().y + 5},
                            {linePos.x + size.x, title->position.y + title->getSize().y + 5},
                            COLOR_WHITE, 2);
        details->draw();
    }

    /// @brief Défini la couleur du bouton.
    /// @param color La nouvelle couleur.
    void setButtonColor(const SDL_Color &color) {
        bgColor = color;
    }

    void setAnchor(Anchor anchor) {
        this->anchor = anchor;

        setLabelPositions();
    }

    void setLabelPositions() {
        Vector3d topCenter = AnchorUtils::getTopCenterPosition(position, size, anchor);

        title->setPosition({topCenter.x, topCenter.y + 5});
        details->setPosition({topCenter.x, title->position.y + title->getSize().y + 7});
    }

    void setPosition(const Vector3d &position) {
        Button::setPosition(position);
        setLabelPositions();
    }
};
