/// @file Vector3d.hpp
/// @brief Vecteur à 3 dimensions
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#include <math.h>

/// @class Vector3d
/// @brief Vecteur à 3 dimensions
struct Vector3d{
    double x, y, z;

    /// @brief Constructeur de vecteur
    /// @param x Position sur l'axe des x
    /// @param y Position sur l'axe des y
    /// @param z Position sur l'axe des z
    Vector3d(double x, double y, double z){
        this->x = x; 
        this->y = y; 
        this->z = z;
    }

    /// @brief Norme du vecteur
    /// @return Valeur de la norme
    double norm(){
        return sqrt(x * x + y * y + z * z);
    }
    
    /// @brief Normaliser le vecteur
    /// @return Vecteur normalisé
    Vector3d normalized(){
        return Vector3d(x / norm(), y / norm(), z / norm());
    }

    /// @brief Additionner deux vecteurs
    /// @param v Vecteur à additionner
    /// @return Vecteur additionné
    Vector3d operator+(const Vector3d& v){
        return Vector3d(x + v.x, y + v.y, z + v.z);
    }

    /// @brief Soustraire deux vecteurs
    /// @param v Vecteur à soustraire
    /// @return Vecteur soustrait
    Vector3d operator-(const Vector3d& v){
        return Vector3d(x - v.x, y - v.y, z - v.z);
    }

    /// @brief Produit scalaire
    /// @param v Vecteur à multiplier
    /// @return Vecteur multiplié par le vecteur
    Vector3d operator*(const Vector3d& v){
        return Vector3d((v.y * z) - (y * v.z), (v.z * x) - (z * v.x), (v.x * y) - (x * v.y));
    }

    /// @brief Multiplier un vecteur par un scalaire
    /// @param n Scalaire à multiplier
    /// @return Vecteur multiplié par le scalaire
    Vector3d operator*(const double n){
        return Vector3d(x * n, y * n, z * n);
    }

    /// @brief Produit vectoriel
    /// @param v Vecteur à multiplier  
    /// @return Le resultat du produit vectoriel
    double operator%(const Vector3d& v){
        return x * v.x + y * v.y + z * v.z;
    }

    /// @brief Calculer l'angle entre deux vecteurs
    /// @param v Vecteur à comparer
    /// @return Valeur de l'angle
    double angleBetween(Vector3d v){
        return acos(*this % v / (norm() * v.norm()));
    }
};