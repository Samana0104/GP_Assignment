#include "GamePhaseEnd.h"
#include "SDL_image.h"

GamePhaseEnd::GamePhaseEnd(SDL_Renderer* _gameRender) : gameRender(_gameRender)
{
	createStartButtonTexture();

	SDL_Surface* tmpSurface = IMG_Load("../../resources/end.jpg");
	this->backgroundTexture = SDL_CreateTextureFromSurface(this->gameRender, tmpSurface);
	this->backgroundTextureRenderPos = { 0, 0, 1200, 800 };
	SDL_FreeSurface(tmpSurface);
}

void GamePhaseEnd::initPhaseDatas()
{
	this->nextGamePhase = GAME_PHASE::NONE;
}

void GamePhaseEnd::createStartButtonTexture()
{
	SDL_Rect srcPos, renderPos;
	SDL_Surface* buttonSurface = IMG_Load("../../resources/endbutton.png");
	SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(this->gameRender, buttonSurface);
	srcPos = { 0, 0, 560, 160 };
	renderPos = { 320, 550, 560, 160 };
	this->endButton = new Button(srcPos, renderPos, buttonTexture);
	SDL_FreeSurface(buttonSurface);
}

void GamePhaseEnd::handleEvents(const SDL_Event& gameEvent)
{
	switch (gameEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (gameEvent.button.button == SDL_BUTTON_LEFT)
			checkAllButtonsInClickRange(gameEvent.button.x, gameEvent.button.y);
		break;
	}
}

void GamePhaseEnd::checkAllButtonsInClickRange(const int& mousePosX, const int& mousePosY)
{
	if (this->endButton->isMouseClickInRange(mousePosX, mousePosY))
		this->nextGamePhase = GAME_PHASE::INTRO;
}

void GamePhaseEnd::updateDatas()
{

}

void GamePhaseEnd::drawGameRender()
{
	SDL_RenderCopy(this->gameRender, this->backgroundTexture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
	SDL_RenderCopy(this->gameRender, this->endButton->getButtonImage(), &(this->endButton->getSrcPos()), &(this->endButton->getRenderPos()));
	SDL_RenderPresent(this->gameRender);
}

GAME_PHASE GamePhaseEnd::getNextGamePhase()
{
	return this->nextGamePhase;
}

GamePhaseEnd::~GamePhaseEnd()
{
	delete this->endButton;
	SDL_DestroyTexture(this->backgroundTexture);
}
