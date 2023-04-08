#pragma once

#include "SDL.H"
#include "SDL_image.h"

class Entity {
public:
	Entity(SDL_Texture*);
	float getX();
	float getY();
	void setX(float);
	void setY(float);
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	void setCurrentFrame(int, int, int, int);
	void moveBoard();
	void ballMovement(Entity&);
	void intersectWith(Entity&);

private:
	SDL_Texture* EntityTex;
	SDL_Rect currentFrame;
	bool click = true;
	float xPos, yPos;
	float velocityX = 0;
	float velocityY = 0;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
};