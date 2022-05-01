#pragma once

enum GAME_WINDOW_RECT
{
	WINDOW_POSX = 100,
	WINDOW_POSY = 100,
	WIDTH = 1200,
	HEIGHT = 800
};

enum GAME_PHASE
{
	INTRO = 0,
	MAIN = 1,
	END = 2,
	COUNT = 3 // °¹¼ö
};

namespace MAIN_PHASE
{
	enum OBJECT_TEXTURE
	{
		BOX = 0,
		MARINE = 1,
		TANK_BULLET = 2,
		TANK = 3,
		TEXTURE_COUNT = 4 // °¹¼ö
	};

	enum OBJECT_MIX
	{
		WOODEN_BOX = 0,
		GET_IN_TANK = 1,
		GET_OUT_TANK = 2,
		TANK_SHOOTING = 3,
		MIX_COUNT = 4
	};
}

namespace MARINE
{
	enum MOVE_ACTION
	{
		UP = 0,
		DIAGONAL_RIGHT_UP = 1,
		RIGHT = 2,
		DIAGONAL_RIGHT_DOWN = 3,
		DOWN = 4,
		COUNT = 5
	};

	const int MOVE_MOTION_COUNT = 9;
	const int MOVE_SPEED = 10;
	const int DIAGONAL_MOVE_SPEED = 8;
}

namespace TANK
{
	enum SHOOTING_ACTION
	{
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3,
		COUNT = 3
	};
}

const double MILLI_SECOND = 1000.0;