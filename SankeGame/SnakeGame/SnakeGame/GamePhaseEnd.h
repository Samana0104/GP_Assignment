#pragma once

#include "GamePhaseInterface.h"
#include "SDL.h"
#include "Button.h"

class GamePhaseEnd : public GamePhaseInterface
{
private:
	SDL_Renderer* gameRender;
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundTextureRenderPos;
	Button* endButton;
	GAME_PHASE nextGamePhase;

	void checkAllButtonsInClickRange(const int& mousePosX, const int& mousePosY);
	void createStartButtonTexture();
public:
	explicit GamePhaseEnd(SDL_Renderer* _gameRender);
	~GamePhaseEnd();

	virtual void initPhaseDatas();
	virtual void handleEvents(const SDL_Event& gameEvent);
	virtual void updateDatas();
	virtual void drawGameRender();
	virtual GAME_PHASE getNextGamePhase();
};