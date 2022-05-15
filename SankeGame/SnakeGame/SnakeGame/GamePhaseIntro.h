#pragma once

#include "GamePhaseInterface.h"
#include "SDL.h"
#include "Button.h"

class GamePhaseIntro : public GamePhaseInterface
{
private:
	SDL_Renderer* gameRender;
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundTextureRenderPos;
	Button * startButton;
	GAME_PHASE nextGamePhase;

	void checkAllButtonsInClickRange(const int& mousePosX, const int& mousePosY);
	void createStartButtonTexture();
public:
	explicit GamePhaseIntro(SDL_Renderer* _gameRender);
	~GamePhaseIntro();

	virtual void initPhaseDatas();
	virtual void handleEvents(const SDL_Event& gameEvent);
	virtual void updateDatas();
	virtual void drawGameRender();
	virtual GAME_PHASE getNextGamePhase();
};