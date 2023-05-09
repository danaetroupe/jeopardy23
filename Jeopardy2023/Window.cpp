#include "window.h"

Window::Window(const char* name, int width, int height, int x, int y) {
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    gWindow = SDL_CreateWindow(name, x, y, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) { cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;}
    else {
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == NULL) { cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;}
        else { 
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); 
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
            }
        }
    }
};

Window::~Window() {
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
};

SDL_Renderer* Window::getRenderer() {
    return gRenderer;
};

int Window::getWidth() {
    return SCREEN_WIDTH;
};

int Window::getHeight() {
    return SCREEN_HEIGHT;
};