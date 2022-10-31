/// @file Cours.hpp
/// @brief Scène de cours.
/// @authors Patrick Singcaster

#pragma once

#include "Scene.hpp"
#include "../Matrix44d.hpp"
#include "../Mesh.hpp"

/// @class Test
/// @brief Scène de cours.
class Cours : public Scene {
private:
    double rotX, rotY, rotZ; ///< Angles de rotation
    Matrix44d orthographic;  ///< Matrice de projection orthogonale.
    Matrix44d perspective;   ///< Matrice de projection perspective.
    Matrix44d rotation;      ///< Matrice de rotation.
    Mesh *mesh;              ///< Maillage.

    double *vertex, *texCoords;

public:
    /// @brief Chargement de la scène.
    void load() override {
        /// TODO: Activation des interrupteurs nécessaires.
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        /// TODO: Chargement des matrices de projection nécessaires.
        orthographic.loadOrthographic(size.x, size.y);
        perspective.loadPerspective(85.0, 1.0, 10.0, (double)size.y / (double)size.x);

        /// TODO: Ajout des resources nécessaires.
        ResourcesManager::addResource("Crate", new Texture("crate.png"));

        vertex = new double[72] { -0.5, -0.5, -0.5,  0.5, -0.5, -0.5,  0.5,  0.5, -0.5, -0.5,  0.5, -0.5,
                                  -0.5, -0.5,  0.5,  0.5, -0.5,  0.5,  0.5,  0.5,  0.5, -0.5,  0.5,  0.5,
                                  -0.5, -0.5, -0.5, -0.5,  0.5, -0.5, -0.5,  0.5,  0.5, -0.5, -0.5,  0.5,
                                   0.5, -0.5, -0.5,  0.5,  0.5, -0.5,  0.5,  0.5,  0.5,  0.5, -0.5,  0.5,
                                  -0.5, -0.5, -0.5, -0.5, -0.5,  0.5,  0.5, -0.5,  0.5,  0.5, -0.5, -0.5,
                                  -0.5,  0.5, -0.5, -0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  0.5, -0.5};


        texCoords = new double[48] {  0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
                                      0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
                                      0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
                                      0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
                                      0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
                                      0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0  };

        mesh = new Mesh(vertex, texCoords, 24);
        mesh->translate({-5.0, 0.0, -5.0});
        rotation.loadYRotation(0.001);
        rotation.e14 = -5.0;
        rotation.e24 = 0.0;
        rotation.e34 = -5.0;
        rotX = rotY = rotZ = 0.0;

    }

    /// @brief Déchargement de la scène.
    void unload() {

    }    

    /// @brief Notification de la scène.
    void notification() {

    }

    /// @brief Mise à jour de la scène.
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double &deltaTime) {
        /*
        rotX += 3.0 * deltaTime;
        rotY += 5.0 * deltaTime;
        rotZ += 7.0 * deltaTime;
        */

        //mesh->translate({0.0, 0.0, -0.0011});
        //mesh->translate({0.01, 0.0, 0.0});
        mesh->localTransform(rotation);
    }

    /// @brief Affichage de la scène.
    void handleDraw() override {
        // Affichage 3D.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(perspective.elements);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslated(0.0, 0.0, -3.0);
        glRotated(rotX, 1.0, 0.0, 0.0);
        glRotated(rotY, 0.0, 1.0, 0.0);
        glRotated(rotZ, 0.0, 0.0, 1.0);

        mesh->draw();
    }
};
