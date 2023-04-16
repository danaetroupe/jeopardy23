#include "texture.h"

Texture::Texture(SDL_Renderer* render, string path, bool isText, SDL_Color color, int size, int wrap) {
    gRenderer = render;
    this->path = path;
    gColor = color;
    
    if (isText) { loadText(color, size, wrap); }
    else { loadImage(); }
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

bool Texture::loadText(SDL_Color color, int size, int wrap)
{
    bool success = true;

    gFont = TTF_OpenFont(path.c_str(), size);
    gColor = color;
    gWrap = wrap;
    if (gFont == NULL)
    {
        cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }
    return success;
}

bool Texture::loadFromRenderedText(std::string textureText) {
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(gFont, textureText.c_str(), gColor, gWrap);
    if (textSurface == NULL) { cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;}
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (newTexture == NULL) { cout << "Unable to create texture from rendered text! SDL Error: " <<  SDL_GetError() << endl;}
        else
        {
            //Get image dimensions
            width = textSurface->w;
            height = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    //Return success
    return newTexture != NULL;
};

int Texture::getWidth() {
    return width;
};

int Texture::getHeight() {
    return height;
};