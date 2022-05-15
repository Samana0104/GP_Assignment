#include "MainHandler.h"
#include "GamePhaseIntro.h"
#include "GamePhaseMain.h"
#include "GamePhaseEnd.h"
#include "TimerToDelay.h"

MainHandler::MainHandler(int windowPosX, int windowPosY, int windowWidth, int windowHeight) :
presentGamePhase(GAME_PHASE::INTRO), isPlayingGame(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameWindow = SDL_CreateWindow("SnakeGame", windowPosX, windowPosY, windowWidth, windowHeight, 0);
	this->gameRender = SDL_CreateRenderer(this->gameWindow, -1, 0);
	createGamePhase();
}

void MainHandler::createGamePhase()
{
	this->gamePhases[GAME_PHASE::INTRO] = new GamePhaseIntro(this->gameRender);
	this->gamePhases[GAME_PHASE::MAIN] = new GamePhaseMain(this->gameRender);
	this->gamePhases[GAME_PHASE::END] = new GamePhaseEnd(this->gameRender);
}

void MainHandler::gameStart()
{
	SDL_Event gameEvent;
	this->isPlayingGame = true;
	while (this->isPlayingGame)
	{
		SDL_Delay(10);
		changeGamePhase();

		if(getPresentGameEvent(gameEvent))
		{
			handleSystemEvents(gameEvent);
			this->gamePhases[this->presentGamePhase]->handleEvents(gameEvent);
		}

		this->gamePhases[this->presentGamePhase]->updateDatas();
		this->gamePhases[this->presentGamePhase]->drawGameRender();
	}
}

void MainHandler::changeGamePhase()
{
	GAME_PHASE nextGamePhase;
	nextGamePhase = this->gamePhases[this->presentGamePhase]->getNextGamePhase();

	if (nextGamePhase == GAME_PHASE::NONE)
		return;
	
	this->presentGamePhase = nextGamePhase;
	this->gamePhases[this->presentGamePhase]->initPhaseDatas();
}

bool MainHandler::getPresentGameEvent(SDL_Event& gameEvent) const
{
	if (!SDL_PollEvent(&gameEvent))
		return false;
	else
		return true;
}

void MainHandler::handleSystemEvents(SDL_Event& gameEvent)
{
	switch (gameEvent.type)
	{
	case SDL_QUIT:
		this->isPlayingGame = false;
		break;
	}
}

MainHandler::~MainHandler()
{
	delete this->gamePhases[GAME_PHASE::INTRO];
	delete this->gamePhases[GAME_PHASE::MAIN];
	delete this->gamePhases[GAME_PHASE::END];
	SDL_Quit();
}
