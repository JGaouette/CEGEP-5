/// @file Vector3d.hpp
/// @brief Vecteurs.
/// @author Thomas Laporte (thomas.laporte@hotmail.com)

#pragma once

/// @struct Vector3d
/// @brief Structure représantant un vecteur de 3 composantes réelles et opérations de vectorielles.
struct Vector3d {
    double x, y, z;   ///< Composantes (x, y, z).

    /// @param x Composante x.
    /// @param y Composante y.
    /// @param z Composante z.
    Vector3d(double x = 0.0, double y = 0.0, double z = 0.0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /// @brief Additionne deux vecteurs.
    /// @param v Vecteur à additionner.
    /// @return Vecteur additionné.
    Vector3d operator +(const Vector3d &v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    /// @brief Soustrait deux vecteurs.
    /// @param v Vecteur à soustraire.
    /// @return Vecteur soustrait.
    Vector3d operator -(const Vector3d &v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    /// @brief Multiplie notre vecteur avec un scalaire
    /// @param scalaire Le scalaire à calculer
    /// @return Le vecteur résultant de cette multiplication
    Vector3d operator *(int scalaire) {
        return Vector3d(this->x * scalaire, this->y * scalaire, this->z * scalaire);
    }

    /// @brief Effectue un produit vectoriel avec un autre vecteur
    /// @param v Le vecteur avec lequel nous ferons le produit vectoriel
    /// @return Le vecteur résultant du produit vectoriel
    Vector3d operator *(const Vector3d &v) {
        return Vector3d(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
    }

    /// @brief Effectue un produit scalaire avec un autre vecteur
    /// @param v Le vecteur avec lequel le calcul sera effectué
    /// @return Le scalaire
    double operator %(const Vector3d &v) {
        return this->x * v.x + this->y * v.y + this->z * v.z;    
    }

    /// @brief Calcule l'angle entre deux vecteurs
    /// @param v L'autre vecteur
    /// @return L'angle entre ces deux vecteurs
    double angle(Vector3d &v) {
        return acos((*this % v) / (this->norm() * v.norm()));
    }

    /// @brief Compare deux vecteurs pour savoir si ils sont égaux.
    /// @param o Le vecteur à comparer.
    /// @return L'égalité des deux vecteurs.
    bool operator==(const Vector3d& o) const {
        return abs(x - o.x) < std::numeric_limits<double>::epsilon() &&
               abs(y - o.y) < std::numeric_limits<double>::epsilon() &&
               abs(z - o.z) < std::numeric_limits<double>::epsilon();
    }

    /// @brief Compare deux vecteurs pour savoir si ils sont inégaux.
    /// @param o Le vecteur à comparer.
    /// @return L'inégalité des deux vecteurs.
    bool operator!=(const Vector3d& o) const {
        return !(*this == o);
    }

    /// @brief Vérifie si un vecteur est initialisé
    operator bool() const {
        return x != 0 || y != 0 || z != 0;        
    }

    /// @brief Normaliser le vecteur
    /// @return Vecteur normalisé
    Vector3d normalized(){
        return Vector3d(x / norm(), y / norm(), z / norm());
    }

    /// @brief Norme du vecteur
    /// @return Valeur de la norme
    double norm(){
        return sqrt(x * x + y * y + z * z);
    }
};