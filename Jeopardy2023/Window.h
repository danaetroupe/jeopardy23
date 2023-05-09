#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
using namespace std;

class Window
{
public:
	Window(const char* name, int width, int height, int x, int y);
	~Window();

	SDL_Renderer* getRenderer();
	int getWidth();
	int getHeight();
private:
	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;

	int SCREEN_WIDTH = 1920;
	int SCREEN_HEIGHT = 1080;

};

