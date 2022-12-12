/// @file Constants.hpp
/// @brief Définition des constantes.
/// @author Jean-Philippe Miguel-Gagnon

#pragma once

// Couleurs
#define COLOR_WHITE \
    { 255, 255, 255, 255 }   ///< Couleur blanche.
#define COLOR_BLACK \
    { 0, 0, 0, 255 }   ///< Couleur noire.
#define COLOR_GRAY \
    { 128, 128, 128, 255 }   ///< Couleur grise.
#define COLOR_DARK_GRAY \
    { 64, 64, 64, 255 }   ///< Couleur grise foncée.
#define COLOR_RED \
    { 255, 0, 0, 255 }   ///< Couleur rouge.
#define COLOR_GREEN \
    { 0, 255, 0, 255 }   ///< Couleur verte.
#define COLOR_LIGHT_GREEN \
    { 39, 217, 119, 255 }   ///< Couleur verte pâle.
#define COLOR_BLUE \
    { 0, 0, 255, 255 }   ///< Couleur bleue.
#define COLOR_LIGHT_BLUE \
    { 96, 197, 240, 255 }   ///< Couleur bleue pâle.
#define COLOR_BLUE_REPAIR \
    { 124, 171, 207, 255 }   ///< Couleur bleue de réparation.
#define COLOR_YELLOW \
    { 255, 255, 0, 255 }   ///< Couleur jaune.
#define COLOR_ORANGE_RED \
    { 242, 81, 41, 255 }   ///< Couleur orange-rouge.
#define COLOR_PRIMARY \
    { 128, 128, 255, 255 }   ///< Couleur primaire. (bleu)
#define COLOR_MIO_TEXT \
    { 252, 202, 3, 255 }   ///< Couleur du texte dans les mio. (Bleu pâle)
#define COLOR_MIO_BUTTON \
    { 0, 149, 255, 255 }   ///< Couleur du bouton dans les scènes de mio
#define COLOR_MIO_HOVER_BUTTON \
    { 66, 83, 168, 255 }   ///< Couleur du bouton dans les scènes de mio lorsqu'il est survolé

// Chemins
#define ASSSETS_PATH "../Assets/"            ///< Chemin vers les assets.
#define FONTS_PATH ASSSETS_PATH "Fonts/"     ///< Chemin vers les polices.
#define IMAGES_PATH ASSSETS_PATH "Images/"   ///< Chemin vers les images.

// Polices
#define DEFAULT_FONT "Segoe_UI.ttf"   ///< Police par défaut.
#define DEFAULT_FONT_SIZE 24          ///< Taille de police par défaut.

// Images
#define MISSING_IMAGE "missing.png"                    ///< Chemin vers l'image manquante.
#define MISSING_IMAGE_PATH IMAGES_PATH MISSING_IMAGE   ///< Chemin vers l'image manquante.

#define DEFAULT_COLOR COLOR_WHITE              ///< Couleur par défaut.
#define DEFAULT_BACKGROUND_COLOR COLOR_BLACK   ///< Couleur de fond par défaut.

// Paramètres de la fenêtre
#define DEFAULT_WINDOW_WIDTH 1280   ///< Largeur de la fenêtre.
#define DEFAULT_WINDOW_HEIGTH 720   ///< Hauteur de la fenêtre.

// Scènes
#define SCENE_COURS "Cours"                   ///< Nom de la scène du cours.
#define SCENE_TEST "Test"                     ///< Nom de la scène de test.
#define SCENE_MENU "MainMenu"                 ///< Nom de la scène du menu.
#define SCENE_OPTIONS "Options"               ///< Nom de la scène des options.
#define SCENE_NEW_GAME "NewGame"              ///< Nom de la scène de nouvelle partie.
#define SCENE_SAVE "Save"                     ///< Nom de la scène de sauvegarde.
#define SCENE_MIO "Mio"                       ///< Nom de la scène de mio.
#define SCENE_QUART "Quart"                   ///< Nom de la scène du quart de travail.
#define SCENE_POST_QUART "MioPostQuart"       ///< Nom de la scène de mio après le quart.
#define SCENE_SKILL_TREE "SkillTree"          ///< Nom de la scène de l'arbre de compétences.
#define SCENE_GAME_OVER "GameOver"            ///< Nom de la scène de game over.
#define SCENE_PAPER_BALL "PaperBall"          ///< Nom de la scène de paper ball.
#define SCENE_ESCAPE_GAME "EscapeGame"        ///< Nom de la scène de l'escape game.
#define SCENE_NETWORK "NetworkArchitecture"   ///< Nom de la scène de l'architecture réseau.
#define SCENE_RACE "ChairRace"                ///< Nom de la scène de la course de chaise.
#define SCENE_TERMINAL "Terminal"             ///< Nom de la scène du terminal.
