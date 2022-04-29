#pragma once

#include "SDL.h"

class GamePhaseImp
{
public:
	GamePhaseImp() { }
	virtual ~GamePhaseImp() { };
	virtual void updateGameData() = 0;
	virtual void drawGameRender(SDL_Renderer*) = 0;
	virtual void whenPressTheKeyboard() = 0;
};
