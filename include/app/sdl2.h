#pragma once
#include <api/sdl2.h>

#if SDL2_ENABLE
#include <app/base.h>

#if DEBUG
#define SLOG_ERROR(...) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#define SLOG_WARN(...) SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#define SLOG_INFO(...) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#else
#define SLOG_ERROR(...) do {} while (0)
#define SLOG_WARN(...) do {} while (0)
#define SLOG_INFO(...) do {} while (0)
#endif

typedef struct {
	App p;
	Uint64 c_last_tick;
	double c_freq;
	SDL_Event ev;
	SDL_Window* win;
	size_t cwd_base_size;
	char* cwd_buf;
} AppSDL2;

extern AppSDL2* app_sdl2;

#endif
