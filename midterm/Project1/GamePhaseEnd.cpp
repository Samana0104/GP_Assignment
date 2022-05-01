#include "GamePhaseEnd.h"
#include "SDL_image.h"
#include "ConstantDecl.h"

#include <iostream>
GamePhaseEnd::GamePhaseEnd(SDL_Renderer* _gameRender) : gameRender(_gameRender)
{
	createBackgroundTexture();
	createBackgroundMusic();
}

void GamePhaseEnd::createBackgroundTexture()
{
	SDL_Surface* backgroundSurface = IMG_Load("../../resources/image/end_background.jpg");
	this->backgroundTexture = SDL_CreateTextureFromSurface(this->gameRender, backgroundSurface);
	this->backgroundTexturePos = { 0, 0, GAME_WINDOW_RECT::WIDTH, GAME_WINDOW_RECT::HEIGHT };
	SDL_FreeSurface(backgroundSurface);
}

void GamePhaseEnd::createBackgroundMusic()
{
	this->backgroundMusic = Mix_LoadMUS("../../resources/sound/end_theme.mp3");
}

void GamePhaseEnd::updateGameData()
{

}

void GamePhaseEnd::drawGameRender()
{
	SDL_RenderCopy(this->gameRender, this->backgroundTexture, &(this->backgroundTexturePos), &(this->backgroundTexturePos));
	SDL_RenderPresent(this->gameRender);
}


void GamePhaseEnd::startGamePhase()
{
	Mix_FadeInMusic(this->backgroundMusic, -1, 500);
}

void GamePhaseEnd::pauseGamePhase()
{
	Mix_HaltMusic();
}

GamePhaseEnd::~GamePhaseEnd()
{
	SDL_DestroyTexture(this->backgroundTexture);
}