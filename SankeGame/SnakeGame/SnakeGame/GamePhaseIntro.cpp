#include "GamePhaseIntro.h"
#include "SDL_image.h"

GamePhaseIntro::GamePhaseIntro(SDL_Renderer* _gameRender) : gameRender(_gameRender)
{
	createStartButtonTexture();

	SDL_Surface* tmpSurface = IMG_Load("../../resources/intro.png");
	this->backgroundTexture = SDL_CreateTextureFromSurface(this->gameRender, tmpSurface);
	this->backgroundTextureRenderPos = { 0, 0, 1200, 800 };
	SDL_FreeSurface(tmpSurface);
}

void GamePhaseIntro::initPhaseDatas()
{
	this->nextGamePhase = GAME_PHASE::NONE;
}

void GamePhaseIntro::createStartButtonTexture()
{
	SDL_Rect srcPos, renderPos;
	SDL_Surface* buttonSurface = IMG_Load("../../resources/startbutton.png");
	SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(this->gameRender, buttonSurface);
	srcPos = { 0, 0, 560, 160 };
	renderPos = { 320, 550, 560, 160 };
	this->startButton = new Button(srcPos, renderPos, buttonTexture);
	SDL_FreeSurface(buttonSurface);
}

void GamePhaseIntro::handleEvents(const SDL_Event& gameEvent)
{
	switch (gameEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (gameEvent.button.button == SDL_BUTTON_LEFT)
			checkAllButtonsInClickRange(gameEvent.button.x, gameEvent.button.y);
		break;
	}
}

void GamePhaseIntro::checkAllButtonsInClickRange(const int& mousePosX, const int& mousePosY)
{
	if (this->startButton->isMouseClickInRange(mousePosX, mousePosY))
		this->nextGamePhase = GAME_PHASE::MAIN;
}

void GamePhaseIntro::updateDatas()
{

}

void GamePhaseIntro::drawGameRender()
{
	SDL_RenderCopy(this->gameRender, this->backgroundTexture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
	SDL_RenderCopy(this->gameRender, this->startButton->getButtonImage(), &(this->startButton->getSrcPos()), &(this->startButton->getRenderPos()));
	SDL_RenderPresent(this->gameRender);
}

GAME_PHASE GamePhaseIntro::getNextGamePhase()
{
	return this->nextGamePhase;
}

GamePhaseIntro::~GamePhaseIntro()
{
	delete this->startButton;
	SDL_DestroyTexture(this->backgroundTexture);
}
