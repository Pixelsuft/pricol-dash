#pragma once
#include <platform.h>
#include <minstd.h>
#include <stdbool.h>

#if DEBUG
#define m_alloc(size) (app->memory_alloc((size_t)(size), __FILE__, __func__, __LINE__))
#else
#define m_alloc(size) (app->memory_alloc((size_t)(size)))
#endif
#define m_free(ptr) (app->memory_free(ptr))
// TODO
#define f_alloc(size) m_alloc(size)
#define f_free(ptr) m_free(ptr)

// TODO: call from class App
#define SINFO(...) SLOG_INFO(__VA_ARGS__)
#define ATOI(str) SDL_atoi(str)
#define ATOF(str) (float)SDL_atof(str)
#define MEMSET(dst, c, len) SDL_memset(dst, c, len)
#define STRNLEN(str, n) SDL_strlen(str)
#define STRNEQ(str1, str2, n) (SDL_strncmp(str1, str2, n) == 0)

typedef struct Scene Scene;

typedef struct {
	bool (*init)(void);
	void (*quit)(void);
	void (*apply_dark)(void);
	void (*destroy)(void);
	void (*show_win)(bool show);
	void (*run)(void);
	void (*stop)(void);
	void (*on_resize)(void);
	void (*poll_events)(void);
#if DEBUG
	void* (*memory_alloc)(size_t size, const char* file_path, const char* func_name, size_t line);
#else
	void* (*memory_alloc)(size_t size);
#endif
	void (*memory_free)(void* ptr);
	void (*run_scene)(Scene* scene);
	Point size;
	Scene* sc;
	char* cwd;
	void* hwnd;
	bool running;
} App;

extern App* app;

void app_fill_base(void);
#if SDL2_ENABLE
bool app_sdl2_create(void);
#endif
