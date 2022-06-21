#include <iostream>
#include <ctime>
#include <cstdlib>
#include "SnakeGameBoard.h"

SnakeGameBoard::SnakeGameBoard(const int& _xBoardSize, const int& _yBoardSize) : _isDyingSnake(false), snakePreMoveType(SNAKE_MOVE_TYPE::STOP),
snakePresentMoveType(SNAKE_MOVE_TYPE::STOP), snakeDelay(300.0), blockTimer(2000.0), blockMove(250.0), checkKey(false),
xBoardSize(_xBoardSize+2), yBoardSize(_yBoardSize+2) // +2를 하면 계산이 편함
{
	Point snakeP;

	this->gameBoardArray = new int*[yBoardSize];

	for (int i = 0; i < yBoardSize; i++)
	{
		this->gameBoardArray[i] = new int[xBoardSize];
		memset(gameBoardArray[i], BOARD_TYPE::CANT_MOVE, sizeof(int) * xBoardSize);
	}

	for (int i = 1; i < yBoardSize-1; i++)
	{
		for (int j = 1; j < xBoardSize-1; j++)
			this->gameBoardArray[i][j] = BOARD_TYPE::CAN_MOVE;
		/*
		  1 1 1 1
		  1 0 0 1
		  1 0 0 1
		  1 1 1 1
		  이런식으로 게임판 제작
		*/
	}
	srand(static_cast<unsigned int>(time(NULL)));
	snakeP.xPos = static_cast<int>(xBoardSize / 2);
	snakeP.yPos = static_cast<int>(yBoardSize / 2);
	this->itemPos = { 10, 10 };
	this->gameBoardArray[11][11] = BOARD_TYPE::ITEM;
	this->snake.push_back(snakeP);
}

void SnakeGameBoard::moveSnake()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_LEFT])
	{
		if (this->snakePreMoveType != SNAKE_MOVE_TYPE::RIGHT)
		{
			this->snakePresentMoveType = SNAKE_MOVE_TYPE::LEFT;
			checkKey = true;
		}
	}
	else if (state[SDL_SCANCODE_UP])
	{
		if (this->snakePreMoveType != SNAKE_MOVE_TYPE::DOWN)
		{
			this->snakePresentMoveType = SNAKE_MOVE_TYPE::UP;
			checkKey = true;
		}
	}
	else if (state[SDL_SCANCODE_RIGHT])
	{
		if (this->snakePreMoveType != SNAKE_MOVE_TYPE::LEFT)
		{
			this->snakePresentMoveType = SNAKE_MOVE_TYPE::RIGHT;
			checkKey = true;
		}
	}
	else if (state[SDL_SCANCODE_DOWN])
	{
		if (this->snakePreMoveType != SNAKE_MOVE_TYPE::UP)
		{
			this->snakePresentMoveType = SNAKE_MOVE_TYPE::DOWN;
			checkKey = true;
		}
	}

	if (state[SDL_SCANCODE_SPACE])
	{
		this->snakeDelay.decreaseTime(5.0);
	}
}

void SnakeGameBoard::drawGameBoard(SDL_Renderer* gameRender)
{
	drawGameBoardLine(gameRender);
	drawGameBoardSquare(gameRender);
	drawBlock(gameRender);
	drawitemForPos(gameRender);
	drawSnake(gameRender);
}

void SnakeGameBoard::drawGameBoardLine(SDL_Renderer* gameRender) const
{
	SDL_Rect line;

	for (int i = 0; i < yBoardSize - 1; i++)
	{
		line =
		{
			BOARD_STYLE::RENDER_POS_X,
			BOARD_STYLE::RENDER_POS_Y + (i * BOARD_STYLE::LINE_SIZE + i * BOARD_STYLE::SQUARE_SIZE),
			(xBoardSize - 1) * BOARD_STYLE::LINE_SIZE + (xBoardSize - 2) * BOARD_STYLE::SQUARE_SIZE,
			BOARD_STYLE::LINE_SIZE
		};
		SDL_SetRenderDrawColor(gameRender, 0, 0, 0, 255);
		SDL_RenderFillRect(gameRender, &line);
	}

	for (int i = 0; i < xBoardSize - 1; i++)
	{
		line =
		{
			BOARD_STYLE::RENDER_POS_X + (i * BOARD_STYLE::LINE_SIZE + i * BOARD_STYLE::SQUARE_SIZE),
			BOARD_STYLE::RENDER_POS_Y,
			BOARD_STYLE::LINE_SIZE,
			(yBoardSize - 1) * BOARD_STYLE::LINE_SIZE + (yBoardSize - 2) * BOARD_STYLE::SQUARE_SIZE
		};
		SDL_SetRenderDrawColor(gameRender, 0, 0, 0, 255);
		SDL_RenderFillRect(gameRender, &line);
	}
}

void SnakeGameBoard::drawGameBoardSquare(SDL_Renderer* gameRender) const
{
	SDL_Rect square;

	for (int i = 0; i < yBoardSize - 2; i++)
	{
		for (int j = 0; j < xBoardSize - 2; j++)
		{
			square =
			{
				BOARD_STYLE::RENDER_POS_X + BOARD_STYLE::LINE_SIZE + (j * BOARD_STYLE::LINE_SIZE + j * BOARD_STYLE::SQUARE_SIZE),
				BOARD_STYLE::RENDER_POS_Y + BOARD_STYLE::LINE_SIZE + (i * BOARD_STYLE::LINE_SIZE + i * BOARD_STYLE::SQUARE_SIZE),
				BOARD_STYLE::SQUARE_SIZE,
				BOARD_STYLE::SQUARE_SIZE
			};
			SDL_SetRenderDrawColor(gameRender, 213, 213, 213, 255);
			SDL_RenderFillRect(gameRender, &square);
		}
	}
}

void SnakeGameBoard::drawBlock(SDL_Renderer* gameRender)
{
	if (!checkKey)
		return;

	for (auto i = this->block.begin(); i != this->block.end(); ++i)
	{
		drawblockForPos(i->xPos, i->yPos, gameRender);
	}

	if (this->isDyingSnake())
		return;

	if (this->blockTimer.isDelaying())
	{
		this->blockTimer.decreaseTime(1.0);
	}
	else
	{
		int posY = rand() % (this->yBoardSize - 2);
		int posX = 0;
		Point pt = { posX, posY };
		this->block.push_back(pt);
	}

	if (this->blockMove.isDelaying())
	{
		this->blockMove.decreaseTime(1.0);
	}
	else
	{

		for (auto i = this->block.begin(); i != this->block.end(); ++i)
		{
			this->gameBoardArray[i->yPos + 1][i->xPos + 1] = BOARD_TYPE::CAN_MOVE;
			i->xPos += 1;

			if (this->gameBoardArray[i->yPos + 1][i->xPos + 1] == BOARD_TYPE::ITEM || i->xPos == this->xBoardSize - 2)
			{
				if(this->gameBoardArray[i->yPos + 1][i->xPos + 1] != BOARD_TYPE::ITEM)
					this->gameBoardArray[i->yPos + 1][i->xPos] = BOARD_TYPE::CAN_MOVE;
				this->block.erase(i);
				--i;
				continue;
			}
			else if (this->gameBoardArray[i->yPos + 1][i->xPos + 1] == BOARD_TYPE::CANT_MOVE)
			{
				this->_isDyingSnake = true;
				return;
			}

			this->gameBoardArray[i->yPos + 1][i->xPos + 1] = BOARD_TYPE::CANT_MOVE;
		}
	}
}

void SnakeGameBoard::drawSnake(SDL_Renderer* gameRender)
{
	checkSnakeMove();

	for (auto i = this->snake.begin(); i != this->snake.end(); ++i)
		drawSnakeForPos(i->xPos, i->yPos, gameRender);
}

void SnakeGameBoard::checkSnakeMove()
{
	if (this->isDyingSnake())
		return;

	if (this->snakeDelay.isDelaying())
	{
		this->snakeDelay.decreaseTime(1.0);
		return;
	}

	int xPos, yPos;
	xPos = this->snake.begin()->xPos;
	yPos = this->snake.begin()->yPos;
	Point pt;

	switch (this->snakePresentMoveType)
	{
	case SNAKE_MOVE_TYPE::UP:
		if (this->gameBoardArray[yPos][xPos + 1] == BOARD_TYPE::CANT_MOVE)
		{
			this->_isDyingSnake = true;
			return;
		}
		else if (this->gameBoardArray[yPos][xPos + 1] == BOARD_TYPE::CAN_MOVE)
		{
			this->gameBoardArray[(--this->snake.end())->yPos + 1][(--this->snake.end())->xPos + 1] = BOARD_TYPE::CAN_MOVE;
			this->snake.pop_back();
		}
		else
		{
			this->gameBoardArray[yPos][xPos + 1] = BOARD_TYPE::CAN_MOVE;
			generateItem();
		}

		pt = { xPos, yPos - 1 };
		this->snake.push_front(pt);
		this->gameBoardArray[pt.yPos + 1][pt.xPos + 1] = BOARD_TYPE::CANT_MOVE;
		this->snakePreMoveType = snakePresentMoveType;
		break;
	case SNAKE_MOVE_TYPE::RIGHT:
		if (this->gameBoardArray[yPos + 1][xPos + 2] == BOARD_TYPE::CANT_MOVE)
		{
			this->_isDyingSnake = true;
			return;
		}
		else if (this->gameBoardArray[yPos + 1][xPos + 2] == BOARD_TYPE::CAN_MOVE)
		{
			this->gameBoardArray[(--this->snake.end())->yPos + 1][(--this->snake.end())->xPos + 1] = BOARD_TYPE::CAN_MOVE;
			this->snake.pop_back();
		}
		else
		{
			this->gameBoardArray[yPos + 1][xPos + 2] = BOARD_TYPE::CAN_MOVE;
			generateItem();
		}

		pt = { xPos + 1, yPos };
		this->snake.push_front(pt);
		this->gameBoardArray[pt.yPos + 1][pt.xPos + 1] = BOARD_TYPE::CANT_MOVE;
		this->snakePreMoveType = snakePresentMoveType;
		break;
	case SNAKE_MOVE_TYPE::LEFT:
		if (this->gameBoardArray[yPos + 1][xPos] == BOARD_TYPE::CANT_MOVE)
		{
			this->_isDyingSnake = true;
			return;
		}
		else if (this->gameBoardArray[yPos + 1][xPos] == BOARD_TYPE::CAN_MOVE)
		{
			this->gameBoardArray[(--this->snake.end())->yPos + 1][(--this->snake.end())->xPos + 1] = BOARD_TYPE::CAN_MOVE;
			this->snake.pop_back();
		}
		else
		{
			this->gameBoardArray[yPos + 1][xPos] = BOARD_TYPE::CAN_MOVE;
			generateItem();
		}

		pt = { xPos - 1, yPos };
		this->snake.push_front(pt);
		this->gameBoardArray[pt.yPos + 1][pt.xPos + 1] = BOARD_TYPE::CANT_MOVE;
		this->snakePreMoveType = snakePresentMoveType;
		break;
	case SNAKE_MOVE_TYPE::DOWN:
		if (this->gameBoardArray[yPos + 2][xPos + 1] == BOARD_TYPE::CANT_MOVE)
		{
			this->_isDyingSnake = true;
			return;
		}
		else if (this->gameBoardArray[yPos + 2][xPos + 1] == BOARD_TYPE::CAN_MOVE)
		{
			this->gameBoardArray[(--this->snake.end())->yPos + 1][(--this->snake.end())->xPos + 1] = BOARD_TYPE::CAN_MOVE;
			this->snake.pop_back();
		}
		else
		{
			this->gameBoardArray[yPos + 2][xPos + 1] = BOARD_TYPE::CAN_MOVE;
			generateItem();
		}

		pt = { xPos, yPos + 1 };
		this->snake.push_front(pt);
		this->gameBoardArray[pt.yPos + 1][pt.xPos + 1] = BOARD_TYPE::CANT_MOVE;
		this->snakePreMoveType = snakePresentMoveType;
		break;
	}

	//for (int i = 0; i < yBoardSize; i++)
	//{
	//	for (int j = 0; j < xBoardSize; j++)
	//		std::cout << gameBoardArray[i][j] << " ";
	//	std::cout<<std::endl;
	//}
}

void SnakeGameBoard::drawSnakeForPos(int x, int y, SDL_Renderer* gameRender)
{
	SDL_Rect snake =
	{
		BOARD_STYLE::RENDER_POS_X + BOARD_STYLE::LINE_SIZE + (x * BOARD_STYLE::LINE_SIZE + x * BOARD_STYLE::SQUARE_SIZE),
		BOARD_STYLE::RENDER_POS_Y + BOARD_STYLE::LINE_SIZE + (y * BOARD_STYLE::LINE_SIZE + y * BOARD_STYLE::SQUARE_SIZE),
		BOARD_STYLE::SQUARE_SIZE,
		BOARD_STYLE::SQUARE_SIZE
	};

	SDL_SetRenderDrawColor(gameRender, 255, 255, 179, 255);
	SDL_RenderFillRect(gameRender, &snake);
}

void SnakeGameBoard::drawitemForPos(SDL_Renderer* gameRender)
{
	SDL_Rect item =
	{
		BOARD_STYLE::RENDER_POS_X + BOARD_STYLE::LINE_SIZE + (this->itemPos.xPos * BOARD_STYLE::LINE_SIZE + this->itemPos.xPos * BOARD_STYLE::SQUARE_SIZE),
		BOARD_STYLE::RENDER_POS_Y + BOARD_STYLE::LINE_SIZE + (this->itemPos.yPos * BOARD_STYLE::LINE_SIZE + this->itemPos.yPos * BOARD_STYLE::SQUARE_SIZE),
		BOARD_STYLE::SQUARE_SIZE,
		BOARD_STYLE::SQUARE_SIZE
	};

	SDL_SetRenderDrawColor(gameRender, 255, 167, 167, 255);
	SDL_RenderFillRect(gameRender, &item);
}

void SnakeGameBoard::drawblockForPos(int x, int y, SDL_Renderer* gameRender)
{
	SDL_Rect block =
	{
		BOARD_STYLE::RENDER_POS_X + BOARD_STYLE::LINE_SIZE + (x * BOARD_STYLE::LINE_SIZE + x * BOARD_STYLE::SQUARE_SIZE),
		BOARD_STYLE::RENDER_POS_Y + BOARD_STYLE::LINE_SIZE + (y * BOARD_STYLE::LINE_SIZE + y * BOARD_STYLE::SQUARE_SIZE),
		BOARD_STYLE::SQUARE_SIZE,
		BOARD_STYLE::SQUARE_SIZE
	};

	SDL_SetRenderDrawColor(gameRender, 0, 0, 0, 255);
	SDL_RenderFillRect(gameRender, &block);
}

void SnakeGameBoard::generateItem()
{
	int posX, posY;

	posX = rand() % (this->xBoardSize-10);
	posY = rand() % (this->yBoardSize-2);

	

	while (this->gameBoardArray[posY + 1][posX + 9] != BOARD_TYPE::CAN_MOVE)
	{
		posX = rand() % (this->xBoardSize - 10);
		posY = rand() % (this->yBoardSize - 2);
	}

	this->itemPos = { posX + 8, posY };
	this->gameBoardArray[posY+1][posX+9] = BOARD_TYPE::ITEM;
}

bool SnakeGameBoard::isDyingSnake() const
{
	return this->_isDyingSnake;
}

SnakeGameBoard::~SnakeGameBoard()
{
	for (int i = 0; i < this->yBoardSize; i++)
		delete[] this->gameBoardArray[i];

	delete[] this-> gameBoardArray;
}