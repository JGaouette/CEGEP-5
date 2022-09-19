/// @file Matrix44.hpp
/// @brief Création de matrice 44d
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#define e11 elements[0]
#define e12 elements[1]
#define e13 elements[2]
#define e14 elements[3]
#define e21 elements[4]
#define e22 elements[5]
#define e23 elements[6]
#define e24 elements[7]
#define e31 elements[8]
#define e32 elements[9]
#define e33 elements[10]
#define e34 elements[11]
#define e41 elements[12]
#define e42 elements[13]
#define e43 elements[14]
#define e44 elements[15]

#include "Vector3d.hpp"

/// @class Matrix44d
/// @brief Structure permettant de représenter une matrice 4x4
struct Matrix44d{
    double elements[16]; ///< Elements de la matrice

    /// @brief Création d'une matrice identité
    void loadIdentity(){
        e11 = e22 = e33 = e44 = 1.0;
        e12 = e13 = e14 = e21 = e23 = e24 = e31 = e32 = e34 = e41 = e42 = e43 = 0.0;
    }

    /// @brief Transposer la matrice
    void transpose(){
        double tmp;
        tmp = e12; e12 = e21; e21 = tmp;
        tmp = e13; e13 = e31; e31 = tmp;
        tmp = e14; e14 = e41; e41 = tmp;
        tmp = e23; e23 = e32; e32 = tmp;
        tmp = e24; e24 = e42; e42 = tmp;
        tmp = e34; e34 = e43; e43 = tmp;
    }

    /// @brief Création d'une matrice à l'échelle
    /// @param x Mise à l'échelle sur l'axe des x
    /// @param y Mise à l'échelle sur l'axe des y
    /// @param z Mise à l'échelle sur l'axe des z
    void loadScale(double x, double y, double z){
        e11 = x;
        e22 = y;
        e33 = z;
        e44 = 1.0;
        e12 = e13 = e14 = e21 = e23 = e24 = e31 = e32 = e34 = e41 = e42 = e43 = 0.0;
    }

    /// @brief Création d'une matrice à l'échelle à partir d'un vecteur
    /// @param scale Vecteur de mise à l'échelle
    void loadScale(Vector3d scale){
        loadScale(scale.x, scale.y, scale.z);
    }

    /// @brief Création d'une matrice de rotation sur l'axe des x
    /// @param angle Angle de rotation en radian
    void loadXRotation(double angle){
        e22 = cos(angle);
        e23 = -sin(angle);
        e32 = sin(angle);
        e33 = cos(angle);        
        e11 = e44 = 1.0;
        e12 = e13 = e14 = e21 = e24 = e31 = e34 = e41 = e42 = e43 = 0.0;
    }

    /// @brief Création d'une matrice de rotation sur l'axe des y
    /// @param angle Angle de rotation en radian
    void loadYRotation(double angle){
        e11 = cos(angle);
        e13 = sin(angle);
        e31 = -sin(angle);
        e33 = cos(angle);
        e22 = e44 = 1.0;
        e12 = e14 = e21 = e23 = e24 = e32 = e34 = e41 = e42 = e43 = 0.0;
    }
    
    /// @brief Création d'une matrice de rotation sur l'axe des z
    /// @param angle Angle de rotation en radian
    void loadZRotation(double angle){
        e11 = cos(angle);
        e12 = -sin(angle);
        e21 = sin(angle);
        e22 = cos(angle);  
        e33 = e44 = 1.0;
        e13 = e14 = e23 = e24 = e31 = e32 = e34 = e41 = e42 = e43 = 0.0;
    }

    /// @brief Création d'une matrice de rotation sur un axe normalisé
    /// @param angle Angle de rotation en radian
    void loadRotationOnNormalizedAxis(double angle, Vector3d axis){
        double c = cos(angle);
        double s = sin(angle);
        double t = 1.0 - c;
        double x = axis.x;
        double y = axis.y;
        double z = axis.z;

        e11 = t * x * x + c;
        e12 = t * x * y - s * z;
        e13 = t * x * z + s * y;
        e14 = 0.0;

        e21 = t * x * y + s * z;
        e22 = t * y * y + c;
        e23 = t * y * z - s * x;
        e24 = 0.0;

        e31 = t * x * z - s * y;
        e32 = t * y * z + s * x;
        e33 = t * z * z + c;
        e34 = 0.0;

        e41 = e42 = e43 = 0.0;
        e44 = 1.0;
    }

    /// @brief Création de matrice de rotation sur un axe donné 
    /// @param angle Angle de rotation en radian
    /// @param axis Vecteur de l'axe de rotation
    void loadRotationOnAxis(double angle, Vector3d axis){
        if(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z == 1)
            loadRotationOnNormalizedAxis(angle, axis);
        else
            loadRotationOnNormalizedAxis(angle, axis.normalized());
    }

    /// @brief Addition de deux matrices
    /// @param matrix Matrice à additionner
    /// @return Matrice résultante
    Matrix44d operator+(Matrix44d matrix){
        Matrix44d result;
        for(int i = 0; i < 16; i++){
            result.elements[i] = elements[i] + matrix.elements[i];
        }
        return result;
    }

    /// @brief Soustraction de deux matrices
    /// @param matrix Matrice à soustraire
    /// @return Matrice résultante
    Matrix44d operator-(Matrix44d matrix){
        Matrix44d result;
        for(int i = 0; i < 16; i++){
            result.elements[i] = elements[i] - matrix.elements[i];
        }
        return result;
    }

    /// @brief Multiplication de deux matrices
    /// @param matrix Matrice à multiplier
    /// @return Matrice résultante
    Matrix44d operator*(const Matrix44d& matrix) const {
        Matrix44d result;
        result.e11 = e11 * matrix.e11 + e12 * matrix.e21 + e13 * matrix.e31 + e14 * matrix.e41;
        result.e12 = e11 * matrix.e12 + e12 * matrix.e22 + e13 * matrix.e32 + e14 * matrix.e42;
        result.e13 = e11 * matrix.e13 + e12 * matrix.e23 + e13 * matrix.e33 + e14 * matrix.e43;
        result.e14 = e11 * matrix.e14 + e12 * matrix.e24 + e13 * matrix.e34 + e14 * matrix.e44;
        result.e21 = e21 * matrix.e11 + e22 * matrix.e21 + e23 * matrix.e31 + e24 * matrix.e41;
        result.e22 = e21 * matrix.e12 + e22 * matrix.e22 + e23 * matrix.e32 + e24 * matrix.e42;
        result.e23 = e21 * matrix.e13 + e22 * matrix.e23 + e23 * matrix.e33 + e24 * matrix.e43;
        result.e24 = e21 * matrix.e14 + e22 * matrix.e24 + e23 * matrix.e34 + e24 * matrix.e44;
        result.e31 = e31 * matrix.e11 + e32 * matrix.e21 + e33 * matrix.e31 + e34 * matrix.e41;
        result.e32 = e31 * matrix.e12 + e32 * matrix.e22 + e33 * matrix.e32 + e34 * matrix.e42;
        result.e33 = e31 * matrix.e13 + e32 * matrix.e23 + e33 * matrix.e33 + e34 * matrix.e43;
        result.e34 = e31 * matrix.e14 + e32 * matrix.e24 + e33 * matrix.e34 + e34 * matrix.e44;
        result.e41 = e41 * matrix.e11 + e42 * matrix.e21 + e43 * matrix.e31 + e44 * matrix.e41;
        result.e42 = e41 * matrix.e12 + e42 * matrix.e22 + e43 * matrix.e32 + e44 * matrix.e42;
        result.e43 = e41 * matrix.e13 + e42 * matrix.e23 + e43 * matrix.e33 + e44 * matrix.e43;
        result.e44 = e41 * matrix.e14 + e42 * matrix.e24 + e43 * matrix.e34 + e44 * matrix.e44;
        return result;
    }
};