/// @file IEventElement.hpp
/// @brief Élément qui peuvent déclencher des évènements.
/// @author Jean-Philippe Miguel-Gagnon

#pragma once

/// @class IEventElement
/// @brief Élément qui peut déclencher des évènements.
class IEventElement {
protected:
    void (*action)();   ///< Action à effectuer lors d'un évènement.

    IEventElement() {
        action = nullptr;
    }

public:
    /// @brief Assignation d'une action au contrôle.
    /// @param action Action à exécuter.
    virtual void setAction(void (*action)()) {
        this->action = action;
    };
};