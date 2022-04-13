#include "DrawingTechniques_GameFunc.h"
#include <windows.h>
#include <atlstr.h>
#include <vector>
#include <string>
#include <cmath>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"


SDL_Rect g_bg_source_rect;
SDL_Rect g_bg_destination_rect;
SDL_Texture* g_bg_texture;

SDL_Window* g_window;
SDL_Renderer* g_renderer;

Mix_Music* g_bg_mus;
Mix_Chunk* g_shoot_sound;

SDL_Texture* g_plane;
SDL_Rect g_plane_source;
SDL_Rect g_plane_destination;

SDL_Texture* g_rocket;
SDL_Rect g_rocket_source;
std::vector<SDL_Rect> g_rocket_destination(10);

TTF_Font* g_game_font;
SDL_Texture* g_score;
SDL_Texture* g_score_string;

SDL_Rect g_score_destination_rect;
SDL_Rect g_score_string_destination_rect;
SDL_Color fg;

int g_rocket_per_sec;

int g_image_mode;
int g_time_mode;

void CreateGameWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	g_window = SDL_CreateWindow("Game", 100, 100, 600, 720, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}
}

void InitGame() {
	g_flag_running = true;

	// BG
	g_bg_mus = Mix_LoadMUS("../../Resources/Main_Music.mp3");
	g_shoot_sound = Mix_LoadWAV("../../Resources/Shooting_BGM.mp3");

	SDL_Surface* bg_surface = IMG_Load("../../Resources/universe.jpg");
	g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	g_game_font = TTF_OpenFont("../../Resources/OdBestFreind.ttf", 25);
	g_score = NULL;
	fg = { 255, 255, 255, 0 };

	SDL_Surface* tmp_font_surface = TTF_RenderUTF8_Blended(g_game_font, CW2A(L"Á¡¼ö : ", CP_UTF8), fg);
	g_score_string_destination_rect.x = 460;
	g_score_string_destination_rect.y = 20;
	g_score_string_destination_rect.w = tmp_font_surface->w;
	g_score_string_destination_rect.h = tmp_font_surface->h;
	
	g_score_string = SDL_CreateTextureFromSurface(g_renderer, tmp_font_surface);

	tmp_font_surface = TTF_RenderUTF8_Blended(g_game_font, "00000", fg);

	g_score_destination_rect.x = 510;
	g_score_destination_rect.y = 20;
	g_score_destination_rect.w = tmp_font_surface->w;
	g_score_destination_rect.h = tmp_font_surface->h;

	g_score = SDL_CreateTextureFromSurface(g_renderer, tmp_font_surface);
	SDL_FreeSurface(tmp_font_surface);

	g_bg_source_rect.x = 0;
	g_bg_source_rect.y = 0;
	g_bg_source_rect.w = 600;
	g_bg_source_rect.h = 720;

	g_bg_destination_rect.x = 0;
	g_bg_destination_rect.y = 0;
	g_bg_destination_rect.w = 600;
	g_bg_destination_rect.h = 720;


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
	g_image_mode = 0;
	g_frame_per_sec = 100;
	g_rocket_per_sec = 0; 
	Mix_FadeInMusic(g_bg_mus, -1, 1000);
}

void HandleEvents() 
{
	// Handle Events
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			g_flag_running = false;
		}
	}

	if (state[SDL_SCANCODE_LEFT])
	{
		if (g_plane_destination.x > 20)
			g_plane_destination.x -= 5;
	}

	if (state[SDL_SCANCODE_UP])
	{
		if (g_plane_destination.y > 60)
			g_plane_destination.y -= 5;
	}

	if (state[SDL_SCANCODE_RIGHT])
	{
		if (g_plane_destination.x < 480)
			g_plane_destination.x += 5;
	}

	if (state[SDL_SCANCODE_DOWN])
	{
		if (g_plane_destination.y < 610)
			g_plane_destination.y += 5;
	}

	if (state[SDL_SCANCODE_SPACE])
	{
		if (g_rocket_per_sec >= 20)
		{
			SDL_Rect rocketAdd = { g_plane_destination.x, g_plane_destination.y - 50, g_rocket_source.w, g_rocket_source.h };
			g_rocket_destination.push_back(rocketAdd);
			g_rocket_per_sec = 0;
			Mix_PlayChannel(1, g_shoot_sound, 0);



			static int score;
			score += 10;

			std::string format((4-static_cast<int>(log10(score))), '0');
			format += std::to_string(score);

			if (g_score != NULL)
				SDL_DestroyTexture(g_score);

			SDL_Surface* tmp_font_surface = TTF_RenderUTF8_Blended(g_game_font, format.c_str(), fg);
			g_score = SDL_CreateTextureFromSurface(g_renderer, tmp_font_surface);
			SDL_FreeSurface(tmp_font_surface);
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
	SDL_RenderCopy(g_renderer, g_score_string, NULL, &g_score_string_destination_rect);
	SDL_RenderCopy(g_renderer, g_score, NULL, &g_score_destination_rect);

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
	
	Mix_FreeMusic(g_bg_mus);
	Mix_FreeChunk(g_shoot_sound);
	Mix_CloseAudio();

	TTF_CloseFont(g_game_font);
	SDL_DestroyTexture(g_score);
	SDL_DestroyTexture(g_score_string);

	SDL_DestroyWindow(g_window);
	SDL_Quit();
}