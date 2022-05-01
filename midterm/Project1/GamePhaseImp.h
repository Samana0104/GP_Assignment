#pragma once

class GamePhaseImp
{
protected:
	GamePhaseImp() { }
public:
	virtual ~GamePhaseImp() { };
	virtual void updateGameData() = 0;
	virtual void drawGameRender() = 0;
	virtual void startGamePhase() = 0;
	virtual void pauseGamePhase() = 0;
};
