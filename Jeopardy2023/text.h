#pragma once
#include "texture.h"

class Text : public Texture
{
public:
	Text(SDL_Renderer* render, string path, SDL_Color color, int size, int wrap);
	~Text();

	bool loadFromRenderedText(std::string textureText);
protected:
	TTF_Font* gFont = NULL;
	SDL_Color gColor = { 0, 0, 0 };
	int gWrap;

};

