/// @file Anchor.hpp
/// @brief Classe d'ancrage.
/// @author Jean-Philippe Miguel-Gagnon

#pragma once

#include "Vector3d.hpp"

enum Anchor {
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_CENTER,
    MIDDLE_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT
};

class AnchorUtils {
public:
    /// @brief Retourne la position du rectangle en fonction de l'ancre.
    /// @param position Position du rectangle.
    /// @param size Taille du rectangle.
    /// @param anchor Ancre du rectangle, par défaut en haut à gauche.
    /// @return Position du rectangle.
    static Vector3d getPosition(const Vector3d &position, const Vector3d &size, Anchor anchor = TOP_LEFT) {
        Vector3d actualPosition = position;

        switch (anchor) {
            case TOP_LEFT:
                break;
            case TOP_CENTER:
                actualPosition.x -= size.x / 2;
                break;
            case TOP_RIGHT:
                actualPosition.x -= size.x;
                break;
            case MIDDLE_LEFT:
                actualPosition.y -= size.y / 2;
                break;
            case MIDDLE_CENTER:
                actualPosition.x -= size.x / 2;
                actualPosition.y -= size.y / 2;
                break;
            case MIDDLE_RIGHT:
                actualPosition.x -= size.x;
                actualPosition.y -= size.y / 2;
                break;
            case BOTTOM_LEFT:
                actualPosition.y -= size.y;
                break;
            case BOTTOM_CENTER:
                actualPosition.x -= size.x / 2;
                actualPosition.y -= size.y;
                break;
            case BOTTOM_RIGHT:
                actualPosition.x -= size.x;
                actualPosition.y -= size.y;
                break;
        }

        return actualPosition;
    }

    /// @brief Retourne la position du milieu du rectangle en fonction de l'ancre.
    /// @param position Position du rectangle.
    /// @param size Taille du rectangle.
    /// @param anchor Ancre du rectangle, par défaut en haut à gauche.
    static Vector3d getCenterPosition(const Vector3d &position, const Vector3d &size, Anchor anchor = TOP_LEFT) {
        Vector3d actualPosition = position;

        switch (anchor) {
            case TOP_LEFT:
                actualPosition.x += size.x / 2;
                actualPosition.y += size.y / 2;
                break;
            case TOP_CENTER:
                actualPosition.y += size.y / 2;
                break;
            case TOP_RIGHT:
                actualPosition.x -= size.x / 2;
                actualPosition.y += size.y / 2;
                break;
            case MIDDLE_LEFT:
                actualPosition.x += size.x / 2;
                break;
            case MIDDLE_CENTER:
                break;
            case MIDDLE_RIGHT:
                actualPosition.x -= size.x / 2;
                break;
            case BOTTOM_LEFT:
                actualPosition.x += size.x / 2;
                actualPosition.y -= size.y / 2;
                break;
            case BOTTOM_CENTER:
                actualPosition.y -= size.y / 2;
                break;
            case BOTTOM_RIGHT:
                actualPosition.x -= size.x / 2;
                actualPosition.y -= size.y / 2;
                break;
        }

        return actualPosition;
    }

    /// @brief Retourne la position en haut au centre du rectangle en fonction de l'ancre.
    /// @param position Position du rectangle.
    /// @param size Taille du rectangle.
    /// @param anchor Ancre du rectangle, par défaut en haut à gauche.
    static Vector3d getTopCenterPosition(const Vector3d &position, const Vector3d &size, Anchor anchor = TOP_LEFT) {
        Vector3d actualPosition = position;

        switch (anchor) {
            case TOP_LEFT:
                actualPosition.x += size.x / 2;
                break;
            case TOP_CENTER:
                break;
            case TOP_RIGHT:
                actualPosition.x -= size.x / 2;
                break;
            case MIDDLE_LEFT:
                actualPosition.x += size.x / 2;
                actualPosition.y -= size.y / 2;
                break;
            case MIDDLE_CENTER:
                actualPosition.y -= size.y / 2;
                break;
            case MIDDLE_RIGHT:
                actualPosition.x -= size.x / 2;
                actualPosition.y -= size.y / 2;
                break;
            case BOTTOM_LEFT:
                actualPosition.x += size.x / 2;
                actualPosition.y -= size.y;
                break;
            case BOTTOM_CENTER:
                actualPosition.y -= size.y;
                break;
            case BOTTOM_RIGHT:
                actualPosition.x -= size.x / 2;
                actualPosition.y -= size.y;
                break;
        }

        return actualPosition;
    }
};