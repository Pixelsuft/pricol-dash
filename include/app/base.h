#pragma once
#include <platform.h>
#include <minstd.h>
#include <stdbool.h>

#if DEBUG
#define m_alloc(size) (app->memory_alloc((size_t)(size), __FILE__, __func__, __LINE__))
#else
#define m_alloc(size) (app->memory_alloc((size_t)(size)))
#endif
#define m_realloc(ptr, new_size) (app->memory_realloc(ptr, new_size))
#define m_free(ptr) (app->memory_free(ptr))
// TODO
#define f_alloc(size) m_alloc(size)
#define f_free(ptr) m_free(ptr)

// TODO: call from class App, don't depend on SDL2

#define SINFO(...) SLOG_INFO(__VA_ARGS__)
#define SWARN(...) SLOG_WARN(__VA_ARGS__)
#define SERR(...) SLOG_ERROR(__VA_ARGS__)
#if DEBUG
#define SASSERT(cond) do { \
	sdl2_assertion_check(__FILE__, __func__, __LINE__, (cond)); \
} while (0)
#else
#define SASSERT(cond) do {} while (0)
#endif
#define ATOI(str) SDL_atoi(str)
#define ATOF(str) (float)SDL_atof(str)
#define MEMSET(dst, c, len) SDL_memset(dst, c, len)
#define MEMCPY(dst, src, len) SDL_memcpy(dst, src, len)
#define MEMMOVE(dst, src, len) SDL_memmove(dst, src, len)
#define STRLEN(str) SDL_strlen(str)
#define STRNLEN(str, n) SDL_strlen(str)
#define STRNEQ(str1, str2, n) (SDL_strncmp(str1, str2, n) == 0)
#define STRNCPY(dst, src, maxlen) SDL_strlcpy(dst, src, maxlen)
#define SSCANF(text, fmt, ...) SDL_sscanf(text, fmt, __VA_ARGS__)

typedef struct Scene Scene;

extern float dt;

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
	void (*clock_reset)(void);
	void (*clock_update)(void);
#if DEBUG
	void* (*memory_alloc)(size_t size, const char* file_path, const char* func_name, size_t line);
#else
	void* (*memory_alloc)(size_t size);
#endif
	void* (*memory_realloc)(void* ptr, size_t new_size);
	void (*memory_free)(void* ptr);
	void (*run_scene)(Scene* scene);
	void* (*load_surf)(const char* fp);
	void (*free_surf)(void* surf);
	char* (*read_res_file)(const char* fp, size_t* size);
	Point size;
	double d_dt;
	Scene* sc;
	char* cwd;
	void* hwnd;
	int fps;
	bool running;
} App;

extern App* app;

void app_fill_base(void);
#if SDL2_ENABLE
bool app_sdl2_create(void);
#endif
