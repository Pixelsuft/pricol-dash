#include <ren/sdl2.h>

#if SDL2_ENABLE
#include <app/sdl2.h>
#include <scenes/base.h>
#include <minstd.h>

RenSDL2* ren_sdl2;

void ren_sdl2_destroy(void) {
	m_free(ren_sdl2);
	ren = NULL;
}

bool ren_sdl2_init(void) {
	ren_sdl2->ren = SDL_CreateRenderer(
		app_sdl2->win,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (ren_sdl2->ren == NULL) {
		SLOG_ERROR("Failed to create SDL2 renderer (%s)", SDL_GetError());
		return true;
	}
	ren->offset.x = ren->offset.y = 0.0f;
	return false;
}

void ren_sdl2_quit(void) {
	SDL_DestroyRenderer(ren_sdl2->ren);
}

void ren_sdl2_draw_scene(void) {
	SDL_SetRenderDrawColor(ren_sdl2->ren, 0, 0, 0, 255);
	SDL_RenderClear(ren_sdl2->ren);
	if (app->sc != NULL)
		app->sc->on_draw(app->sc);
	SDL_RenderPresent(ren_sdl2->ren);
}

void ren_sdl2_fill_rect_s(const Rect* rect, const Color* col) {
	SDL_FRect dst = { rect->x + ren->offset.x + rect->w / 2.0f, rect->y + ren->offset.y + rect->h / 2.0f, rect->w, rect->h };
	SDL_SetRenderDrawBlendMode(ren_sdl2->ren, col->r >= 255.0f ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(ren_sdl2->ren, (Uint8)col->r, (Uint8)col->g, (Uint8)col->b, (Uint8)col->a);
	SDL_RenderFillRectF(ren_sdl2->ren, &dst);
}

void ren_sdl2_on_resize(void) {
	int w_buf, h_buf;
	if (SDL_GetRendererOutputSize(ren_sdl2->ren, &w_buf, &h_buf) < 0) {
		SLOG_WARN("Failed to get SDL2 renderer size (%s)", SDL_GetError());
		ren->size.w = app->size.w;
		ren->size.h = app->size.h;
	}
	else {
		ren->size.w = (float)w_buf;
		ren->size.h = (float)h_buf;
	}
	ren->scale = ren->size.h / 360.f; // Scale by Y
	ren->vs.h = 360.f;
	ren->vs.w = ren->size.w / ren->scale;
	SDL_RenderSetScale(ren_sdl2->ren, ren->scale, ren->scale);
	SLOG_INFO("Size [%ix%i] [%ix%i]", w_buf, h_buf, (int)ren->vs.w, (int)ren->vs.h);
}

bool ren_sdl2_create(void) {
	ren_sdl2 = m_alloc(sizeof(RenSDL2));
	ren = (Ren*)ren_sdl2;
	ren_fill_base();
	ren->destroy = ren_sdl2_destroy;
	ren->init = ren_sdl2_init;
	ren->quit = ren_sdl2_quit;
	ren->draw_scene = ren_sdl2_draw_scene;
	ren->on_resize = ren_sdl2_on_resize;
	ren->fill_rect_s = ren_sdl2_fill_rect_s;
	return false;
}
#endif
