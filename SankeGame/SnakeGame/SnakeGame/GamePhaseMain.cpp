#include "GamePhaseMain.h"
#include "SDL_image.h"
#include <iostream>
GamePhaseMain::GamePhaseMain(SDL_Renderer* _gameRender) : gameRender(_gameRender)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/main.png");
	this->backgroundTexture = SDL_CreateTextureFromSurface(this->gameRender, tmpSurface);
	this->backgroundTextureRenderPos = { 0, 0, 1200, 800 };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/gameover.png");
	SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 255, 255, 255));
	this->gameoverTexture = SDL_CreateTextureFromSurface(this->gameRender, tmpSurface);
	this->gameoverTextureRenderPos = { 0, 0, 1200, 800 };
	SDL_FreeSurface(tmpSurface);
}

void GamePhaseMain::initPhaseDatas()
{
	if (this->gameBoard != NULL)
		delete this->gameBoard;

	this->gameBoard = new SnakeGameBoard(40, 20);
	this->nextGamePhase = GAME_PHASE::NONE;
}

void GamePhaseMain::handleEvents(const SDL_Event& gameEvent)
{
	switch (gameEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (gameEvent.button.button == SDL_BUTTON_LEFT)
		{
			if (this->gameBoard->isDyingSnake())
				this->nextGamePhase = GAME_PHASE::END;
		}
		break;
	}
}

void GamePhaseMain::updateDatas()
{
	this->gameBoard->moveSnake();
}

void GamePhaseMain::drawGameRender()
{
	SDL_RenderCopy(this->gameRender, this->backgroundTexture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
	this->gameBoard->drawGameBoard(this->gameRender);

	if (this->gameBoard->isDyingSnake())
	{
		SDL_RenderCopy(this->gameRender, this->gameoverTexture, &(this->gameoverTextureRenderPos), &(this->gameoverTextureRenderPos));
	}

	SDL_RenderPresent(this->gameRender);
}

GAME_PHASE GamePhaseMain::getNextGamePhase()
{
	return this->nextGamePhase;
}

GamePhaseMain::~GamePhaseMain()
{
	delete this->gameBoard;
	SDL_DestroyTexture(this->backgroundTexture);
	SDL_DestroyTexture(this->gameoverTexture);
}
