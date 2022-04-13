#include "DrawingTechniques_GameFunc.h"
#include <windows.h>
#include <vector>
#include "SDL_image.h"

SDL_Rect g_bg_source_rect;
SDL_Rect g_bg_destination_rect;
SDL_Texture* g_bg_texture;

SDL_Window* g_window;
SDL_Renderer* g_renderer;

SDL_Texture* g_plane;
SDL_Rect g_plane_source;
SDL_Rect g_plane_destination;

SDL_Texture* g_rocket;
SDL_Rect g_rocket_source;
std::vector<SDL_Rect> g_rocket_destination(10);
int g_rocket_per_sec;

void CreateGame()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	g_window = SDL_CreateWindow("First Window", 100, 100, 600, 720, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);
}

void InitGame() {
	g_flag_running = true;

	// BG
	SDL_Surface* bg_surface = IMG_Load("../../Resources/universe.jpg");
	g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	g_bg_source_rect.x = 0;
	g_bg_source_rect.y = 0;
	g_bg_source_rect.w = 600;
	g_bg_source_rect.h = 720;

	g_bg_destination_rect.x = 0;
	g_bg_destination_rect.y = 0;
	g_bg_destination_rect.w = 600;
	g_bg_destination_rect.h = 720;

	

	// Ryu Character

	SDL_Surface* g_plane_surface = IMG_Load("../../Resources/plane.png");
	//SDL_SetColorKey(g_plane_surface, SDL_TRUE, SDL_MapRGB(g_plane_surface->format, 0, 0, 248));
	
	g_plane = SDL_CreateTextureFromSurface(g_renderer, g_plane_surface);
	SDL_FreeSurface(g_plane_surface);

	g_plane_source = { 0, 0, 100, 100 };
	g_plane_destination = { 250, 500, 100, 100 };


	SDL_Surface* g_rocket_surface = IMG_Load("../../Resources/rocket.png");
	g_rocket = SDL_CreateTextureFromSurface(g_renderer, g_rocket_surface);
	SDL_FreeSurface(g_rocket_surface);

	g_rocket_source = { 50, 93, 100, 14 };
	g_frame_per_sec = 100;
	g_rocket_per_sec = 0;
}

void HandleEvents() 
{
	// Handle Events
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			g_flag_running = false;
		}
		else if (event.type == SDL_KEYDOWN) 
		{
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				if (g_plane_destination.x > 0)
					g_plane_destination.x -= 20;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				if (g_plane_destination.y > 0)
					g_plane_destination.y -= 20;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				if (g_plane_destination.x < 500)
					g_plane_destination.x += 20;
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				if (g_plane_destination.y < 620)
					g_plane_destination.y += 20;
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (g_rocket_per_sec >= 10)
				{
					SDL_Rect rocketAdd = { g_plane_destination.x, g_plane_destination.y - 50, g_rocket_source.w, g_rocket_source.h };
					g_rocket_destination.push_back(rocketAdd);
					g_rocket_per_sec = 0;
				}
			}
		}
	}
}

void Update() {
	// Update
	g_rocket_per_sec += 1;
}

void Render() {
	// Background
	SDL_RenderCopy(g_renderer, g_bg_texture, &g_bg_source_rect, &g_bg_destination_rect);

	// Character

	SDL_RenderCopy(g_renderer, g_plane, &g_plane_source, &g_plane_destination);

	for (int i = 0; i < g_rocket_destination.size(); i++)
	{
		SDL_RenderCopy(g_renderer, g_rocket, &g_rocket_source, &g_rocket_destination[i]);
		g_rocket_destination[i].y -= 10;

		if (g_rocket_destination[i].y < 0)
		{
			g_rocket_destination.erase(g_rocket_destination.begin() + i);
			i -= 1;
		}
	}


	SDL_RenderPresent(g_renderer);
}

void ClearGame() {
	SDL_DestroyTexture(g_plane);
	SDL_DestroyTexture(g_bg_texture);
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
}