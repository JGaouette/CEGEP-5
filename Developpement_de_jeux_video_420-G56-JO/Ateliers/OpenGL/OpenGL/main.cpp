#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_main.h"
#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

int main(int argc, char* argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);
  
  SDL_Window* sdlWindow = SDL_CreateWindow("OpenGL 4.3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
  SDL_GLContext sdlGLContext = SDL_GL_CreateContext(sdlWindow);
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  glewExperimental = true;
  glewInit();
  
  glEnable(GL_DEPTH_TEST);
  
  SDL_Event sdlEvent;
  bool isOpen = true;
  while (isOpen) {
    while (SDL_PollEvent(&sdlEvent))
      isOpen = sdlEvent.type != SDL_QUIT;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapWindow(sdlWindow);
  }
  
  SDL_GL_DeleteContext(sdlGLContext);
  SDL_DestroyWindow(sdlWindow);
  
  SDL_Quit();

  return 0;
}

