/// @file Font.hpp
/// @brief Générateur de texture de texte
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "SDL2/SDL_ttf.h"
#include "texture.hpp"

using namespace std;

/// @class TTFont
/// @brief Classe permettant de générer une texture de texte
class TTFont {
private:
    unsigned int id; ///< Identifiant de la texture
    TTF_Font* ttfFont; ///< Police de caractères
    int size; ///< Taille de la police de caractères

    /// @brief Correctif pour réalligner le tableau de pixel générer par TTF_RenderText_Blended
    /// @param sdlSurface Surface de texte
    void patchMisalignement(SDL_Surface* sdlSurface){
        unsigned int realPitch = sdlSurface->w * sdlSurface->format->BytesPerPixel;
        unsigned char* srcPointer = (unsigned char*)sdlSurface->pixels;
        unsigned char* dstPointer = srcPointer;
        for(size_t i = 0; i < sdlSurface->h; i++){
            memmove(dstPointer, srcPointer, realPitch);
            dstPointer += realPitch;
            srcPointer += sdlSurface->pitch;
        }
        sdlSurface->pitch = realPitch;
    }

public:
    string path; ///< Chemin de la police de caractères
    string text = ""; ///< Texte à afficher
    int width, height; ///< Largeur et hauteur de la texture

    /// @brief Constructeur d'une texture de texte
    /// @param path Chemin de la police de caractères
    /// @param size Taille de la police de caractères
    TTFont(string path, int size){
        ttfFont = TTF_OpenFont(path.c_str(), size);
        if(ttfFont == NULL){
            exit(1);
        }
    }

    ~TTFont(){
        TTF_CloseFont(ttfFont);
    }

    /// @brief Génère la texture de texte
    /// @param text Texte à afficher
    /// @param color Couleur du texte
    SDL_Surface* renderText(string text, SDL_Colour colour){
        SDL_Surface* sdlSurface = TTF_RenderText_Blended(ttfFont, text.c_str(), colour);
        if(sdlSurface == NULL){
            exit(1);
        }

        patchMisalignement(sdlSurface);

        return sdlSurface;
    }

    /// @brief Retourne la taille de police de caractères
    /// @return Taille de la police de caractères
    int getSize(){
        return size;
    }
};