#include "Entity.hpp"
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

Entity::Entity(SDL_Texture* tex)
:EntityTex(tex)
{
}

void Entity::setCurrentFrame(int x, int y, int w, int h){
	currentFrame.x = x;
	currentFrame.y = y;
	currentFrame.w = w;
	currentFrame.h = h;
}

SDL_Rect Entity::getCurrentFrame(){
	return currentFrame;
}

SDL_Texture* Entity::getTex(){
	return EntityTex;
}

float Entity::getX(){
	return xPos;
}

float Entity::getY(){
	return yPos;
}

void Entity::setX(float x){
	xPos = x;
}

void Entity::setY(float y){
	yPos = y;
}

void Entity::moveBoard(){
	int x, y;
	SDL_GetMouseState(&x, &y);
	xPos = x - 40;
	if (xPos <= 0)
		xPos = 0;
	if (xPos >= SCREEN_WIDTH - 80)
		xPos = SCREEN_WIDTH - 80;
}

void Entity::ballMovement(Entity& board){
	if (click == true && keystates[SDL_SCANCODE_SPACE]){
			velocityY -= 5;
		click = false;
	}

	setX(xPos + velocityX);
	setY(yPos + velocityY);

	if (velocityY <= -5)
		velocityY = -5;
	if (velocityX <= -5)
		velocityX = -5;

	if (yPos <= 0)
		velocityY *= -1;
	if (xPos <= 0 || xPos >= SCREEN_WIDTH - 16)
		velocityX *= -1;

	if (yPos >= board.getY() - 16 && xPos + 16 >= board.getX() && xPos <= board.getX() + 80){
		velocityY *= -1;
			
			// bagian kiri board
			if (xPos < board.getX() + 8)
				velocityX = -5;
			else if (xPos + 8 < board.getX() + 16)
				velocityX = -4;
			else if (xPos + 8 < board.getX() + 24)
				velocityX = -3;
			else if (xPos + 8 < board.getX() + 32)
				velocityX = -2;
			else if (xPos + 8 < board.getX() + 40)
				velocityX = -1;

			// bagian kanan board
			else if (xPos + 8 < board.getX() + 48)
				velocityX = 1;
			else if (xPos + 8 < board.getX() + 56)
				velocityX = 2;
			else if (xPos + 8 < board.getX() + 64)
				velocityX = 3;
			else if (xPos + 8 < board.getX() + 72)
				velocityX = 4;
			else
				velocityX = 5;
	}
}

void Entity::intersectWith(Entity& brick){
	if (yPos <= brick.getY() + 20 && yPos + 16 >= brick.getY() && xPos + 16 >= 			// atas
		brick.getX() && xPos <= brick.getX() + 60)
	{
		velocityY *= -1;
		brick = nullptr;
	}
	
	else if (yPos + 16 >= brick.getY() && yPos <= brick.getY() + 20 && xPos + 16 >=		// bawah
		brick.getX() && xPos <= brick.getX() + 60)
	{
		velocityY *= -1;
		brick = nullptr;
	}
	
	else if (xPos <= brick.getX() + 60 && xPos + 16 >= brick.getX() && yPos <=			// kiri
		brick.getY() + 20 && yPos + 16 >= brick.getY())
	{
		velocityX *= -1;
		brick = nullptr;
	}

	else if (xPos + 16 >= brick.getX() && xPos <= brick.getX() + 60 && yPos <=			// kanan
		brick.getY() + 20 && yPos + 16 >= brick.getY())
	{
		velocityX *= -1;
		brick = nullptr;
	}
}