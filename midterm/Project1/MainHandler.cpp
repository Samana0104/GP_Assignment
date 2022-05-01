#include <string>
#include "MainHandler.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "ConstantDecl.h"
#include "GamePhaseIntro.h"
#include "GamePhaseMain.h"
#include "GamePhaseEnd.h"

MainHandler::MainHandler(const char* _gameName, const SDL_Rect& _windowInfo, const double& _gameFramePerSecond)
	: PRESENT_PHASE(GAME_PHASE::INTRO), gameFramePerSecond(_gameFramePerSecond), gameFrameVarForCalculation(0.0), gameStartCheck(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameWindow = SDL_CreateWindow(_gameName, _windowInfo.x, _windowInfo.y, _windowInfo.w, _windowInfo.h, 0);
	this->gameRender = SDL_CreateRenderer(this->gameWindow, -1, 0);
	SDL_initSystemMix();
	TTF_Init();
	CreateGamePhase();
}

void MainHandler::SDL_initSystemMix() const 
{
	try
	{
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
			throw Exception("Mix_openAudio " + std::string(Mix_GetError()));
	}
	catch (Exception& e)
	{
		e.showErrorLog();
		exit(-1);
	}
}

void MainHandler::CreateGamePhase()
{
	this->gamePhase[GAME_PHASE::INTRO] = new GamePhaseIntro(this->gameRender);
	this->gamePhase[GAME_PHASE::MAIN] = new GamePhaseMain(this->gameRender);
	this->gamePhase[GAME_PHASE::END] = new GamePhaseEnd(this->gameRender);
}

void MainHandler::gameStart()
{
	this->gameStartCheck = true;
	this->gamePhase[this->PRESENT_PHASE]->startGamePhase();

	while (isGameStart())
	{
		if (delayProcessAboutFrame())
			continue;

		handleGameEvents();
		updateGameData();
		drawGameRender();
	}
}

bool MainHandler::isGameStart() const
{
	return this->gameStartCheck;
}

bool MainHandler::delayProcessAboutFrame()
{
	if (SDL_GetTicks() - this->gameFrameVarForCalculation < (MILLI_SECOND / this->gameFramePerSecond))
	{
		return true;
	}
	else
	{
		this->gameFrameVarForCalculation = SDL_GetTicks();
		return false;
	}
}

void MainHandler::handleGameEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
		handleGameEventType(event);
}

void MainHandler::handleGameEventType(const SDL_Event& eventType)
{
	switch (eventType.type)
	{
	case SDL_QUIT:
		gameStop();
		break;
	case SDL_MOUSEBUTTONDOWN:
		whenPressTheMouse(eventType);
		break;
	}
}

void MainHandler::gameStop()
{
	this->gameStartCheck = false;
}

void MainHandler::whenPressTheMouse(const SDL_Event& eventType)
{
	if (eventType.button.button == SDL_BUTTON_RIGHT)
		changeGamePhase();
}

void MainHandler::changeGamePhase()
{
	this->gamePhase[this->PRESENT_PHASE]->pauseGamePhase();

	switch (this->PRESENT_PHASE)
	{
	case GAME_PHASE::INTRO:
		this->PRESENT_PHASE = GAME_PHASE::MAIN;
		break;
	case GAME_PHASE::MAIN:
		this->PRESENT_PHASE = GAME_PHASE::END;
		break;
	case GAME_PHASE::END:
		this->PRESENT_PHASE = GAME_PHASE::INTRO;
		break;
	}

	this->gamePhase[this->PRESENT_PHASE]->startGamePhase(); // pause phase -> change phase -> start phase
}

void MainHandler::updateGameData()
{
	this->gamePhase[this->PRESENT_PHASE]->updateGameData();
}

void MainHandler::drawGameRender()
{
	this->gamePhase[this->PRESENT_PHASE]->drawGameRender();
}

MainHandler::~MainHandler()
{
	for (int i = 0; i < GAME_PHASE::COUNT; i++)
		delete this->gamePhase[i];

	Mix_CloseAudio();
	SDL_DestroyWindow(this->gameWindow);
	SDL_Quit();
}