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
	Texture(SDL_Renderer* gRenderer, string path);
	~Texture();

	void render(int x, int y, int w = NULL, int h = NULL);
	
	void loadImage();

	int getWidth();
	int getHeight();
protected:
	SDL_Renderer* gRenderer = NULL;
	SDL_Texture* newTexture = NULL;
	string path;

	int width = 0;
	int height = 0;
};
