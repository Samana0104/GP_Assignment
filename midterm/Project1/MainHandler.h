#pragma once

#include "SDL.h"
#include "Exception.h"
#include "GamePhaseImp.h"
#include "ConstantDecl.h"

class MainHandler
{
private:
	SDL_Window* gameWindow;
	SDL_Renderer* gameRender;
	GamePhaseImp * gamePhase[GAME_PHASE::COUNT];
	double gameFramePerSecond, gameFrameVarForCalculation;
	bool gameStartCheck; // 1 = be working, 0 = not be working
	
	MainHandler& operator=(const MainHandler&) { };
	void SDL_initSystemMix() const;
	void CreateGamePhase();
	void initGameData() const;
	bool delayProcessAboutFrame();
	void handleGameEvents();
	void gameStop();
	void whenPressTheKeyboard() const;
	void updateGameData();
	void drawGameRender();
public:
	explicit MainHandler(const char* _gameName, const SDL_Rect & _windowInfo, const double& _gameFramePerSecond = 60.0);
	~MainHandler();
	
	void gameStart();
	bool isGameStart() const;
};