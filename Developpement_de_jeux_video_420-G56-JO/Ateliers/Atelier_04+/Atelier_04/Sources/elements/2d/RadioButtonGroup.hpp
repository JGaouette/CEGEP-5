/// @file RadioButton.hpp
/// @brief Contrôle visuel: RadioButton
/// @author Louis-Félix Veillette

#pragma once

#include "../../Constants.hpp"
#include "../../Event.hpp"
#include "../../Rectangle.hpp"
#include "../../Vector3d.hpp"
#include "CheckBox.hpp"
#include "Drawable2d.hpp"

/// @class RadioButton
/// @brief Contrôle visuel qui permet de sélectionner une option.
class RadioButtonGroup : public Drawable2d, public IEventElement {
private:
    map<string, CheckBox *> group;   ///< Groupe de boutons radio.
public:
    RadioButtonGroup() {
    }

    ~RadioButtonGroup() {
        for (auto &it: group) {
            delete it.second;
        }
    }

    /// @brief Ajoute un radioButton au groupe.
    /// @param radioButton Le radioButton à ajouter.
    void addToGroup(const string &value, CheckBox *checkBox) {
        if (checkBox->isChecked()) {
            for (auto item: group) {
                item.second->setUnchecked();
            }
        }
        group[value] = checkBox;
    }

    /// @brief Affichage du CheckBox.
    void draw() {
        for (auto item: group) {
            item.second->draw();
        }
    }

    /// @brief Gestion des événements.
    void notification() {
        SDL_Point mousePosition = Event::getMousePosition();
        for (const auto &it: group) {
            CheckBox *item = it.second;
            Vector3d itemPos = AnchorUtils::getPosition(item->position, item->getSize(), item->anchor);
            if (mousePosition.x >= itemPos.x && mousePosition.x <= itemPos.x + item->getSize().x && mousePosition.y >= itemPos.y && mousePosition.y <= itemPos.y + item->getSize().y) {
                for (auto other: group)
                    other.second->setUnchecked();

                item->setChecked();
                item->executeAction();

                if (action != nullptr) {
                    action();
                }
            }
        }
    }

    /// @brief Retourne la valeur du bouton radio sélectionné.
    /// @return La valeur du bouton radio sélectionné.
    string getSelectedValue() {
        for (auto item: group)
            if (item.second->isChecked())
                return item.first;

        return "";
    }
};