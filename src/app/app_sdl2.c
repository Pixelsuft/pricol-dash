#include <app/sdl2.h>

#if SDL2_ENABLE
#if SDL2_INCLUDE_DIR
#include <SDL2/SDL_syswm.h>
#else
#include <SDL_syswm.h>
#endif
#include <minstd.h>
#include <ren/base.h>
#define LOG_ALLOC DEBUG

AppSDL2* app_sdl2;

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
	return false;
}
#endif
