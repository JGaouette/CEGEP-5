#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>

#include "Window.hpp"
#include "Matrix44d.hpp"
#include "texture.hpp"
#include "font.hpp"

using namespace std;

class GLContext : public Window {
private:
    SDL_GLContext glContext;
    Matrix44d projectionMatrix;
public:
    /// @param title Titre de la fenêtre
    /// @param x  Position sur l'axe des x
    /// @param y Position sur l'axe des y
    /// @param width Largeur
    /// @param height Hauteur
    /// @param windowFlags Indicateurs de la fenêtre
    /// @param rendererFlags Indicateurs du gestion de rendu
    GLContext(const char* title = "", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 640, int height = 480, unsigned int windowFlags = 0) : Window(title, x, y, width, height, windowFlags | SDL_WINDOW_OPENGL){
        glContext = SDL_GL_CreateContext(sdlWindow);
        SDL_GL_SetSwapInterval(0);

        projectionMatrix.loadOrthographic(width, height);
        TTF_Init();

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    ~GLContext(){
        SDL_GL_DeleteContext(glContext);
    }

    void clear(){
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void draw() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(projectionMatrix.elements);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    } 

    void drawRect(Texture* texture, int x, int y, int w, int h){
        glBindTexture(GL_TEXTURE_2D, texture->id);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(x, y);
            glTexCoord2f(1, 0); glVertex2f(x + w, y);
            glTexCoord2f(1, 1); glVertex2f(x + w, y + h);
            glTexCoord2f(0, 1); glVertex2f(x, y + h);
        glEnd();
    }

    void drawText(Font* font, string text, SDL_Color color, int xPos, int yPos){
        font->setText(text, color);
        glBindTexture(GL_TEXTURE_2D, font->id);

        glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0); glVertex3d((double)(xPos), yPos, 0.0);
            glTexCoord2d(1.0, 0.0); glVertex3d((double)(xPos + font->width), yPos, 0.0);
            glTexCoord2d(1.0, 1.0); glVertex3d((double)(xPos + font->width), yPos + (double)font->height, 0.0);
            glTexCoord2d(0.0, 1.0); glVertex3d((double)(xPos), yPos + (double)font->height, 0.0);
        glEnd(); 
    }

    void drawQuad(Texture* texture, int topLeftPos, int topRightPos, int bottomRightPos, int bottomLeftPos){
        glBindTexture(GL_TEXTURE_2D, texture->id);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(topLeftPos, topRightPos);
            glTexCoord2f(1, 0); glVertex2f(topRightPos, topRightPos);
            glTexCoord2f(1, 1); glVertex2f(bottomRightPos, bottomRightPos);
            glTexCoord2f(0, 1); glVertex2f(bottomLeftPos, bottomLeftPos);
        glEnd();
    }

    void drawFPS(Font* font, string fps, SDL_Color color){
        font->setText(fps, color);
        glBindTexture(GL_TEXTURE_2D, font->id);

        glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0); glVertex3d(width - font->width, 0.0, 0.0);
            glTexCoord2d(1.0, 0.0); glVertex3d(width, 0.0, 0.0);
            glTexCoord2d(1.0, 1.0); glVertex3d(width, font->height, 0.0);
            glTexCoord2d(0.0, 1.0); glVertex3d(width - font->width, font->height, 0.0);
        glEnd(); 
    }

    void refresh(){
        SDL_GL_SwapWindow(sdlWindow);
    }
};