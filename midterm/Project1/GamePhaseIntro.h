#pragma once

#include "GamePhaseImp.h"
#include "SDL.h"

class GamePhaseIntro : public GamePhaseImp
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundRect;

	void createBackgroundTexture(SDL_Renderer* gameRender);
public:
	explicit GamePhaseIntro(SDL_Renderer* _gameRender);
	~GamePhaseIntro();

	virtual void updateGameData();
	virtual void drawGameRender(SDL_Renderer* _gameRender);
	virtual void whenPressTheKeyboard();
};