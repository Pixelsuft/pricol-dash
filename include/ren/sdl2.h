#pragma once
#include <api/sdl2.h>

#if SDL2_ENABLE
#include <ren/base.h>

typedef struct {
	Tex parent;
	SDL_Texture* tex;
} TexSDL2;

typedef struct {
	Ren p;
	SDL_Renderer* ren;
} RenSDL2;

extern RenSDL2* ren_sdl2;

#endif
