/// @file Chrono.hpp
/// @brief Chrono
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#pragma once

#include <chrono>

using namespace std::chrono;

/// @class Chrono
/// @brief Classe permettant de gérer un chronomètre
class Chrono {
public:
    steady_clock::time_point start; ///< Temps initial du chronomètre

    /// @brief Démarre le chronomètre
    void startTimer(){
        start = steady_clock::now();
    }

    /// @brief Obtention du temps écoulé depuis le début du chronomètre
    /// @return Temps écoulé
    double delta(){
        return duration_cast<nanoseconds>(steady_clock::now() - start).count() / 1000000000.0;
    }

    /// @brief Réinitialise le chronomètre
    void reset(){
        start = steady_clock::now();
    }
};