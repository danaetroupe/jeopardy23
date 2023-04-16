#include "rectangle.h"

Rectangle::Rectangle(SDL_Renderer* gRenderer, int color[4], int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	SDL_SetRenderDrawColor(gRenderer, color[0], color[1], color[2], color[3]);
	SDL_Rect fillRect = { x, y, width, height };
	SDL_RenderFillRect(gRenderer, &fillRect);
}

Rectangle::~Rectangle() {
	x = 0;
	y = 0;
}