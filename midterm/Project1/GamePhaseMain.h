#pragma once

#include "SDL.h"
#include "GamePhaseImp.h"
#include "ConstantDecl.h"
#include "Marine.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <vector>

class GamePhaseMain : public GamePhaseImp
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundTexturePos;
	SDL_Renderer* gameRender;

	/* Marine */
	Marine * marinePlayer;
	SDL_Texture* marineTexture;
	SDL_Rect marineMoveMotion[MARINE::MOVE_ACTION::COUNT][MARINE::MOVE_MOTION_COUNT];
	int presentMarineMoveMotion;
	MARINE::MOVE_ACTION presentMarineMoveAction;
	bool presentMarineMoveActionInverse;

	/* box */
	SDL_Texture* boxTexture;
	SDL_Rect boxTexturePos;
	SDL_Rect boxCreationPos;
	Mix_Chunk* boxBgmOfDestruction;
	bool boxCreationCheck;

	/* tank */
	SDL_Texture* tankTexture;
	SDL_Texture* tankBullet;
	SDL_Rect tankBulletTexturePos;
	SDL_Rect tankPos;
	std::vector<SDL_Rect> tankBulletPos;
	std::vector<TANK::SHOOTING_ACTION> tankBulletDirection;

	SDL_Rect tankShootingMotion[TANK::SHOOTING_ACTION::COUNT];
	Mix_Chunk* tankBgmOfGetIn;
	Mix_Chunk* tankBgmOfGetOut;
	Mix_Chunk* tankBgmOfShooting;
	TANK::SHOOTING_ACTION presentTankShootingAction;
	bool tankInMarineCheck;

	/* font */
	TTF_Font* fontInGame;
	SDL_Texture* fontBulletTexture;
	SDL_Texture* fontVehicleTexture;
	SDL_Rect fontBulletTexturePos;
	SDL_Rect fontVehicleTexturePos;
	SDL_Color fontColor;

	void createBackgroundTexture();
	void whenPressTheKeyboard();
	void whenDontPressTheKeyboard();

	/* Marine */
	void createMarineTexture();
	void moveMarine(MARINE::MOVE_ACTION, bool inverse);
	void actMarineMotion();
	bool isMarineMoveActionInverse() const;
	
	/* box */
	void createBoxTextureOrMix();
	void createBox();
	bool isBoxCreated() const;
	void getBulletToBox();

	/* tank */
	void createTankTextureOrMix();
	bool isMarineGettingInTank() const;
	void getInOrgetOutTank();
	void tankShooting(TANK::SHOOTING_ACTION presentAction);

	/* font */
	void createFont();
	void createFontTexture();

public:
	explicit GamePhaseMain(SDL_Renderer* _gameRender);
	virtual ~GamePhaseMain();

	virtual void updateGameData();
	virtual void drawGameRender();
	virtual void startGamePhase();
	virtual void pauseGamePhase();
};