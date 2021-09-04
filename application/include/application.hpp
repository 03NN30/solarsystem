#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#undef main
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL_opengl.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>

class Application {
public:
  Application();
  ~Application();

  void init(const char *title, int xpos, int ypos, int width, int height,
            bool fullscreen);

  void handleEvents();
  void updateFunc();
  void setupFunc();
  void renderFunc();
  void clean();

  bool running() { return isRunning; }
  SDL_Window *getWindow() { return gWindow; }
  SDL_GLContext getContext() { return gContext; }
  SDL_Surface *getSurface() { return gScreenSurface; }

private:
  bool isRunning;
  SDL_Window *gWindow = NULL;
  SDL_GLContext gContext;
  SDL_Surface *gScreenSurface = NULL;
};

#endif
