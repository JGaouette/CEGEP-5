#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Texture{
private:

public:
    unsigned int id;

    Texture(string path){
        SDL_Surface* sdlSurface = IMG_Load(path.c_str());
        if(sdlSurface == NULL){
            exit(1);
        }

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        // Apple
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
};


    
