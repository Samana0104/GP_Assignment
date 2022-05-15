#include "MainHandler.h"

int main(int argc, char* argv[])
{
	MainHandler game(100, 100, 1200, 800);
	game.gameStart();
	return 0;
}
