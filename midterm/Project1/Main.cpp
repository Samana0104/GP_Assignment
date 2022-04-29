#include "MainHandler.h"
#include "ConstantDecl.h"
#include "SDL.h"

int main(int argc, char* argv[])
{
	SDL_Rect gameWindowPos = { GAME_WINDOW_RECT::WINDOW_POSX, GAME_WINDOW_RECT::WINDOW_POSY,
		GAME_WINDOW_RECT::WIDTH, GAME_WINDOW_RECT::HEIGHT };

	MainHandler gameManager("Midterm", gameWindowPos, 60.0);
	gameManager.gameStart();
	return 0;
}