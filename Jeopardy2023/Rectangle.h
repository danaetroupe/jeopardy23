#pragma once
#include <string>
#include <SDL.h>
using namespace std;

class Rectangle
{
public:
	Rectangle(SDL_Renderer* gRenderer, int color[3], int x, int y, int width, int height);
	~Rectangle();
	
	bool checkCoords(int x, int y);
	
	void writeText(string text);
	void setButton(bool state);
private:
	bool active = false;
	int x, y, width, height;
};

