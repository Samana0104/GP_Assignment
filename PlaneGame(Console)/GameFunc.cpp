#include "GameFunc.h"
#include <windows.h>

typedef enum
{
	STOP,
	LEFT,
	RIGHT,
	UP,
	SPACE,
	DOWN
} FLIGHT_MOVE;

typedef enum
{
	MIN = 0,
	MAX_X = 20,
	MAX_Y = 30
} FLIGHT_DISPLAY;

const float MOVE_DELAY = 1.5;
const float LAUCH_DELAY = 2.0;

const char FLIGHT_ASCII = '*';
const char FLIGHT_BACKGROUND = '_';
const char FLIGHT_LAUCH = '!';

int g_X;
int g_Y;
int g_lauch[2];

FLIGHT_MOVE g_input;

float g_move_delay;
float g_lauch_delay;
float g_lauch_output_delay;
bool g_flag_running;
bool g_isLauch;

/////////////////////////////////////////////////////////////
// InitGame() 
void InitGame() {
	g_input = FLIGHT_MOVE::STOP;
	g_flag_running = true;
	g_isLauch = false;

	g_X = 0;
	g_Y = 29;
	g_move_delay = 0.0;
	g_lauch_delay = 0.0;
	g_lauch_output_delay = 0.0;
	// Clear the console screen.
	system("cls");
}

/////////////////////////////////////////////////////////////
// Update() 
void Update()
{
	if (g_move_delay >= MOVE_DELAY)
	{
		switch (g_input)
		{
		case FLIGHT_MOVE::LEFT:
			g_X--;
			g_move_delay = 0.0;
			break;
		case FLIGHT_MOVE::RIGHT:
			g_X++;
			g_move_delay = 0.0;
			break;
		case FLIGHT_MOVE::DOWN:
			g_Y++;
			g_move_delay = 0.0;
			break;
		case FLIGHT_MOVE::UP:
			g_Y--;
			g_move_delay = 0.0;
			break;
		}
	}

	if (g_X <= FLIGHT_DISPLAY::MIN)
		g_X = FLIGHT_DISPLAY::MIN;
	else if (g_X >= FLIGHT_DISPLAY::MAX_X)
		g_X = FLIGHT_DISPLAY::MAX_X -1;
	else if (g_Y <= FLIGHT_DISPLAY::MIN)
		g_Y = FLIGHT_DISPLAY::MIN;
	else if (g_Y >= FLIGHT_DISPLAY::MAX_Y)
		g_Y = FLIGHT_DISPLAY::MAX_Y -1;
	
	if (g_lauch_delay >= LAUCH_DELAY)
	{
		switch (g_input)
		{
		case FLIGHT_MOVE::SPACE:
			if (!g_isLauch)
			{
				g_isLauch = true;
				g_lauch[0] = g_X;
				g_lauch[1] = g_Y - 1;
				g_lauch_delay = 0.0;
			}
		}
	}
}




/////////////////////////////////////////////////////////////
// Render() 
void Render() 
{
	COORD flight;
	COORD lauch;
	flight.X = 0;
	flight.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), flight);

	lauch.X = 0;
	lauch.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), lauch);



	for ( int i=FLIGHT_DISPLAY::MIN; i< FLIGHT_DISPLAY::MAX_Y; i++ ) 
	{
		for ( int j=FLIGHT_DISPLAY::MIN; j< FLIGHT_DISPLAY::MAX_X; j++ )
		{
			std::cout << FLIGHT_BACKGROUND;
		}
		std::cout << std::endl;
	}

	flight.X = g_X;
	flight.Y = g_Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), flight);
	std::cout << FLIGHT_ASCII;

	if (g_lauch[1] != 0)
	{
		lauch.X = g_lauch[0];
		lauch.Y = g_lauch[1];
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), lauch);
		std::cout << FLIGHT_LAUCH;
		g_lauch[1]--;
	} 
	else
	{
		g_isLauch = false;
	}
}

void OccurEventDelay()
{
	g_move_delay += 1.0;
	g_lauch_delay += 1.0;
	g_lauch_output_delay += 1.0;
}


/////////////////////////////////////////////////////////////
// HandleEvents() 
void HandleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				g_input = FLIGHT_MOVE::LEFT;
				break;

			case SDLK_RIGHT:
				g_input = FLIGHT_MOVE::RIGHT;
				break;

			case SDLK_DOWN:
				g_input = FLIGHT_MOVE::DOWN;
				break;

			case SDLK_UP:
				g_input = FLIGHT_MOVE::UP;
				break;

			case SDLK_SPACE:
				g_input = FLIGHT_MOVE::SPACE;
				break;
			}
			break;

		case SDL_KEYUP:
			g_input = FLIGHT_MOVE::STOP;
			break;
			}
		}
	}
}


/////////////////////////////////////////////////////////////
// ClearGame() 
void ClearGame()
{
	system("cls");
	std::cout << "게임이 끝났습니다." << std::endl;
}

