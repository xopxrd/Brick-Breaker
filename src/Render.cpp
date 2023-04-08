#include <iostream>
#include "Render.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

Render::Render(const char* title, int w, int h)
:window(NULL), renderer(NULL)
{
	Uint32 flags = SDL_WINDOW_SHOWN;
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);
	if (window == NULL)
		std::cout << "Window init failed: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
}

SDL_Texture* Render::loadTexture(const char* filepath){
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filepath);

	if (texture == NULL)
		std::cout << "failed to init texture: " << SDL_GetError() << std::endl;

	return texture;
}

void Render::renderBoard(Entity& entity){
	SDL_Rect src;
	SDL_Rect dst;

	src.x = entity.getCurrentFrame().x;
	src.y = entity.getCurrentFrame().y;
	src.w = entity.getCurrentFrame().w;
	src.h = entity.getCurrentFrame().h;

	dst.x = entity.getX();
	dst.y = entity.getY();
	dst.w = entity.getCurrentFrame().w;
	dst.h = entity.getCurrentFrame().h;

	SDL_RenderCopy(renderer, entity.getTex(), &src, &dst);
}

void Render::renderBall(Entity& entity){
	SDL_Rect src;
	SDL_Rect dst;

	src.x = entity.getCurrentFrame().x;
	src.y = entity.getCurrentFrame().y;
	src.w = entity.getCurrentFrame().w;
	src.h = entity.getCurrentFrame().h;

	dst.x = entity.getX();
	dst.y = entity.getY();
	dst.w = entity.getCurrentFrame().w / 2;
	dst.h = entity.getCurrentFrame().h / 2;

	SDL_RenderCopy(renderer, entity.getTex(), &src, &dst);
}

void Render::renderBrick(Entity& entity){
	SDL_Rect src;
	SDL_Rect dst;

	src.x = entity.getCurrentFrame().x;
	src.y = entity.getCurrentFrame().y;
	src.w = entity.getCurrentFrame().w;
	src.h = entity.getCurrentFrame().h;

	dst.x = entity.getX();
	dst.y = entity.getY();
	dst.w = entity.getCurrentFrame().w;
	dst.h = entity.getCurrentFrame().h;

	SDL_RenderCopy(renderer, entity.getTex(), &src, &dst);
}

void Render::renderCenter(int p_x, int p_y, const char* p_text, TTF_Font* font, SDL_Color textColor){
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h; 

	SDL_Rect dst;
	dst.x = SCREEN_WIDTH/2 - src.w/2 + p_x;
	dst.y = SCREEN_HEIGHT/2 - src.h/2 + p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
}

void Render::cleanUp(){
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(renderer);
}

void Render::display(){
	SDL_RenderPresent(renderer);
}

void Render::clear(){
	SDL_RenderClear(renderer);
}