/// @file Rectangle.hpp
/// @brief Classe pour dessiner des rectangles.
/// @author Jean-Philippe Miguel-Gagnon, Isabelle Provost

#pragma once

#include "Anchor.hpp"
#include "Texture.hpp"
#include "Vector3d.hpp"

/// @class Rectangle
/// @brief Classe pour dessiner des rectangles.
class Rectangle {
private:
    /// @brief Dessine un rectangle.
    /// @param position Position du rectangle.
    /// @param size Taille du rectangle.
    /// @param anchor Ancre de la position, par défaut en haut à gauche.
    static void draw(Vector3d position, const Vector3d &size, Anchor anchor = TOP_LEFT) {
        position = AnchorUtils::getPosition(position, size, anchor);

        glBegin(GL_QUADS);
            glTexCoord2d(0, 0); glVertex2d(position.x, position.y);
            glTexCoord2d(1, 0); glVertex2d(position.x + size.x, position.y);
            glTexCoord2d(1, 1); glVertex2d(position.x + size.x, position.y + size.y);
            glTexCoord2d(0, 1); glVertex2d(position.x, position.y + size.y);
        glEnd();
    }

public:
    /// @brief Dessine un rectangle avec une texture.
    /// @param position Position du rectangle.
    /// @param size Taille du rectangle.
    /// @param texture Texture du rectangle.
    /// @param anchor Ancre de la position, par défaut en haut à gauche.
    static void drawTexture(const Vector3d &position, const Vector3d &size, const Texture &texture, Anchor anchor = TOP_LEFT) {
        glBindTexture(GL_TEXTURE_2D, texture.getId());
        draw(position, size, anchor);
    }

    /// @brief Dessine un rectangle avec une couleur.
    /// @param position Position du rectangle.
    /// @param size Taille du rectangle.
    /// @param color Couleur du rectangle, par défaut blanc.
    /// @param anchor Ancre de la position, par défaut en haut à gauche.
    static void drawColor(const Vector3d &position, const Vector3d &size, const SDL_Color &color = COLOR_WHITE, Anchor anchor = TOP_LEFT) {
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_COLOR);
        glColor4d(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
        draw(position, size, anchor);
        glColor4d(1, 1, 1, 1);
        glDisable(GL_COLOR);
        glEnable(GL_TEXTURE_2D);
    }

    static void drawLine(const Vector3d start, const Vector3d end, const SDL_Color &color = COLOR_WHITE, double width = 1) {
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_COLOR);
        glColor4d(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
        glLineWidth(width);
        glBegin(GL_LINES);
            glVertex2d(start.x, start.y);
            glVertex2d(end.x, end.y);
        glEnd();
        glColor4d(1, 1, 1, 1);
        glDisable(GL_COLOR);
        glEnable(GL_TEXTURE_2D);
        
    }
};