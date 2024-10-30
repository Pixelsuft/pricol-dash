#include <ren/sdl2.h>

#if SDL2_ENABLE
#include <app/sdl2.h>
#include <scenes/base.h>
#include <minstd.h>

RenSDL2* ren_sdl2;

TexSDL2* ren_sdl2_tex_dup(TexSDL2* tex) {
	TexSDL2* res = m_alloc(sizeof(TexSDL2));
	res->tex = tex->tex;
	res->parent.is_sub = true;
	res->parent.size.w = tex->parent.size.w;
	res->parent.size.h = tex->parent.size.h;
	res->parent.real_src.x = tex->parent.real_src.x;
	res->parent.real_src.y = tex->parent.real_src.y;
	res->parent.real_src.w = tex->parent.real_src.w;
	res->parent.real_src.h = tex->parent.real_src.h;
	res->parent.real_rot = tex->parent.real_rot;
	return res;
}

void ren_sdl2_tex_destroy(TexSDL2* tex) {
	if (tex == NULL)
		return;
	if (tex->tex != NULL && !tex->parent.is_sub) {
		SDL_DestroyTexture(tex->tex);
		tex->tex = NULL;
	}
	m_free(tex);
}

TexSDL2* ren_sdl2_tex_from_surf(void* surf, bool no_scale) {
	// Assuming it's SDL_surface
	TexSDL2* res = m_alloc(sizeof(TexSDL2));
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren_sdl2->ren, (SDL_Surface*)surf);
	if (tex == NULL) {
		SLOG_ERROR("Failed to create SDL2 texture from surface (%s)", SDL_GetError());
	}
	res->tex = tex;
	res->parent.is_sub = false;
	if (no_scale) {
		res->parent.size.w = (float)((SDL_Surface*)surf)->w;
		res->parent.size.h = (float)((SDL_Surface*)surf)->h;
	}
	else {
		res->parent.size.w = SDL_roundf((float)((SDL_Surface*)surf)->w / ren->t_sc);
		res->parent.size.h = SDL_roundf((float)((SDL_Surface*)surf)->h / ren->t_sc);
	}
	res->parent.real_src.x = res->parent.real_src.y = 0.f;
	res->parent.real_src.w = (float)((SDL_Surface*)surf)->w;
	res->parent.real_src.h = (float)((SDL_Surface*)surf)->h;
	res->parent.real_rot = 0.f;
	return res;
}

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

void ren_sdl2_tex_col(TexSDL2* tex, const Color* col) {
	SDL_SetTextureColorMod(tex->tex, (Uint8)col->r, (Uint8)col->g, (Uint8)col->b);
}

// TODO: transparency
void ren_sdl2_copy(TexSDL2* tex, const Point* dst) {
	if (tex->parent.is_sub) {
		SDL_FRect dst_rect = { dst->x - tex->parent.size.w / 2.0f, dst->y - tex->parent.size.h / 2.0f, tex->parent.size.w, tex->parent.size.h };
		SDL_Rect src_rect = { (int)tex->parent.real_src.x, (int)tex->parent.real_src.y, (int)tex->parent.real_src.w, (int)tex->parent.real_src.h };
		SDL_RenderCopyExF(ren_sdl2->ren, tex->tex, &src_rect, &dst_rect, (double)tex->parent.real_rot, NULL, SDL_FLIP_NONE);
	}
	else {
		SDL_FRect dst_rect = { dst->x - tex->parent.size.w / 2.0f, dst->y - tex->parent.size.h / 2.0f, tex->parent.size.w, tex->parent.size.h };
		SDL_RenderCopyF(ren_sdl2->ren, tex->tex, NULL, &dst_rect);
	}
}

void ren_sdl2_copy_sc(TexSDL2* tex, const Point* dst, float sx, float sy) {
	if (tex->parent.is_sub) {
		SDL_FRect dst_rect = {
			dst->x - tex->parent.size.w * sx / 2.0f, dst->y - tex->parent.size.h * sy / 2.0f,
			tex->parent.size.w * sx, tex->parent.size.h * sy
		};
		SDL_Rect src_rect = { (int)tex->parent.real_src.x, (int)tex->parent.real_src.y, (int)tex->parent.real_src.w, (int)tex->parent.real_src.h };
		SDL_RenderCopyExF(ren_sdl2->ren, tex->tex, &src_rect, &dst_rect, (double)tex->parent.real_rot, NULL, SDL_FLIP_NONE);
	}
	else {
		SDL_FRect dst_rect = {
			dst->x - tex->parent.size.w * sx / 2.0f, dst->y - tex->parent.size.h * sy / 2.0f,
			tex->parent.size.w * sx, tex->parent.size.h * sy
		};
		SDL_RenderCopyF(ren_sdl2->ren, tex->tex, NULL, &dst_rect);
	}
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
	FCAST(ren->tex_from_surf, ren_sdl2_tex_from_surf);
	FCAST(ren->tex_destroy, ren_sdl2_tex_destroy);
	FCAST(ren->tex_col, ren_sdl2_tex_col);
	FCAST(ren->tex_dup, ren_sdl2_tex_dup);
	FCAST(ren->copy, ren_sdl2_copy);
	FCAST(ren->copy_sc, ren_sdl2_copy_sc);
	return false;
}
#endif
