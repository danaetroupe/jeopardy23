#include "texture.h"

Texture::Texture(SDL_Renderer* render, string path) {
    gRenderer = render;
    this->path = path;
};


Texture::~Texture() {
    SDL_DestroyTexture(newTexture);
    newTexture = NULL;
    IMG_Quit();
};

void Texture::loadImage() {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) { cout << "Unable to load image: " << path << "\nSDL_image Error : " << IMG_GetError() << endl; }
    else {
        cout << "Successfully loaded image" << endl;
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) { cout << "Unable to create texture from " << path << "SDL Error :" << SDL_GetError() << endl; }
        SDL_FreeSurface(loadedSurface);
    }
};

void Texture::render(int x, int y, int w, int h) {
    if (w == NULL) { w = width; }
    if (h == NULL) { h = height; }
    SDL_Rect renderQuad = { x, y, w, h };
    SDL_RenderCopy(gRenderer, newTexture, NULL , &renderQuad);
    SDL_RenderPresent(gRenderer);
}


int Texture::getWidth() {
    return width;
};

int Texture::getHeight() {
    return height;
};