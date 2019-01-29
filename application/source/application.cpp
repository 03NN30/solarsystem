#include "application.hpp"
#include "render.hpp"
#include "controls.hpp"
#include "gui.hpp"

#include <iostream>

int frame = 0, time, timebase = 0, fps; 

Application::Application() {}

Application::~Application() {}

void Application::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_GRABBED;
    } else {
        flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_GRABBED;
    }
    
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        isRunning = false;
        std::cerr << "ERROR::SDL::INIT\n" << SDL_GetError() << std::endl;
    } else {
        // use OpenGL 3.1 core
	    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
        // create window
        gWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (gWindow == nullptr) {
            isRunning = false;
            std::cerr << "ERROR::SDL::WINDOW\n" << SDL_GetError() << std::endl;
        } else {
            //
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                isRunning = false;
                std::cerr << "ERROR::SDL::INIT_PNG\n" << SDL_GetError() << std::endl;
            } else {
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
            //
            gContext = SDL_GL_CreateContext(gWindow);
            if(gContext == NULL) {
                isRunning = false;
	        	std::cerr << "ERROR::GL::CONTEXT\n" << SDL_GetError() << std::endl;
	        } else {
                // initialize GLEW
	            glewExperimental = GL_TRUE; 
                GLenum glewError = glewInit();
	            if( glewError != GLEW_OK ) {
                    isRunning = false;
	            	std::cerr << "ERROR::GLEW::INIT\n" << SDL_GetError() << std::endl;
	            } else {
                    isRunning = true; 
                    
                    // Setup Dear ImGui context
                    IMGUI_CHECKVERSION();
                    ImGui::CreateContext();
                    ImGuiIO& io = ImGui::GetIO(); (void)io;
                
                    // Setup Platform/Renderer bindings
                    ImGui_ImplSDL2_InitForOpenGL(gWindow, gContext);
                    ImGui_ImplOpenGL3_Init("#version 330 core");
                    ImGui::StyleColorsDark();
                }
            }
        }
    }
}

void Application::setupFunc() {
    setup();
}

void Application::handleEvents() {
    controller();
}

void Application::updateFunc() {
    glViewport(0, 0, screenWidth, screenHeight);
    update();
}

void Application::renderFunc() {    
    // fps counter in window title
    frame++;
	time = SDL_GetTicks();

	if (time - timebase > 1000) {
		fps = frame * 1000.0 / (time - timebase);
	 	timebase = time;
		frame = 0;
	}
    
    std::string fpstitle = "Solar System @" + std::to_string(fps) + "FPS";

    SDL_SetWindowTitle(gWindow, fpstitle.c_str());  
    SDL_GL_SwapWindow(gWindow);

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(gWindow);
    ImGui::NewFrame();
    
    render();
    isRunning = drawMenu(); 
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());  
}

void Application::clean() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

