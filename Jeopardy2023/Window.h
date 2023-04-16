#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
using namespace std;

class Window
{
public:
	Window(const char* name);
	~Window();

	SDL_Renderer* getRenderer();
	int getWidth();
	int getHeight();
private:
	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;

	const int SCREEN_WIDTH = 980;
	const int SCREEN_HEIGHT = 540;

};

