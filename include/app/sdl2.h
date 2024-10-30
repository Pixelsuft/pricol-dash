#pragma once
#include <api/sdl2.h>

#if SDL2_ENABLE
#include <app/base.h>

#if DEBUG
#define SLOG_ERROR(...) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#define SLOG_WARN(...) SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#define SLOG_INFO(...) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)

static void sdl2_assertion_check(const char* file_path, const char* func, size_t line, int condition) {
	if (!condition) {
		char* f_end = (char*)((size_t)file_path + SDL_strlen(file_path));
		while (f_end >= file_path) {
			if (*f_end == '\\' || *f_end == '/')
				break;
			f_end--;
		}
		f_end++;
		SLOG_ERROR("Assertion failed at %s:%i (%s)", file_path, (int)line, func);
	}
}

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
