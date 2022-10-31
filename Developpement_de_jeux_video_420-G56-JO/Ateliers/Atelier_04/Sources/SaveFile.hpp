/// @file SaveFile.hpp
/// @brief Classe pour les fichiers de sauvegarde.
/// @author Jean-Philippe Miguel-Gagnon

#pragma once

#include <string>

using std::string;

/// @class SaveFile
/// @brief Classe pour les fichiers de sauvegarde.
class SaveFile {
private:
    string name;   ///< Nom du joueur.
    bool exists;   ///< Si la sauvegarde existe.
    // TODO: Ajouter les autres attributs.
public:
    /// @param name Nom du joueur.
    /// @param exists Si la sauvegarde existe.
    SaveFile(const string &name, bool exists = false) {
        this->name = name;
        this->exists = exists;
    }

    ~SaveFile();

    /// @brief Retourne le nom du joueur.
    /// @return Nom du joueur.
    string getName() const {
        return name;
    }

    /// @brief Retourne si la sauvegarde existe.
    /// @return Si la sauvegarde existe.
    bool getExists() const {
        return exists;
    }
};