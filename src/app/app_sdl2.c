#include <app/sdl2.h>

#if SDL2_ENABLE
#if SDL2_INCLUDE_DIR
#include <SDL2/SDL_syswm.h>
#else
#include <SDL_syswm.h>
#endif
#include <spng.h>
#include <minstd.h>
#include <ren/base.h>
#define LOG_ALLOC DEBUG

AppSDL2* app_sdl2;

char* app_sdl2_read_res_file(const char* fp, size_t* size) {
	if (size)
		*size = 0;
	STRNCPY(app_sdl2->cwd_buf + app_sdl2->cwd_base_size, fp, 216);
	SDL_RWops* file = SDL_RWFromFile(app_sdl2->cwd_buf, "rb");
	if (file == NULL) {
		SLOG_ERROR("Failed to load file %s (%s)", fp, SDL_GetError());
		return NULL;
	}
	Sint64 size_buf = SDL_RWsize(file);
	if (size_buf <= 0) {
		SLOG_ERROR("Failed to get size for file %s (%s)", fp, SDL_GetError());
		SDL_RWclose(file);
		return NULL;
	}
	char* buf = m_alloc(size_buf);
	if (buf == NULL) {
		SDL_RWclose(file);
		return NULL;
	}
	if (size)
		*size = (size_t)size_buf;
	if (SDL_RWread(file, (void*)buf, 1, (size_t)size_buf) != (size_t)size_buf) {
		SLOG_ERROR("Failed to read file %s (%s)", fp, SDL_GetError());
		m_free(buf);
		SDL_RWclose(file);
		return NULL;
	}
	SDL_RWclose(file);
	return buf;
}

void app_sdl2_free_surf(SDL_Surface* surf) {
	SDL_free(surf);
}

SDL_Surface* app_sdl2_create_error_surf(void) {
	SDL_Surface* result = SDL_CreateRGBSurfaceWithFormat(0, 2, 2, 32, SDL_PIXELFORMAT_RGB888);
	if (SDL_MUSTLOCK(result))
		SDL_LockSurface(result);
	((Uint32*)result->pixels)[0] = ((Uint32*)result->pixels)[3] = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? 0xF93EFB : 0xFB3EF9;
	((Uint32*)result->pixels)[1] = ((Uint32*)result->pixels)[2] = 0;
	if (SDL_MUSTLOCK(result))
		SDL_UnlockSurface(result);
	return result;
}

SDL_Surface* app_sdl2_load_surf(const char* fp) {
	if (fp == NULL)
		return app_sdl2_create_error_surf();
	size_t buf_size;
	char* buf = app->read_res_file(fp, &buf_size);
	if (buf == NULL)
		return NULL;
	spng_ctx* ctx = spng_ctx_new(0);
	if (ctx == NULL) {
		SLOG_ERROR("Failed to create SPNG ctx");
		m_free(buf);
		return NULL;
	}
	int err = spng_set_png_buffer(ctx, (const void*)buf, buf_size);
	if (err != SPNG_OK) {
		SLOG_ERROR("Failed to set SPNG buffer (%s)", spng_strerror(err));
		spng_ctx_free(ctx);
		m_free(buf);
		return NULL;
	}
	size_t img_size = 0;
	int img_fmt = SPNG_FMT_RGBA8;
	err = spng_decoded_image_size(ctx, img_fmt, &img_size);
	if (err != SPNG_OK) {
		SLOG_ERROR("Failed to get SPNG image size (%s)", spng_strerror(err));
		spng_ctx_free(ctx);
		m_free(buf);
		return NULL;
	}
	struct spng_ihdr ihdr;
	err = spng_get_ihdr(ctx, &ihdr);
	if (err != SPNG_OK) {
		SLOG_ERROR("Failed to get SPNG image ihdr (%s)", spng_strerror(err));
		spng_ctx_free(ctx);
		m_free(buf);
		return NULL;
	}
	SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(
		0, ihdr.width, ihdr.height,
		ihdr.bit_depth, SDL_PIXELFORMAT_ABGR8888
	);
	if (surf == NULL) {
		SLOG_ERROR("Failed create SDL surface (%s)", SDL_GetError());
		spng_ctx_free(ctx);
		m_free(buf);
		return NULL;
	}
	if (SDL_MUSTLOCK(surf))
		SDL_LockSurface(surf);
	err = spng_decode_image(ctx, surf->pixels, img_size, img_fmt, 0);
	if (SDL_MUSTLOCK(surf))
		SDL_UnlockSurface(surf);
	if (err != SPNG_OK) {
		SLOG_ERROR("Failed to read SPNG image (%s)", spng_strerror(err));
		SDL_FreeSurface(surf);
		spng_ctx_free(ctx);
		m_free(buf);
		return NULL;
	}
	spng_ctx_free(ctx);
	m_free(buf);
	return surf;
}

void app_sdl2_destroy(void) {
	SDL_Quit();
	general_free(app_sdl2);
	SLOG_INFO("Number Of Allocations - %i", (int)SDL_GetNumAllocations());
	app = NULL;
}

bool app_sdl2_init(void) {
	app_sdl2->win = SDL_CreateWindow(
		"Pricol Dash",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1280, 720,
		SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE
	);
	if (app_sdl2->win == NULL) {
		SLOG_ERROR("Failed to create SDL2 window (%s)", SDL_GetError());
		return true;
	}
	SDL_SetWindowMinimumSize(app_sdl2->win, 320, 200);
	app->cwd = SDL_GetBasePath();
	if (app->cwd == NULL) {
		app->cwd = SDL_malloc(3);
		app->cwd[0] = '.';
		app->cwd[1] = '/';
		app->cwd[2] = '\0';
	}
	app_sdl2->cwd_base_size = STRLEN(app->cwd);
	app_sdl2->cwd_buf = m_alloc(app_sdl2->cwd_base_size + 256);
	MEMCPY(app_sdl2->cwd_buf, app->cwd, app_sdl2->cwd_base_size);
	MEMCPY(app_sdl2->cwd_buf + app_sdl2->cwd_base_size, "assets", 6);
	app_sdl2->cwd_buf[app_sdl2->cwd_base_size + 6] = IS_WIN ? '\\' : '/';
	app_sdl2->cwd_buf[app_sdl2->cwd_base_size + 7] = '\0';
	app_sdl2->cwd_base_size += 7;
	app_sdl2->c_freq = (double)SDL_GetPerformanceFrequency();
	return false;
}

void app_sdl2_clock_reset(void) {
	app_sdl2->c_last_tick = SDL_GetPerformanceCounter();
}

void app_sdl2_clock_update(void) {
	Uint64 now = SDL_GetPerformanceCounter();
	app->d_dt = (double)(now - app_sdl2->c_last_tick) / app_sdl2->c_freq;
	dt = (float)app->d_dt;
	app_sdl2->c_last_tick = now;
	app->fps = (int)(1.0 / app->d_dt);
	if (app->fps > (int)app_sdl2->c_freq)
		app->fps = (int)app_sdl2->c_freq;
}

void app_sdl2_quit(void) {
	m_free(app_sdl2->cwd_buf);
	SDL_free(app->cwd);
	SDL_DestroyWindow(app_sdl2->win);
}

void app_sdl2_show_win(bool show) {
	if (show)
		SDL_ShowWindow(app_sdl2->win);
	else
		SDL_HideWindow(app_sdl2->win);
}

void app_sdl2_apply_dark(void) {
	SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	if (SDL_GetWindowWMInfo(app_sdl2->win, &info) == SDL_FALSE)
		return;
#if IS_WIN
	app->hwnd = (void*)info.info.win.window;
#endif
}

void app_sdl2_on_resize(void) {
	int w_buf, h_buf;
	SDL_GetWindowSize(app_sdl2->win, &w_buf, &h_buf);
	app->size.w = (float)w_buf;
	app->size.h = (float)h_buf;
	ren->on_resize();
}

void app_sdl2_poll_events(void) {
	// TODO: mul mouse events by screen DPI scale
	while (SDL_PollEvent(&app_sdl2->ev)) {
		switch (app_sdl2->ev.type) {
		case SDL_QUIT: {
			app->stop();
			break;
		}
		case SDL_WINDOWEVENT: {
			if (app_sdl2->ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				app->on_resize();
			break;
		}
		case SDL_MOUSEMOTION: {
			if (app_sdl2->ev.motion.state & SDL_BUTTON_RMASK) {
				ren->offset.x += app_sdl2->ev.motion.xrel / ren->scale;
				ren->offset.y += app_sdl2->ev.motion.yrel / ren->scale;
				break;
			}
		}
		}
	}
}

#if DEBUG
typedef struct {
	const char* file_path;
	const char* func_name;
	size_t line;
} MemDebugInfo;

void* app_sdl2_memory_alloc(size_t size, const char* file_path, const char* func_name, size_t line) {
#else
void* app_sdl2_memory_alloc(size_t size) {
#endif
#if DEBUG
	void* res = SDL_malloc(sizeof(MemDebugInfo) + size);
	if (res == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Memory Allocation Failed!\nApp will likely Crash!", app_sdl2->win);
		return NULL;
	}
	char* f_end = (char*)((size_t)file_path + SDL_strlen(file_path));
	while (f_end >= file_path) {
		f_end--;
		if (*f_end == '\\' || *f_end == '/')
			break;
	}
	f_end++;
	MemDebugInfo* info_p = (MemDebugInfo*)res;
	info_p->file_path = (const char*)f_end;
	info_p->func_name = func_name;
	info_p->line = line;
#if LOG_ALLOC
	SLOG_INFO("[ALLOC] %s:%i (%s)", func_name, (int)line, f_end);
#endif
	return (void*)((size_t)res + sizeof(MemDebugInfo));
#else
	void* res = SDL_malloc(size);
	if (res == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Memory Allocation Failed!\nApp will likely Crash!", app_sdl2->win);
	}
#endif
	return res;
}

void app_sdl2_memory_free(void* ptr) {
#if DEBUG
	if (ptr == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Attempted to free NULL!", app_sdl2->win);
		return;
	}
	MemDebugInfo* info_p = (MemDebugInfo*)((size_t)ptr - sizeof(MemDebugInfo));
	if (info_p == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Attempted to free NULL!", app_sdl2->win);
		return;
	}
#if LOG_ALLOC
	SLOG_INFO("[FREE] %s:%i (%s)", info_p->func_name, (int)info_p->line, info_p->file_path);
#endif
	SDL_free(info_p);
#else
	if (ptr == NULL)
		return;
	SDL_free(ptr);
#endif
}

bool app_sdl2_create(void) {
	app_sdl2 = general_malloc(sizeof(AppSDL2));
	app = (App*)app_sdl2;
	if (app == NULL)
		return true;
	app_fill_base();
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0) {
		general_free(app);
		SLOG_ERROR("Failed to init SDL2 (%s)", SDL_GetError());
		return true;
	}
	app->destroy = app_sdl2_destroy;
	app->init = app_sdl2_init;
	app->quit = app_sdl2_quit;
	app->show_win = app_sdl2_show_win;
	app->apply_dark = app_sdl2_apply_dark;
	app->poll_events = app_sdl2_poll_events;
	app->on_resize = app_sdl2_on_resize;
	app->memory_alloc = app_sdl2_memory_alloc;
	app->memory_free = app_sdl2_memory_free;
	app->clock_reset = app_sdl2_clock_reset;
	app->clock_update = app_sdl2_clock_update;
	app->read_res_file = app_sdl2_read_res_file;
	FCAST(app->load_surf, app_sdl2_load_surf);
	FCAST(app->free_surf, app_sdl2_free_surf);
	return false;
}
#endif
