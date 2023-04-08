#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Entity.hpp"

class Render {
public:
	Render(const char*, int, int);
	SDL_Texture* loadTexture(const char*);
	void renderBoard(Entity&);
	void renderBall(Entity&);
	void renderBrick(Entity&);
	void renderCenter(int, int, const char*, TTF_Font*, SDL_Color);
	void cleanUp();
	void display();
	void clear();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* tex;
};