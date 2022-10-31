#pragma once

#include <map>
#include <string>

#include "../../Rectangle.hpp"
#include "../../Vector3d.hpp"
#include "Drawable2d.hpp"

class Division : public Drawable2d {
private:
    map<string, Drawable2d *> mapDrawables;   ///< Collection de dessinables.
    Vector3d size;                            ///< Taille de la division.

    /// @brief Met à jour la position des dessinables en fonction de la division.
    void setDrawablePosition(Drawable2d *drawable) {
        drawable->setPosition({drawable->position.x + position.x, drawable->position.y + position.y});
    }

public:
    Division(const Vector3d &position, const Vector3d &size, Anchor anchor = TOP_LEFT) {
        this->position = position;
        this->size = size;
        this->anchor = anchor;
    }

    ~Division() {
        for (auto &pair: mapDrawables) {
            delete pair.second;
        }
    }

    void setAnchor(Anchor anchor) {
        this->anchor = anchor;
        this->position = AnchorUtils::getPosition(this->position, this->size, anchor);
        for (auto &pair: mapDrawables) {
            setDrawablePosition(pair.second);
        }
    }

    /// @brief Ajoute un dessinable à la division.
    /// @param name Nom du dessinable.
    /// @param drawable Le dessinable à ajouter.
    void add(const string &name, Drawable2d *drawable) {
        setDrawablePosition(drawable);
        mapDrawables[name] = drawable;
    }

    /// @brief Retourne le dessinable.
    /// @param name Nom du dessinable.
    /// @return Le dessinable.
    Drawable2d *getDrawable(const string &name) {
        return mapDrawables[name];
    }

    /// @brief Retourne la taille de la division.
    /// @return La taille de la division.
    Vector3d getSize() {
        return size;
    }

    void notification() {
        for (auto &pair: mapDrawables) {
            pair.second->notification();
        }
    }

    void draw() {
        for (auto &pair: mapDrawables) {
            pair.second->draw();
        }
    }
};