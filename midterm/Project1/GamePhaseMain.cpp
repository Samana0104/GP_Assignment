#include "GamePhaseMain.h"
#include "SDL_image.h"
#include "ConstantDecl.h"
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <atlstr.h>
#include <string>

GamePhaseMain::GamePhaseMain(SDL_Renderer* _gameRender) : gameRender(_gameRender), presentMarineMoveMotion(0), 
presentMarineMoveAction(MARINE::MOVE_ACTION::DOWN), presentMarineMoveActionInverse(false), boxCreationCheck(false), tankInMarineCheck(false),
presentTankShootingAction(TANK::SHOOTING_ACTION::UP)
{
	srand(static_cast<unsigned int>(time(NULL)));

	createBackgroundTexture();
	createMarineTexture();
	createBackgroundTexture();
	createBoxTextureOrMix();
	createTankTextureOrMix();
	createFont();
}

void GamePhaseMain::createBackgroundTexture()
{
	SDL_Surface* backgroundSurface = IMG_Load("../../resources/image/main_background.png");
	this->backgroundTexture = SDL_CreateTextureFromSurface(this->gameRender, backgroundSurface);
	SDL_FreeSurface(backgroundSurface);
	this->backgroundTexturePos = { 0, 0, GAME_WINDOW_RECT::WIDTH, GAME_WINDOW_RECT::HEIGHT };
}

void GamePhaseMain::createMarineTexture()
{
	SDL_Surface* marineSurface = IMG_Load("../../resources/image/marine.png");
	this->marineTexture = SDL_CreateTextureFromSurface(this->gameRender, marineSurface);
	SDL_FreeSurface(marineSurface);

	this->marineMoveMotion[MARINE::MOVE_ACTION::UP][0] = { 0, 256, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::UP][1] = { 0, 320, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::UP][2] = { 0, 384, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::UP][3] = { 0, 448, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::UP][4] = { 0, 512, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::UP][5] = { 0, 576, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::UP][6] = { 0, 640, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::UP][7] = { 0, 703, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::UP][8] = { 0, 767, 27, 31 };

	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_UP][0] = { 257, 256, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_UP][1] = { 257, 320, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_UP][2] = { 257, 384, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_UP][3] = { 257, 448, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_UP][4] = { 257, 512, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_UP][5] = { 257, 576, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_UP][6] = { 257, 640, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_UP][7] = { 257, 703, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_UP][8] = { 257, 767, 27, 31 };
	
	this->marineMoveMotion[MARINE::MOVE_ACTION::RIGHT][0] = { 513, 256, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::RIGHT][1] = { 513, 320, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::RIGHT][2] = { 513, 384, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::RIGHT][3] = { 513, 448, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::RIGHT][4] = { 513, 512, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::RIGHT][5] = { 513, 576, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::RIGHT][6] = { 513, 640, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::RIGHT][7] = { 513, 703, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::RIGHT][8] = { 513, 767, 27, 31 };

	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_DOWN][0] = { 771, 256, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_DOWN][1] = { 771, 320, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_DOWN][2] = { 771, 384, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_DOWN][3] = { 771, 448, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_DOWN][4] = { 771, 512, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_DOWN][5] = { 771, 576, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_DOWN][6] = { 771, 640, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_DOWN][7] = { 771, 703, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DIAGONAL_RIGHT_DOWN][8] = { 771, 767, 27, 31 };

	this->marineMoveMotion[MARINE::MOVE_ACTION::DOWN][0] = { 1024, 256, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DOWN][1] = { 1024, 320, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DOWN][2] = { 1024, 384, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DOWN][3] = { 1024, 448, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DOWN][4] = { 1024, 512, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DOWN][5] = { 1024, 576, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DOWN][6] = { 1024, 640, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DOWN][7] = { 1024, 703, 27, 31 };
	this->marineMoveMotion[MARINE::MOVE_ACTION::DOWN][8] = { 1024, 767, 27, 31 };
}

void GamePhaseMain::createBoxTextureOrMix()
{
	SDL_Surface* boxSurface = IMG_Load("../../resources/image/box.png");
	this->boxTexture = SDL_CreateTextureFromSurface(this->gameRender, boxSurface);
	SDL_FreeSurface(boxSurface);

	this->boxBgmOfDestruction = Mix_LoadWAV("../../resources/sound/wooden_box_break.mp3");
	this->boxTexturePos = { 0, 0, 255, 255 };
}

void GamePhaseMain::createTankTextureOrMix()
{
	SDL_Surface* tmpTextureSurface = IMG_Load("../../resources/image/bullet.png");
	this->tankBullet = SDL_CreateTextureFromSurface(this->gameRender, tmpTextureSurface);
	SDL_FreeSurface(tmpTextureSurface);

	tmpTextureSurface = IMG_Load("../../resources/image/tank.png");
	this->tankTexture = SDL_CreateTextureFromSurface(this->gameRender, tmpTextureSurface);
	SDL_FreeSurface(tmpTextureSurface);

	this->tankShootingMotion[TANK::SHOOTING_ACTION::UP] = { 24, 20, 48, 56 };
	this->tankShootingMotion[TANK::SHOOTING_ACTION::RIGHT] = { 206, 31, 68, 45 };
	this->tankShootingMotion[TANK::SHOOTING_ACTION::DOWN] = { 408, 20, 48, 56 };
	this->tankBulletTexturePos = { 64, 64, 97, 97 };
	this->tankPos = { 550, 350, 100, 100 };

	this->tankBgmOfGetIn = Mix_LoadWAV("../../resources/sound/get_in_tank.wav");
	this->tankBgmOfGetOut = Mix_LoadWAV("../../resources/sound/get_out_tank.wav");
	this->tankBgmOfShooting = Mix_LoadWAV("../../resources/sound/shooting.wav");

}

void GamePhaseMain::createFont()
{
	this->fontInGame = TTF_OpenFont("../../resources/font/abcd.ttf", 50);
}

void GamePhaseMain::updateGameData()
{
	this->whenPressTheKeyboard();
}

void GamePhaseMain::drawGameRender()
{
	SDL_Rect presentMarineRect = this->marinePlayer->getPresentRect();

	SDL_RenderCopy(this->gameRender, this->backgroundTexture, &(this->backgroundTexturePos), &(this->backgroundTexturePos));

	if (isBoxCreated())
		SDL_RenderCopy(this->gameRender, this->boxTexture, &(this->boxTexturePos), &(this->boxCreationPos));

	if (this->presentTankShootingAction == TANK::SHOOTING_ACTION::LEFT)
		SDL_RenderCopyEx(this->gameRender, this->tankTexture, &(this->tankShootingMotion[TANK::SHOOTING_ACTION::RIGHT]),
			&(tankPos), 0, 0, SDL_FLIP_HORIZONTAL);
	else
		SDL_RenderCopy(this->gameRender, this->tankTexture, &(this->tankShootingMotion[this->presentTankShootingAction]), &(this->tankPos));

	if (!isMarineGettingInTank())
	{
		if (isMarineMoveActionInverse())
			SDL_RenderCopyEx(this->gameRender, this->marineTexture, &(this->marineMoveMotion[this->presentMarineMoveAction][this->presentMarineMoveMotion]),
				&(presentMarineRect), 0, 0, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopy(this->gameRender, this->marineTexture, &(this->marineMoveMotion[this->presentMarineMoveAction][this->presentMarineMoveMotion]), &(presentMarineRect));
	}
	else
	{
		SDL_RenderCopy(this->gameRender, this->fontVehicleTexture, NULL, &(this->fontVehicleTexturePos));
	}

	if (this->tankBulletPos.size() > 0)
	{
		for (int i=0; i< this->tankBulletPos.size(); ++i)
		{
			SDL_RenderCopy(this->gameRender, this->tankBullet, NULL, &(this->tankBulletPos[i]));

			switch (this->tankBulletDirection[i])
			{
			case TANK::SHOOTING_ACTION::UP:
				this->tankBulletPos[i].y -= 15;

				if (this->tankBulletPos[i].y < 0)
				{
					this->tankBulletPos.erase(this->tankBulletPos.begin() + i);
					this->tankBulletDirection.erase(this->tankBulletDirection.begin() + i);
					i--;
					continue;
				}
				break;

			case TANK::SHOOTING_ACTION::RIGHT:
				this->tankBulletPos[i].x += 15;

				if (this->tankBulletPos[i].x > GAME_WINDOW_RECT::WIDTH)
				{
					this->tankBulletPos.erase(this->tankBulletPos.begin() + i);
					this->tankBulletDirection.erase(this->tankBulletDirection.begin() + i);
					i--;
					continue;
				}
				break;

			case TANK::SHOOTING_ACTION::DOWN:
				this->tankBulletPos[i].y += 15;

				if (this->tankBulletPos[i].y > GAME_WINDOW_RECT::HEIGHT)
				{
					this->tankBulletPos.erase(this->tankBulletPos.begin() + i);
					this->tankBulletDirection.erase(this->tankBulletDirection.begin() + i);
					i--;
					continue;
				}
				break;

			case TANK::SHOOTING_ACTION::LEFT:
				this->tankBulletPos[i].x -= 15;

				if (this->tankBulletPos[i].x < 0)
				{
					this->tankBulletPos.erase(this->tankBulletPos.begin() + i);
					this->tankBulletDirection.erase(this->tankBulletDirection.begin() + i);
					i--;
					continue;
				}
				break;
			}
		}
	}

	SDL_RenderCopy(this->gameRender, this->fontBulletTexture, NULL, &(this->fontBulletTexturePos));

	SDL_RenderPresent(this->gameRender);
}

bool GamePhaseMain::isMarineMoveActionInverse() const
{
	return this->presentMarineMoveActionInverse;
}

bool GamePhaseMain::isBoxCreated() const
{
	return this->boxCreationCheck;
}

bool GamePhaseMain::isMarineGettingInTank() const
{
	return this->tankInMarineCheck;
}

void GamePhaseMain::whenPressTheKeyboard()
{
	static int delayTime1, delayTime2;

	delayTime1++;
	delayTime2++;

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	if (keyboardState[SDL_SCANCODE_SPACE])
	{
		if (delayTime1 > 10)
		{
			getBulletToBox();
			getInOrgetOutTank();

			delayTime1 = 0;
		}
	}

	if (keyboardState[SDL_SCANCODE_UP] && keyboardState[SDL_SCANCODE_RIGHT])
	{
		moveMarine(MARINE::MOVE_ACTION::DIAGONAL_RIGHT_UP, false);
	}
	else if (keyboardState[SDL_SCANCODE_UP] && keyboardState[SDL_SCANCODE_LEFT])
	{
		moveMarine(MARINE::MOVE_ACTION::DIAGONAL_RIGHT_UP, true);
	}
	else if (keyboardState[SDL_SCANCODE_DOWN] && keyboardState[SDL_SCANCODE_RIGHT])
	{
		moveMarine(MARINE::MOVE_ACTION::DIAGONAL_RIGHT_DOWN, false);
	}
	else if (keyboardState[SDL_SCANCODE_DOWN] && keyboardState[SDL_SCANCODE_LEFT])
	{
		moveMarine(MARINE::MOVE_ACTION::DIAGONAL_RIGHT_DOWN, true);
	}
	else if (keyboardState[SDL_SCANCODE_UP])
	{
		moveMarine(MARINE::MOVE_ACTION::UP, false);

		if (delayTime2 > 10)
		{
			tankShooting(TANK::SHOOTING_ACTION::UP);
			delayTime2 = 0;
		}
	}
	else if (keyboardState[SDL_SCANCODE_RIGHT])
	{
		moveMarine(MARINE::MOVE_ACTION::RIGHT, false);

		if (delayTime2 > 10)
		{
			tankShooting(TANK::SHOOTING_ACTION::RIGHT);
			delayTime2 = 0;
		}
	}
	else if (keyboardState[SDL_SCANCODE_DOWN])
	{
		moveMarine(MARINE::MOVE_ACTION::DOWN, false);

		if (delayTime2 > 10)
		{
			tankShooting(TANK::SHOOTING_ACTION::DOWN);
			delayTime2 = 0;
		}
	}
	else if (keyboardState[SDL_SCANCODE_LEFT])
	{
		moveMarine(MARINE::MOVE_ACTION::RIGHT, true);

		if (delayTime2 > 10)
		{
			tankShooting(TANK::SHOOTING_ACTION::LEFT);
			delayTime2 = 0;
		}
	}
	else
	{
		whenDontPressTheKeyboard();
		return;
	}
}

void GamePhaseMain::moveMarine(MARINE::MOVE_ACTION presentAction, bool inverse)
{
	if (isMarineGettingInTank())
		return;

	static int delayTime;

	delayTime++;
	if (delayTime < 2)
		return;

	int inversePos = (inverse) ? -1 : 1;
	SDL_Rect presentMarinPos = this->marinePlayer->getPresentRect();
	this->presentMarineMoveAction = presentAction;
	this->presentMarineMoveActionInverse = inverse;

	switch (presentAction)
	{
	case MARINE::MOVE_ACTION::UP:
		this->marinePlayer->SetPosY(this->marinePlayer->getPosY() + MARINE::MOVE_SPEED * -1);
		break;

	case MARINE::MOVE_ACTION::DIAGONAL_RIGHT_UP:
		this->marinePlayer->SetPosX(this->marinePlayer->getPosX() + MARINE::DIAGONAL_MOVE_SPEED * inversePos);
		this->marinePlayer->SetPosY(this->marinePlayer->getPosY() + MARINE::DIAGONAL_MOVE_SPEED * -1);
		break;

	case MARINE::MOVE_ACTION::RIGHT:
		this->marinePlayer->SetPosX(this->marinePlayer->getPosX() + MARINE::MOVE_SPEED * inversePos);
		break;

	case MARINE::MOVE_ACTION::DIAGONAL_RIGHT_DOWN:
		this->marinePlayer->SetPosX(this->marinePlayer->getPosX() + MARINE::DIAGONAL_MOVE_SPEED * inversePos);
		this->marinePlayer->SetPosY(this->marinePlayer->getPosY() + MARINE::DIAGONAL_MOVE_SPEED);
		break;

	case MARINE::MOVE_ACTION::DOWN:
		this->marinePlayer->SetPosY(this->marinePlayer->getPosY() + MARINE::MOVE_SPEED);
		break;
	}

	if (!this->marinePlayer->isBackgroundCollision(this->backgroundTexturePos))
	{
		this->marinePlayer->setPresentRect(presentMarinPos);
		return;
	}

	if (this->marinePlayer->isCollisionInside(this->boxCreationPos))
	{
		this->marinePlayer->setPresentRect(presentMarinPos);
		return;
	}

	if (this->marinePlayer->isCollisionInside(this->tankPos))
	{
		this->marinePlayer->setPresentRect(presentMarinPos);
		return;
	}

	actMarineMotion();

	delayTime = 0;
}

void GamePhaseMain::actMarineMotion()
{
	static int delayTime;

	delayTime++;
	if (delayTime < 2)
		return;

	this->presentMarineMoveMotion++;
	this->presentMarineMoveMotion %= MARINE::MOVE_MOTION_COUNT;

	delayTime = 0;
}

void GamePhaseMain::getBulletToBox()
{
	if (isBoxCreated())
	{
		if (this->marinePlayer->isCollisionOutside(this->boxCreationPos))
		{
			int presentMyBullet = this->marinePlayer->getTankBullet();

			SDL_DestroyTexture(this->fontBulletTexture);
			SDL_Surface* fontTextureSurface = TTF_RenderUTF8_Blended(this->fontInGame, std::to_string(presentMyBullet + 5).c_str(), this->fontColor);
			this->fontBulletTexture = SDL_CreateTextureFromSurface(this->gameRender, fontTextureSurface);
			SDL_FreeSurface(fontTextureSurface);

			this->boxCreationPos.x = -1000;
			this->boxCreationPos.y = -1000;
			this->marinePlayer->setTankBullet(presentMyBullet + 5);
			Mix_PlayChannel(1, this->boxBgmOfDestruction, 0);
			this->boxCreationCheck = false;


		}
	}
}

void GamePhaseMain::getInOrgetOutTank()
{
	if (isMarineGettingInTank())
	{
		if (this->marinePlayer->isCollisionInside(this->tankPos))
		{
			if (this->presentTankShootingAction == TANK::SHOOTING_ACTION::LEFT)
				this->marinePlayer->SetPosX(this->marinePlayer->getPosX() - 10);
			else if (this->presentTankShootingAction == TANK::SHOOTING_ACTION::RIGHT)
				this->marinePlayer->SetPosX(this->marinePlayer->getPosX() + 10);
		}

		this->tankInMarineCheck = false;
		Mix_PlayChannel(1, this->tankBgmOfGetOut, 0);
	}
	else
	{
		if (this->marinePlayer->isCollisionOutside(this->tankPos))
		{
			Mix_PlayChannel(1, this->tankBgmOfGetIn, 0);
			this->tankInMarineCheck = true;
		}
	}
}

void GamePhaseMain::tankShooting(TANK::SHOOTING_ACTION presentAction)
{
	if (!isMarineGettingInTank())
		return;

	SDL_Rect bulletPos;

	bulletPos.w = 50;
	bulletPos.h = 50;

	switch (presentAction)
	{
	case TANK::SHOOTING_ACTION::UP:
		this->tankPos.x = 550;
		this->tankPos.y = 350;
		this->tankPos.w = 100;
		this->tankPos.h = 100;
		bulletPos.x = 575;
		bulletPos.y = 300;
		break;

	case TANK::SHOOTING_ACTION::RIGHT:
		this->tankPos.x = 550;
		this->tankPos.y = 350;
		this->tankPos.w = 120;
		this->tankPos.h = 100;
		bulletPos.x = 695;
		bulletPos.y = 375;
		break;

	case TANK::SHOOTING_ACTION::DOWN:
		this->tankPos.x = 550;
		this->tankPos.y = 350;
		this->tankPos.w = 100;
		this->tankPos.h = 100;
		bulletPos.x = 575;
		bulletPos.y = 475;
		break;

	case TANK::SHOOTING_ACTION::LEFT:
		this->tankPos.x = 530;
		this->tankPos.y = 350;
		this->tankPos.w = 120;
		this->tankPos.h = 100;
		bulletPos.x = 480;
		bulletPos.y = 375;
		break;
	}

	this->presentTankShootingAction = presentAction;

	int presentMyBullet = this->marinePlayer->getTankBullet();
	if (presentMyBullet <= 0)
		return;

	presentMyBullet--;
	this->marinePlayer->setTankBullet(presentMyBullet);

	this->tankBulletPos.push_back(bulletPos);
	this->tankBulletDirection.push_back(presentAction);

	SDL_DestroyTexture(this->fontBulletTexture);
	SDL_Surface* fontTextureSurface = TTF_RenderUTF8_Blended(this->fontInGame, std::to_string(presentMyBullet).c_str(), this->fontColor);
	this->fontBulletTexture = SDL_CreateTextureFromSurface(this->gameRender, fontTextureSurface);
	SDL_FreeSurface(fontTextureSurface);

	Mix_PlayChannel(1, this->tankBgmOfShooting, 0);

	if (presentMyBullet == 0)
	{
		if (!isBoxCreated())
			createBox();
	}
}

void GamePhaseMain::whenDontPressTheKeyboard()
{
	this->presentMarineMoveMotion = 0;
}

void GamePhaseMain::startGamePhase()
{
	createFontTexture();

	this->marinePlayer = new Marine();
	createBox();
}

void GamePhaseMain::createFontTexture()
{
	this->fontColor = { 255, 255, 255, 0 };
	SDL_Surface* fontTextureSurface = TTF_RenderUTF8_Blended(this->fontInGame, CW2A(L"Å¾½ÂÁß", CP_UTF8), fontColor);
	this->fontVehicleTexturePos.x = 100;
	this->fontVehicleTexturePos.y = 600;
	this->fontVehicleTexturePos.w = fontTextureSurface->w;
	this->fontVehicleTexturePos.h = fontTextureSurface->h;
	this->fontVehicleTexture = SDL_CreateTextureFromSurface(this->gameRender, fontTextureSurface);
	SDL_FreeSurface(fontTextureSurface);

	fontTextureSurface = TTF_RenderText_Blended(this->fontInGame, "0", fontColor);
	this->fontBulletTexturePos.x = 1000;
	this->fontBulletTexturePos.y = 600;
	this->fontBulletTexturePos.w = fontTextureSurface->w;
	this->fontBulletTexturePos.h = fontTextureSurface->h;
	this->fontBulletTexture = SDL_CreateTextureFromSurface(this->gameRender, fontTextureSurface);
	SDL_FreeSurface(fontTextureSurface);
}

void GamePhaseMain::createBox()
{
	int boxCreationPosX, boxCreationPosY;

	boxCreationPosX = (rand() % 1000) + 50;
	boxCreationPosY = (rand() % 600) + 50;
	this->boxCreationPos = { boxCreationPosX, boxCreationPosY, 100, 100 };

	while (this->marinePlayer->isCollisionInside(this->boxCreationPos))
	{
		boxCreationPosX = (rand() % 1000) + 50;
		boxCreationPosY = (rand() % 600) + 50;
		this->boxCreationPos = { boxCreationPosX, boxCreationPosY, 100, 100 };
	}

	this->boxCreationCheck = true;
}

void GamePhaseMain::pauseGamePhase()
{
	this->boxCreationCheck = false;
	this->tankInMarineCheck = false;

	delete this->marinePlayer;
	SDL_DestroyTexture(this->fontVehicleTexture);
	SDL_DestroyTexture(this->fontBulletTexture);
}

GamePhaseMain::~GamePhaseMain()
{
	if (this->marinePlayer != NULL)
		delete this->marinePlayer;

	SDL_DestroyTexture(this->backgroundTexture);
	SDL_DestroyTexture(this->boxTexture);
	SDL_DestroyTexture(this->marineTexture);
	SDL_DestroyTexture(this->tankTexture);
	SDL_DestroyTexture(this->fontBulletTexture);
	SDL_DestroyTexture(this->fontVehicleTexture);

	Mix_FreeChunk(this->boxBgmOfDestruction);
	Mix_FreeChunk(this->tankBgmOfGetIn);
	Mix_FreeChunk(this->tankBgmOfGetOut);
	Mix_FreeChunk(this->tankBgmOfShooting);
	TTF_CloseFont(this->fontInGame);
}