#pragma once
#include <config.h>
#include <stdbool.h>
#include <minstd.h>

typedef struct {
	Point size;
	bool is_sub;
} Tex;

typedef struct {
	bool (*init)(void);
	void (*quit)(void);
	void (*on_resize)(void);
	void (*destroy)(void);
	void (*draw_scene)(void);
	void (*fill_rect_s)(const Rect* rect, const Color* col);
	Point size;
	Point vs;
	Point offset;
	float scale;
	float t_sc;
} Ren;

extern Ren* ren;

void ren_fill_base(void);
#if SDL2_ENABLE
bool ren_sdl2_create(void);
#endif
