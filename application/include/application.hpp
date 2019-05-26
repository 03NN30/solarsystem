#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_image.h>
#undef main
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <GL/glu.h>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

class Application {
public:
    Application();
    ~Application();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void updateFunc();
    void setupFunc();
    void renderFunc();
    void clean();

    bool running() { return isRunning; }
    SDL_Window* getWindow() { return gWindow; }
    SDL_GLContext getContext() { return gContext; }
    SDL_Surface* getSurface() { return gScreenSurface; }
    
private:
    bool isRunning;
    SDL_Window* gWindow = NULL;
    SDL_GLContext gContext;
    SDL_Surface* gScreenSurface = NULL;
};

#endif