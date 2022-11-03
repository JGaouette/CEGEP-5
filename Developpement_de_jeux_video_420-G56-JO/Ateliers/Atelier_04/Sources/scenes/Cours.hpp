/// @file Cours.hpp
/// @brief Scène de cours.
/// @authors Patrick Singcaster

#pragma once

#include "Scene.hpp"
#include "../Matrix44d.hpp"
#include "../elements/3d/Mesh.hpp"

/// @class Test
/// @brief Scène de cours.
class Cours : public Scene {
private:
    double rotX, rotY, rotZ; ///< Angles de rotation
    Matrix44d orthographic;  ///< Matrice de projection orthogonale.
    Matrix44d perspective;   ///< Matrice de projection perspective.
    Matrix44d rotation;      ///< Matrice de rotation.
    Mesh *mesh;              ///< Maillage.
    Matrix44d rotationX, rotationY, rotationZ;  ///< Matrices de rotation.

public:
    /// @brief Chargement de la scène.
    void load() override {
        /// TODO: Activation des interrupteurs nécessaires.
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        /// TODO: Chargement des matrices de projection nécessaires.
        orthographic.loadOrthographic(size.x, size.y);
        perspective.loadPerspective(85.0, 1.0, 10.0, (double)size.y / (double)size.x);

        /// TODO: Ajout des resources nécessaires.
        ResourcesManager::addResource("Crate", new Texture("crate.png"));

        mesh = new Mesh("../Assets/Meshes/crate.obj", "Crate");

       // mesh->translate({-5.0, 0.0, -5.0});
        rotation.loadYRotation(0.001);
        //rotation.e14 = -5.0;
        //rotation.e24 = 0.0;
        //rotation.e34 = -5.0;
        rotX = rotY = rotZ = 0.0;

        rotationX.loadXRotation(0.0003);
       // rotationX.e14 = -5.0;
       // rotationX.e24 = 0.0;
       // rotationX.e34 = -5.0;

        rotationY.loadYRotation(0.0005);
      //  rotationY.e14 = -5.0;
      //  rotationY.e24 = 0.0;
      //  rotationY.e34 = -5.0;

        rotationZ.loadZRotation(0.0007);
       // rotationZ.e14 = -5.0;
       // rotationZ.e24 = 0.0;
       // rotationZ.e34 = -5.0;

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
        mesh->localTransform(rotationX);
        mesh->localTransform(rotationY);
        mesh->localTransform(rotationZ);
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
