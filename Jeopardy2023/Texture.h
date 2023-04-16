#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include<stdio.h>
#include<iostream>
#include <SDL_ttf.h>
using namespace std;

class Texture {
public:
	Texture(SDL_Renderer* gRenderer, string path, bool isText = false, SDL_Color color = { 0, 0, 0 }, int size = 16, int wrap = 0);
	~Texture();

	void render(int x, int y, int w = NULL, int h = NULL);
	
	bool loadText(SDL_Color color, int size, int wrap);
	void loadImage();
	
	bool loadFromRenderedText(string text);

	int getWidth();
	int getHeight();
protected:
	SDL_Renderer* gRenderer = NULL;
	SDL_Texture* newTexture = NULL;
	string path;

	int width = 0;
	int height = 0;

	TTF_Font* gFont = NULL;
	SDL_Color gColor = { 0, 0, 0 };
	int gWrap;
};
