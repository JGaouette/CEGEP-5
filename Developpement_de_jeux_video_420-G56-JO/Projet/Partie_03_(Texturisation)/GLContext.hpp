/// @file GLContext.hpp
/// @brief Contexte OpenGL permettant d'afficher du contenue à l'écran
/// @author Jérémy Gaouette (jeremygaouette@gmail.com)

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>

#include "Window.hpp"
#include "Matrix44d.hpp"
#include "Texture.hpp"
#include "TTFont.hpp"

using namespace std;

/// @class GLContext
/// @brief Classe permettant de gérer l'affichage
class GLContext : public Window {
private:
    SDL_GLContext glContext; ///< Contexte OpenGL
    Matrix44d projectionMatrix; ///< Matrice de projection
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

    /// @brief Vider le contenue de la fenêtre
    void clear(){
        glClear(GL_COLOR_BUFFER_BIT);
    }

    /// @brief Définis les matrices de projection et de modèle
    void drawingParameters() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(projectionMatrix.elements);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    } 

    /// @brief Dessiner un rectangle
    /// @param texture Texture du rectangle
    /// @param xPos Position sur l'axe des x
    /// @param yPos Position sur l'axe des y
    /// @param width Largeur du rectangle
    /// @param height Hauteur du rectangle
    void drawRect(Texture* texture, int xPos, int yPos, int width, int height){
        glBindTexture(GL_TEXTURE_2D, texture->getId());
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(xPos, yPos);
            glTexCoord2f(1, 0); glVertex2f(xPos + width, yPos);
            glTexCoord2f(1, 1); glVertex2f(xPos + width, yPos + height);
            glTexCoord2f(0, 1); glVertex2f(xPos, yPos + height);
        glEnd();
    }

    /// @brief Dessiner un quadrilatère quelconque
    /// @param texture Texture du quadrilatère
    /// @param x1 Position sur l'axe des x du premier point
    /// @param y1 Position sur l'axe des y du premier point
    /// @param x2 Position sur l'axe des x du deuxième point
    /// @param y2 Position sur l'axe des y du deuxième point
    void drawQuad(Texture* texture, int topLeftPos, int topRightPos, int bottomRightPos, int bottomLeftPos){
        glBindTexture(GL_TEXTURE_2D, texture->getId());
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(topLeftPos, topRightPos);
            glTexCoord2f(1, 0); glVertex2f(topRightPos, topRightPos);
            glTexCoord2f(1, 1); glVertex2f(bottomRightPos, bottomRightPos);
            glTexCoord2f(0, 1); glVertex2f(bottomLeftPos, bottomLeftPos);
        glEnd();
    }

    /// @brief Dessiner les FPS
    /// @param texture Texture du texte
    void drawFPS(Texture* texture){
        glBindTexture(GL_TEXTURE_2D, texture->getId());
        glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0); glVertex3d(width - texture->getWidth(), 0.0, 0.0);
            glTexCoord2d(1.0, 0.0); glVertex3d(width, 0.0, 0.0);
            glTexCoord2d(1.0, 1.0); glVertex3d(width, texture->getHeight(), 0.0);
            glTexCoord2d(0.0, 1.0); glVertex3d(width - texture->getWidth(), texture->getHeight(), 0.0);
        glEnd(); 
    }

    /// @brief Dessiner un texte
    /// @param texture Texture du texte
    /// @param xPos Position sur l'axe des x
    /// @param yPos Position sur l'axe des y
    void drawText(Texture* texture, int xPos, int yPos){
        glBindTexture(GL_TEXTURE_2D, texture->getId());
        glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0); glVertex3d((double)(xPos), yPos, 0.0);
            glTexCoord2d(1.0, 0.0); glVertex3d((double)(xPos + texture->getWidth()), yPos, 0.0);
            glTexCoord2d(1.0, 1.0); glVertex3d((double)(xPos + texture->getWidth()), yPos + (double)texture->getHeight(), 0.0);
            glTexCoord2d(0.0, 1.0); glVertex3d((double)(xPos), yPos + (double)texture->getHeight(), 0.0);
        glEnd(); 
    }

    /// @brief Rafraichir la fenêtre
    void refresh(){
        SDL_GL_SwapWindow(sdlWindow);
    }
};