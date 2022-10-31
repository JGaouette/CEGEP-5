/// @file Mesh.hpp
/// @brief Maillage
/// @author Jérémy Gaouette

#pragma once

/// @class Mesh
/// @brief Maillage
class Mesh {
private:
    double *vertex, *texCoords;
    size_t vertexCount;

public:
    Mesh(double *vertex, double *texCoords, size_t vertexCount) {
        this->vertex = vertex;
        this->texCoords = texCoords;
        this->vertexCount = vertexCount;
    }

    /// @brief Déplacement du maillage.
    /// @param Vector3d Vecteur de déplacement.
    void translate(Vector3d vector3d){
        for (int i = 0; i < vertexCount * 3; i += 3){
            vertex[i] += vector3d.x;
            vertex[i + 1] += vector3d.y;
            vertex[i + 2] += vector3d.z;
        }
    }

    // Rotation, translation, mise à l'échelle
    void localTransform(Matrix44d& matrix){
        for (int i = 0; i < vertexCount * 3; i += 3){
            vertex[i] -= matrix.e14;
            vertex[i + 1] -= matrix.e24;
            vertex[i + 2] -= matrix.e34;

            double x = vertex[i];
            double y = vertex[i + 1];
            double z = vertex[i + 2];

            vertex[i] = matrix.e11 * x + matrix.e21 * y + matrix.e31 * z;
            vertex[i + 1] = matrix.e12 * x + matrix.e22 * y + matrix.e32 * z;
            vertex[i + 2] = matrix.e13 * x + matrix.e23 * y + matrix.e33 * z;


            vertex[i] += matrix.e14;
            vertex[i + 1] += matrix.e24;
            vertex[i + 2] += matrix.e34;
        }
    }

    void globalTransform(Matrix44d& matrix){
        //Vector3d vector3d = Vector3d({matrix.e41, matrix.e42, matrix.e43});
        
        //tranformation
        for (int i = 0; i < vertexCount * 3; i += 3){
            double x = vertex[i];
            double y = vertex[i + 1];
            double z = vertex[i + 2];

            vertex[i] = matrix.e11 * x + matrix.e21 * y + matrix.e31 * z;
            vertex[i + 1] = matrix.e12 * x + matrix.e22 * y + matrix.e32 * z;
            vertex[i + 2] = matrix.e13 * x + matrix.e23 * y + matrix.e33 * z;
        }
    }
    
    void draw(){
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, vertex);
        glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
        glDrawArrays(GL_QUADS, 0, vertexCount);
    }
};