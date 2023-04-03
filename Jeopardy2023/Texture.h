#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include<stdio.h>
#include<iostream>
using namespace std;

class Texture {
public:
	Texture(SDL_Renderer* gRenderer, string file);
	~Texture();

	void render();
protected:
	SDL_Renderer* gRenderer = NULL;
	SDL_Texture* newTexture = NULL;
	string path;
};
