///@file Folder.hpp
///@brief Dossier
///@authors Raphaël Sincerny

#pragma once

#include <list>
#include <string>

#include "File.hpp"

using namespace std;

///@class Folder
///@brief Class représentant un dossier
class Folder {
private:
    string name;
    list<Folder *> *folders;
    list<File *> *files;

public:
    Folder(string name) {
        this->name = name;
    }

    ~Folder() {
        while (folders->size()) {
            delete folders->back();
            folders->pop_back();
        }

        while (files->size()) {
            delete files->back();
            files->pop_back();
        }
    }

    /// @brief Création d'un dossier dans le dossier actuel
    /// @param name Nom du nouveau dossier
    void addFolder(string name) {
        folders->push_back(new Folder(this->name + "/" + name));
    }

    /// @brief Création d'un fichier dans le dossier actuel
    /// @param name Nom du nouveau fichier
    void addFile(string name) {
        files->push_back(new File(this->name + "/" + name));
    }

    /// @brief Suppression d'un dossier dans le dossier actuel
    /// @param name Le nom du dossier à supprimer
    void removeFolder(string name) {
        Folder *toRemove = findFolder(name);

        if (toRemove) {
            folders->remove(toRemove);
            delete toRemove;
        }
    }

    /// @brief Supression d'un fichier dans le dossier actuel
    /// @param name Nom du fichier à supprimer
    void removeFile(string name) {
        File *toRemove = findFile(name);

        if (toRemove) {
            files->remove(toRemove);
            delete toRemove;
        }
    }

    /// @brief Retourne le nom du dossier
    /// @return Le nom du dossier
    string getName() {
        return name;
    }

    /// @brief Recherche un dossier dans le dossier actuel
    /// @param search Le nom du dossier à chercher
    /// @return le pointeur du dossier s'il existe, nullptr sinon
    Folder *findFolder(string search) {
        for (auto &folder: *folders) {
            if (folder->getName() == search)
                return folder;
        }

        return nullptr;
    }

    /// @brief Recherche un fichier dans le dossier actuel
    /// @param search Le nom du fichier à chercher
    /// @return le pointeur du fichier s'il existe, nullptr sinon
    File *findFile(string search) {
        for (auto &file: *files) {
            if (file->getName() == search)
                return file;
        }

        return nullptr;
    }
};