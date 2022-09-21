/// @file Vector3d.hpp
/// @brief Vecteur à 3 dimensions
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#include <math.h>

/// @class Vector3d
/// @brief Vecteur à 3 dimensions
struct Vector3d{
    double x, y, z; ///< Position du vecteur

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
    /// @param vector Vecteur à additionner
    /// @return Vecteur additionné
    Vector3d operator+(const Vector3d& vector){
        return Vector3d(x + vector.x, y + vector.y, z + vector.z);
    }

    /// @brief Soustraire deux vecteurs
    /// @param vector Vecteur à soustraire
    /// @return Vecteur soustrait
    Vector3d operator-(const Vector3d& vector){
        return Vector3d(x - vector.x, y - vector.y, z - vector.z);
    }

    /// @brief Produit vectoriel
    /// @param vector Vecteur à multiplier  
    /// @return Le resultat du produit vectoriel
    Vector3d operator*(const Vector3d& vector){
        return Vector3d((vector.y * z) - (y * vector.z), (vector.z * x) - (z * vector.x), (vector.x * y) - (x * vector.y));
    }

    /// @brief Multiplier un vecteur par un scalaire
    /// @param scale Scalaire à multiplier
    /// @return Vecteur multiplié par le scalaire
    Vector3d operator*(const double scale){
        return Vector3d(x * scale, y * scale, z * scale);
    }

    /// @brief Produit scalaire
    /// @param vector Vecteur à multiplier
    /// @return Vecteur multiplié par le vecteur
    double operator%(const Vector3d& vector){
        return x * vector.x + y * vector.y + z * vector.z;
    }

    /// @brief Calculer l'angle entre deux vecteurs
    /// @param vector Vecteur à comparer
    /// @return Valeur de l'angle
    double angleBetween(Vector3d vector){
        return acos(*this % vector / (norm() * vector.norm()));
    }
};