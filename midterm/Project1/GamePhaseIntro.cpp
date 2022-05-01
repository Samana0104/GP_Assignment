#include "GamePhaseIntro.h"
#include "SDL_image.h"
#include "ConstantDecl.h"

GamePhaseIntro::GamePhaseIntro(SDL_Renderer * _gameRender) :gameRender(_gameRender)
{
	createBackgroundTexture();
	createBackgroundMusic();
}

void GamePhaseIntro::createBackgroundTexture()
{
	SDL_Surface * backgroundSurface = IMG_Load("../../resources/image/intro_background.jpg");
	this->backgroundTexture = SDL_CreateTextureFromSurface(this->gameRender, backgroundSurface);
	this->backgroundTexturePos = { 0, 0, GAME_WINDOW_RECT::WIDTH, GAME_WINDOW_RECT::HEIGHT };
	SDL_FreeSurface(backgroundSurface);
}

void GamePhaseIntro::createBackgroundMusic()
{
	this->backgroundMusic = Mix_LoadMUS("../../resources/sound/intro_theme.mp3");
}

void GamePhaseIntro::updateGameData()
{

}

void GamePhaseIntro::drawGameRender()
{
	SDL_RenderCopy(this->gameRender, this->backgroundTexture, &(this->backgroundTexturePos), &(this->backgroundTexturePos));
	SDL_RenderPresent(this->gameRender);
}

void GamePhaseIntro::startGamePhase()
{
	Mix_FadeInMusic(this->backgroundMusic, -1, 500);
}

void GamePhaseIntro::pauseGamePhase()
{
	Mix_HaltMusic();
}

GamePhaseIntro::~GamePhaseIntro()
{
	Mix_FreeMusic(this->backgroundMusic);
	SDL_DestroyTexture(this->backgroundTexture);
}