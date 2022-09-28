#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "SDL2/SDL_ttf.h"

using namespace std;

class Font {
private:
    TTF_Font* ttfFont;

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
    unsigned int id;
    string text = "";
    int width, height;

    Font(string path, int size){
        ttfFont = TTF_OpenFont(path.c_str(), size);
        if(ttfFont == NULL){
            exit(1);
        }

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        //! Si c'est mauvais mettre dans set text

    }

    ~Font(){
        TTF_CloseFont(ttfFont);
    }

    void setText(string text, SDL_Colour colour){
        this->text = text;
        SDL_Surface* sdlSurface = TTF_RenderText_Blended(ttfFont, text.c_str(), colour);
        if(sdlSurface == NULL){
            exit(1);
        }

        patchMisalignement(sdlSurface);
        glBindTexture(GL_TEXTURE_2D, id);
    
        width = sdlSurface->w;
        height = sdlSurface->h;
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 
                                    0, GL_BGRA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
         
        SDL_FreeSurface(sdlSurface);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
};

#pragma once
    
