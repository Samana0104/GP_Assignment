#include "GamePhaseIntro.h"
#include "SDL_image.h"
#include "ConstantDecl.h"

GamePhaseIntro::GamePhaseIntro(SDL_Renderer * _gameRender)
{
	createBackgroundTexture(_gameRender);
}

void GamePhaseIntro::createBackgroundTexture(SDL_Renderer* gameRender)
{
	SDL_Surface * backgroundSurface = IMG_Load("../../resources/image/intro_background.jpg");
	this->backgroundTexture = SDL_CreateTextureFromSurface(gameRender, backgroundSurface);
	this->backgroundRect = { 0, 0, GAME_WINDOW_RECT::WIDTH, GAME_WINDOW_RECT::HEIGHT };
	SDL_FreeSurface(backgroundSurface);
}

void GamePhaseIntro::updateGameData()
{

}

void GamePhaseIntro::drawGameRender(SDL_Renderer* gameRender)
{
	SDL_RenderCopy(gameRender, this->backgroundTexture, &(this->backgroundRect), &(this->backgroundRect));
}

void GamePhaseIntro::whenPressTheKeyboard()
{

}

GamePhaseIntro::~GamePhaseIntro()
{
	SDL_DestroyTexture(this->backgroundTexture);
}