#pragma once

#include "GamePhaseInterface.h"
#include "SnakeGameBoard.h"
#include "SDL.h"

class GamePhaseMain : public GamePhaseInterface
{
private:
	SDL_Renderer* gameRender;
	SDL_Texture* backgroundTexture;
	SDL_Texture* gameoverTexture;
	SDL_Rect backgroundTextureRenderPos;
	SDL_Rect gameoverTextureRenderPos;
	GAME_PHASE nextGamePhase;

	SnakeGameBoard * gameBoard;
public:
	explicit GamePhaseMain(SDL_Renderer* _gameRender);
	~GamePhaseMain();

	virtual void initPhaseDatas();
	virtual void handleEvents(const SDL_Event& gameEvent);
	virtual void updateDatas();
	virtual void drawGameRender();
	virtual GAME_PHASE getNextGamePhase();
};