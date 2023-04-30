#include "text.h"

Text::Text(SDL_Renderer* render, string path, SDL_Color color, int size, int wrap) : Texture(render, path) {
    gFont = TTF_OpenFont(path.c_str(), size);
    gColor = color;
    gWrap = wrap;
    if (gFont == NULL)
    {
        cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << endl;
    }
}

Text::~Text() {
    SDL_DestroyTexture(newTexture);
    newTexture = NULL;
    IMG_Quit();
};

bool Text::loadFromRenderedText(std::string textureText) {
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(gFont, textureText.c_str(), gColor, gWrap);
    if (textSurface == NULL) { cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl; }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (newTexture == NULL) { cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl; }
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
