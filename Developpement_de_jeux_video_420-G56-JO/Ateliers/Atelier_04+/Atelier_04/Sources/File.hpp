///@file File.hpp
///@brief Fichier
///@authors Raphaël Sincerny

#pragma once

#include <list>
#include <string>

using std::string;

///@class File
///@brief Class représentant un fichier
class File {
private:
    string name;
    string content;

public:
    File(string name, string content = "") {
        this->name = name;
        this->content = content;
    }

    /// @brief Accéder au nom du fichier
    /// @return Le nom du fichier
    string getName() {
        return name;
    }

    /// @brief Accéder au contenu du fichier
    /// @return Le contenu du du fichier
    string getContent() {
        return content;
    }

    /// @brief Renomme le fichier
    /// @param newName Nouveau nom du fichier
    void rename(string newName) {
        name = newName;
    }

    /// @brief Modifie le contenu du fichier
    /// @param newContent Le nouveau contenu du fichier
    void changeContent(string newContent) {
        content = newContent;
    }
};