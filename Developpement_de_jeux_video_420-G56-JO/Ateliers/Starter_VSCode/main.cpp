#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_opengl.h>

#include "iostream"

using namespace std;

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_EVERYTHING)); // initialize
    cout << "Necessite la librairie SDLT2" << endl;


  //! Pour faire du 2D avec SDL
  //SDL_Window* sdlWindow = SDL_CreateWindow("Ma première fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_RESIZABLE);
  //SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Pour du 2D
  //SDL_RenderClear(sdlRenderer);
  // TODO: Draw
  //SDL_RenderPresent(sdlRenderer);

  //! Pour faire du 3D avec opengl
  SDL_Window* sdlWindow = SDL_CreateWindow("Ma première fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  SDL_GLContext glContext = SDL_GL_CreateContext(sdlWindow);
  SDL_Event sdlEvent; //Contient les informations d'un Event - Unique
  
  bool isOpen = true;
  while(isOpen){
    glClear(GL_COLOR_BUFFER_BIT);
    // TODO: Draw
    SDL_GL_SwapWindow(sdlWindow);  
  
    //* Gestion des évènements
    while(SDL_PollEvent(&sdlEvent)){
      switch(sdlEvent.type) {
        case SDL_QUIT:
          isOpen = false;
          break;
      }
    }

    //* Gestion des mises à jours

    //* Gestion de l'affichage
  }
    
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(sdlWindow);  
  SDL_Quit();

  return 0;
}
