#pragma once

#include "GamePhaseInterface.h"
#include "SDL.h"

class MainHandler
{
private:
	SDL_Window* gameWindow;
	SDL_Renderer* gameRender;
	GamePhaseInterface* gamePhases[3];
	GAME_PHASE presentGamePhase;
	bool isPlayingGame;

	bool getPresentGameEvent(SDL_Event& gameEvent) const;

	void createGamePhase();
	void changeGamePhase();
	void handleSystemEvents(SDL_Event& gameEvent);

public:
	explicit MainHandler(int windowPosX, int windowPosY, int windowWidth, int windowHeight);
	
	void gameStart();

	~MainHandler();
};