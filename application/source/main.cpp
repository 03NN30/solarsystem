#include "utils.hpp"
#include "application.hpp"
#include "glewInc.hpp"
#include "render.hpp"
#include "gui.hpp"
#include <iostream>

Application *app = nullptr;

static bool flag = true;
static bool isLoading = true;

SDL_Surface* gLoadImg1 = NULL;

SDL_Surface* loadSurface(std::string path) {
	// The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		// Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, app->getSurface()->format, NULL );
		if(optimizedSurface == NULL) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

int loadThread(void* data) {
    gLoadImg1 = loadSurface((resource_path + "textures/loadingScreen/matrix.png").c_str());

    while(isLoading) {
        SDL_BlitSurface( gLoadImg1, NULL, app->getSurface(), NULL );
		SDL_UpdateWindowSurface(app->getWindow());
    }
    isLoading = false;
    SDL_FreeSurface(gLoadImg1);
    gLoadImg1 = NULL;
    
    return 0;
}

int main() {
    
    app = new Application();
    app->init("Solar System", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, fullScreen);    

    // start loading screen on new thread
    int data = 101; 
    SDL_Thread* threadID = SDL_CreateThread(loadThread, "Loading Screen Thread", (void*)data); 

    app->setupFunc();
    isLoading = false;
    while(app->running()) {
        if(!isLoading) {
            if (flag) {
                SDL_DetachThread(threadID);
                flag = false;
            }
            app->handleEvents();
            app->updateFunc();     
            app->renderFunc();
        }
    }
    app->clean();

    SDL_DetachThread(threadID);

    return 0;
}