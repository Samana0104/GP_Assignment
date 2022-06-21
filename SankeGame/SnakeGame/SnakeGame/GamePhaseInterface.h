#pragma once

#include "SDL.h"

enum GAME_PHASE
{
	NONE = -1,
	INTRO = 0,
	MAIN = 1,
	END = 2
};

class GamePhaseInterface
{
protected:
	GamePhaseInterface() { }
public:
	virtual ~GamePhaseInterface() { }

	virtual void initPhaseDatas() = 0;
	virtual void handleEvents(const SDL_Event&) = 0;
	virtual void updateDatas() = 0;
	virtual void drawGameRender() = 0;
	virtual GAME_PHASE getNextGamePhase() = 0;
};