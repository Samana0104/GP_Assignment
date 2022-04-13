#include "DrawingTechniques_GameFunc.h"

bool g_flag_running;
Uint32 g_last_time_ms;
Uint32 g_frame_per_sec = 30;

int main(int argc, char* argv[]) {

	// Initializing SDL library

	CreateGameWindow();
	InitGame();

	g_last_time_ms = SDL_GetTicks();

	while (g_flag_running) {

		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < (1000/ g_frame_per_sec) )
			continue;

		HandleEvents();
		Update();
		Render();

		g_last_time_ms = cur_time_ms;
	}

	ClearGame();

	return 0;
}