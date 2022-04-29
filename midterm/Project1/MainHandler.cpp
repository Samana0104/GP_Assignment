#include <string>
#include "MainHandler.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "ConstantDecl.h"
#include "GamePhaseIntro.h"

MainHandler::MainHandler(const char* _gameName, const SDL_Rect& _windowInfo, const double& _gameFramePerSecond)
	: gameFramePerSecond(_gameFramePerSecond), gameFrameVarForCalculation(0.0), gameStartCheck(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameWindow = SDL_CreateWindow(_gameName, _windowInfo.x, _windowInfo.y, _windowInfo.w, _windowInfo.h, 0);
	this->gameRender = SDL_CreateRenderer(this->gameWindow, -1, 0);
	SDL_initSystemMix();
	TTF_Init();
	CreateGamePhase();
	initGameData();
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
}

void MainHandler::initGameData() const
{

}

void MainHandler::gameStart()
{
	this->gameStartCheck = true;

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

	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameStop();
			break;
		case SDL_KEYDOWN:
			whenPressTheKeyboard();
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		}
	}
}

void MainHandler::gameStop()
{
	this->gameStartCheck = false;
}

void MainHandler::whenPressTheKeyboard() const
{

}

void MainHandler::updateGameData()
{

}

void MainHandler::drawGameRender()
{
	this->gamePhase[GAME_PHASE::INTRO]->drawGameRender(this->gameRender);

	SDL_RenderPresent(this->gameRender);
}

MainHandler::~MainHandler()
{
	SDL_DestroyWindow(this->gameWindow);
	SDL_Quit();
}