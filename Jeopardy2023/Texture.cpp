#include "Texture.h"

Texture::Texture(SDL_Renderer* render, string file) {
    path = file;
    gRenderer = render;
    SDL_Surface* loadedSurface = IMG_Load(file.c_str());
    if (loadedSurface == NULL) { cout << "Unable to load image: " << file << "\nSDL_image Error : " << IMG_GetError() << endl; }
    else {
        cout << "Successfully loaded image" << endl;
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) { cout << "Unable to create texture from " << file << "SDL Error :" << SDL_GetError() << endl; }
        SDL_FreeSurface(loadedSurface);
    }
};

Texture::~Texture() {
    SDL_DestroyTexture(newTexture);
    newTexture = NULL;
    IMG_Quit();
};

void Texture::render() {
    SDL_RenderCopy(gRenderer, newTexture, NULL, NULL);
    SDL_RenderPresent(gRenderer);
}