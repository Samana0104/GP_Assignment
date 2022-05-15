#pragma once

#include <list>
#include "SDL.h"
#include "TimerToDelay.h"
enum BOARD_TYPE
{
	CANT_MOVE = 0,
	CAN_MOVE = 1,
	ITEM = 2,
};

enum BOARD_STYLE
{
	RENDER_POS_X = 30,
	RENDER_POS_Y = 30,
	LINE_SIZE = 3,
	SQUARE_SIZE = 25
};

enum SNAKE_MOVE_TYPE
{
	STOP,
	UP,
	DOWN,
	RIGHT,
	LEFT
};

struct Point
{
	int xPos;
	int yPos;
};

class SnakeGameBoard
{
private:
	int** gameBoardArray;
	int xBoardSize, yBoardSize;
	bool _isDyingSnake;

	std::list<Point> snake;
	SNAKE_MOVE_TYPE snakePresentMoveType;
	TimerToDelay snakeDelay;
	SNAKE_MOVE_TYPE snakePreMoveType;
	
	bool checkKey;

	Point itemPos;

	std::list<Point> block;
	TimerToDelay blockTimer;
	TimerToDelay blockMove;

	void drawGameBoardLine(SDL_Renderer* gameRender) const;
	void drawGameBoardSquare(SDL_Renderer* gameRender) const;
	void drawBlock(SDL_Renderer* gameRender);

	void drawSnakeForPos(int x, int y, SDL_Renderer* gameRender);
	void drawitemForPos(SDL_Renderer* gameRender);
	void drawblockForPos(int x, int y, SDL_Renderer* gameRender);
	void drawSnake(SDL_Renderer* gameRender);
	void checkSnakeMove();
	void generateItem();
public:
	explicit SnakeGameBoard(const int& _xBoardSize, const int& _yBoardSize);

	void moveSnake();
	void drawGameBoard(SDL_Renderer* gameRender);
	bool isDyingSnake() const;
	~SnakeGameBoard();
};