/// @file Texture.hpp
/// @brief Texture pour afficher divers éléments
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

using namespace std;

/// @class Texture
/// @brief Classe permettant de générer une texture
class Texture{
private:
    int width, height; ///< Largeur et hauteur de la texture
    unsigned int id; ///< Identifiant de la texture
    
public:

    /// @brief Constructeur d'une texture d'image
    /// @param path Chemin de l'image
    Texture(string path){
        SDL_Surface* sdlSurface = IMG_Load(path.c_str());
        if(sdlSurface == NULL){
            exit(1);
        }

        width = sdlSurface->w;
        height = sdlSurface->h;

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 
                                    0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);

 
        SDL_FreeSurface(sdlSurface);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    /// @brief Constructeur d'une texture de texte
    /// @param sdlSurface Surface de texte
    Texture(SDL_Surface* sdlSurface){
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        width = sdlSurface->w;
        height = sdlSurface->h;

        #ifdef __APPLE__
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 
                                        0, GL_BGRA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
        #else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 
                                        0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
        #endif
 
        SDL_FreeSurface(sdlSurface);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    ~Texture(){
        glDeleteTextures(1, &id);
    }

    /// @brief Retourne la largeur de la texture
    /// @return Largeur
    int getWidth(){
        return width;
    }

    /// @brief Retourne la hauteur de la texture
    /// @return Hauteur
    int getHeight(){
        return height;
    }

    /// @brief Retourne l'identifiant de la texture
    /// @return Identifiant
    int getId(){
        return id;
    }
};


    
