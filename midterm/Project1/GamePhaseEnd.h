#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include "GamePhaseImp.h"

class GamePhaseEnd : public GamePhaseImp
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundTexturePos;
	SDL_Renderer* gameRender;
	Mix_Music* backgroundMusic;

	void createBackgroundTexture();
	void createBackgroundMusic();
public:
	explicit GamePhaseEnd(SDL_Renderer* _gameRender);
	virtual ~GamePhaseEnd();

	virtual void updateGameData();
	virtual void drawGameRender();
	virtual void startGamePhase();
	virtual void pauseGamePhase();
};