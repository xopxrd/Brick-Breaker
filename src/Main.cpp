#include <iostream>
#include <cmath>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Render.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

TTF_Font* font24;
SDL_Color white = { 255, 255, 255 };
bool mainMenu = true;

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0) 
		std::cout << "SDL init failed: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG init failed: " << SDL_GetError() << std::endl;

	TTF_Init();

	Render window("The Game!", SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Texture* theBoard = window.loadTexture("../../brickBreaker/res/board.png");
	SDL_Texture* theBrick = window.loadTexture("../../brickBreaker/res/brick.png");
	SDL_Texture* theBall = window.loadTexture("../../brickBreaker/res/ball.png");
	font24 = TTF_OpenFont("../../brickBreaker/res/fonts/cocogoose.ttf", 24);

	Entity ball(theBall);
	ball.setCurrentFrame(0, 0, 32, 32);
	ball.setY(240);
	ball.setX(400);

	Entity board(theBoard);
	board.setCurrentFrame(0, 1, 80, 7);
	board.setY(400);

	// brick
	Entity brick(theBrick);
	Entity emptyBrick[40] = {brick, brick, brick, brick, brick, brick, brick, brick, brick, brick,
							brick, brick, brick, brick, brick, brick, brick, brick, brick, brick,
							brick, brick, brick, brick, brick, brick, brick, brick, brick, brick,
							brick, brick, brick, brick, brick, brick, brick, brick, brick, brick};

	for (int i = 0; i < 40; i++)
		emptyBrick[i].setCurrentFrame(0, 2, 60, 20);

	// posisi x brick
	for (int i = 0; i < 10; i++)
		emptyBrick[i].setX(5 + i * 80);
	for (int i = 0; i < 10; i++)
		emptyBrick[i + 10].setX(5 + i * 80);
	for (int i = 0; i < 10; i++)
		emptyBrick[i + 20].setX(5 + i * 80);
	for (int i = 0; i < 10; i++)
		emptyBrick[i + 30].setX(5 + i * 80);

	// posisi y brick
	for (int i = 0; i < 10; i++)
		emptyBrick[i].setY(80);
	for (int i = 0; i < 10; i++)
		emptyBrick[i + 10].setY(110);
	for (int i = 0; i < 10; i++)
		emptyBrick[i + 20].setY(140);
	for (int i = 0; i < 10; i++)
		emptyBrick[i + 30].setY(170);


	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning){
		while (SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
				{
					gameRunning = false;
					break;
				}

				case SDL_MOUSEBUTTONDOWN:
				{
					if (mainMenu){
						if (event.button.button == SDL_BUTTON_LEFT && SDL_GetTicks() > 2500){
							mainMenu = false;
							SDL_ShowCursor(SDL_DISABLE);
						}
					}
					break;
				}
			}
		}

		if (mainMenu){
			if (SDL_GetTicks() < 2500){
				window.clear();
				window.renderCenter(0, sin(SDL_GetTicks()/100) * 2 - 4, "Brick Breaker!", font24, white);
				window.display();
			}else{
				window.clear();
				window.renderCenter(0, 90 + sin(SDL_GetTicks()/100) * 2, "Double Click to start", font24, white);
				window.renderCenter(0, -24, "press space to move the ball", font24, white);
				window.display();
			}
		}else{
			board.moveBoard();
			ball.ballMovement(board);

			if (ball.getY() > SCREEN_HEIGHT)
				gameRunning = false;

			for (int i = 0; i < 40; i++)
				ball.intersectWith(emptyBrick[i]);

			window.clear();
			window.renderBall(ball);
			window.renderBoard(board);
			for (int i = 0; i < 40; i++)
				window.renderBrick(emptyBrick[i]);

			window.display();
		}
	}
	
	window.cleanUp();
	SDL_Quit();
	
	return 0;
}