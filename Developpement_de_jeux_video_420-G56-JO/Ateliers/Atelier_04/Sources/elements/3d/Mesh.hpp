/// @file Mesh.hpp
/// @brief Maillage
/// @author Jérémy Gaouette

#pragma once

#include <fstream>
#include <vector>
#include <string>
#include "../../ResourcesManager.hpp"


/// @class Mesh
/// @brief Maillage
class Mesh {
private:
    double *vertices;           ///< Sommets
    double *texCoords;          ///< Coordonnées de texture
    size_t vertexCount;         ///< Nombre de sommets.
    unsigned int textureId;     ///< Identifiant de la texture.
    double *normals;            ///< Normales

public:
    /// @brief Classe représentant un maillage.
    /// @param fileName Nom du fichier contenant le maillage.
    /// @param textureId Identifiant de la texture.
    Mesh(const char* fileName, const string& textureName) {
        textureId = ResourcesManager::getResource<Texture>(textureName)->getId();
        
        ifstream file;
        file.open(fileName);
        
        if (file.is_open()) {
            vector<double> v;
            vector<double> vt;
            vector<double> vn;
            vector<int> f;

            string read;

            while(!file.eof()){
                file >> read;

                if (read == "#" || read == "o" || read == "g" || read == "s") {
                    file.ignore(256, 10);
                }
                else if (read == "v"){
                    double x, y, z;
                    file >> x >> y >> z;
                    v.push_back(x);
                    v.push_back(y);
                    v.push_back(z);
                }
                else if (read == "vt"){
                    double x, y;
                    file >> x >> y;
                    vt.push_back(x);
                    vt.push_back(y);
                }
                else if (read == "vn"){
                    double x, y, z;
                    file >> x >> y >> z;
                    vn.push_back(x);
                    vn.push_back(y);
                    vn.push_back(z);
                }
                else if (read == "f"){
                    for (int i = 0; i < 3; i++){
                        int x, y, z;
                        file >> x >> read >> y >> read >> z;
                        f.push_back(x);
                        f.push_back(y);
                        f.push_back(z);
                    }
                }
            }
            
            vertexCount = f.size() / 3;
            vertices = new double[vertexCount * 3];
            texCoords = new double[vertexCount * 2];
            normals = new double[vertexCount * 3];

            for (int i = 0; i < f.size(); i += 3){
                vertices[i] = v[(f[i] - 1) * 3];
                vertices[i + 1] = v[(f[i] - 1) * 3 + 1];
                vertices[i + 2] = v[(f[i] - 1) * 3 + 2];

                texCoords[i / 3 * 2] = vt[(f[i + 1] - 1) * 2];
                texCoords[i / 3 * 2 + 1] = vt[(f[i + 1] - 1) * 2 + 1];

                normals[i] = vn[(f[i + 2] - 1) * 3];
                normals[i + 1] = vn[(f[i + 2] - 1) * 3 + 1];
                normals[i + 2] = vn[(f[i + 2] - 1) * 3 + 2];
            }

            file.close();
        }

        /*
        vertexCount = 24;

        vertices = new double[72] { 
            -0.5, -0.5, -0.5,  0.5, -0.5, -0.5,  0.5,  0.5, -0.5, -0.5,  0.5, -0.5, 
            -0.5, -0.5,  0.5,  0.5, -0.5,  0.5,  0.5,  0.5,  0.5, -0.5,  0.5,  0.5, 
            -0.5, -0.5,  0.5, -0.5, -0.5, -0.5,  0.5, -0.5, -0.5,  0.5, -0.5,  0.5, 
            -0.5,  0.5,  0.5, -0.5,  0.5, -0.5,  0.5,  0.5, -0.5,  0.5,  0.5,  0.5, 
            -0.5,  0.5,  0.5, -0.5,  0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5,  0.5, 
             0.5,  0.5,  0.5,  0.5,  0.5, -0.5,  0.5, -0.5, -0.5,  0.5, -0.5,  0.5};
        
        texCoords = new double[48] {  
            0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0  };

        normals = new double[72] {  
             0.0,  0.0, -1.0,  0.0,  0.0, -1.0,  0.0,  0.0, -1.0,  0.0,  0.0, -1.0,    //Back
             0.0,  0.0,  1.0,  0.0,  0.0,  1.0,  0.0,  0.0,  1.0,  0.0,  0.0,  1.0,    //Front
             0.0, -1.0,  0.0,  0.0, -1.0,  0.0,  0.0, -1.0,  0.0,  0.0, -1.0,  0.0,    //Bottom
             0.0,  1.0,  0.0,  0.0,  1.0,  0.0,  0.0,  1.0,  0.0,  0.0,  1.0,  0.0,    //Top
            -1.0,  0.0,  0.0, -1.0,  0.0,  0.0, -1.0,  0.0,  0.0, -1.0,  0.0,  0.0,    //Left
             1.0,  0.0,  0.0,  1.0,  0.0,  0.0,  1.0,  0.0,  0.0,  1.0,  0.0,  0.0 };  //Right

             */
    }

    /// @brief Destructeur du maillage.
    ~Mesh() {
        delete[] vertices;
        delete[] texCoords;
        delete[] normals;
    }

    /// @brief Déplacement du maillage.
    /// @param Vector3d Vecteur de déplacement.
    void translate(Vector3d vector3d){
        for (int i = 0; i < vertexCount * 3; i += 3){
            vertices[i] += vector3d.x;
            vertices[i + 1] += vector3d.y;
            vertices[i + 2] += vector3d.z;
        }
    }

    /// @brief Fait une transformation au maillage par rapport à sa position.
    /// @param matrix Matrice de transformation.
    void localTransform(const Matrix44d& matrix){
        for (int i = 0; i < vertexCount * 3; i += 3){
            vertices[i] -= matrix.e14;
            vertices[i + 1] -= matrix.e24;
            vertices[i + 2] -= matrix.e34;

            double x = vertices[i];
            double y = vertices[i + 1];
            double z = vertices[i + 2];

            vertices[i] = matrix.e11 * x + matrix.e21 * y + matrix.e31 * z;
            vertices[i + 1] = matrix.e12 * x + matrix.e22 * y + matrix.e32 * z;
            vertices[i + 2] = matrix.e13 * x + matrix.e23 * y + matrix.e33 * z;
            
            x = normals[i];
            y = normals[i + 1];
            z = normals[i + 2];

            normals[i] = matrix.e11 * x + matrix.e21 * y + matrix.e31 * z;
            normals[i + 1] = matrix.e12 * x + matrix.e22 * y + matrix.e32 * z;
            normals[i + 2] = matrix.e13 * x + matrix.e23 * y + matrix.e33 * z;


            vertices[i] += matrix.e14;
            vertices[i + 1] += matrix.e24;
            vertices[i + 2] += matrix.e34;
        }
    }

    /// @brief Fait une transformation au maillage par rapport à la position {0, 0, 0}.
    /// @param matrix Matrice de transformation.
    void globalTransform(const Matrix44d& matrix){
        for (int i = 0; i < vertexCount * 3; i += 3){
            double x = vertices[i];
            double y = vertices[i + 1];
            double z = vertices[i + 2];

            vertices[i] = matrix.e11 * x + matrix.e21 * y + matrix.e31 * z;
            vertices[i + 1] = matrix.e12 * x + matrix.e22 * y + matrix.e32 * z;
            vertices[i + 2] = matrix.e13 * x + matrix.e23 * y + matrix.e33 * z;
            
            x = normals[i];
            y = normals[i + 1];
            z = normals[i + 2];

            normals[i] = matrix.e11 * x + matrix.e21 * y + matrix.e31 * z;
            normals[i + 1] = matrix.e12 * x + matrix.e22 * y + matrix.e32 * z;
            normals[i + 2] = matrix.e13 * x + matrix.e23 * y + matrix.e33 * z;
        }
    }
    
    /// @brief Dessine le maillage.
    void draw(){
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, vertices);
        glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
        glNormalPointer(GL_DOUBLE, 0, normals);
        glDrawArrays(GL_QUADS, 0, vertexCount);
    }
};