#include <fs.h>
#include <app/base.h>
// TODO: revert scale
#define LOAD_PNGL(fn) do { \
	fs->temp_no_scale = true; \
	int temp_png_id = RES_PNG(fn ".png"); \
	fs_load_texture(fn ".png", temp_png_id); \
} while (0)
#define LOAD_PNG(fn) do { \
	fs->temp_no_scale = false; \
	int temp_png_id = RES_PNG(fn ".png"); \
	fs_load_texture((ren->t_sc == 2.0f ? (fn "-hd.png") : fn ".png"), temp_png_id); \
} while (0)

FileSystem* fs;

bool fs_create(void) {
	fs = m_alloc(sizeof(FileSystem));
	if (fs == NULL)
		return true;
	MEMSET(fs->tex, 0, sizeof(fs->tex));
	return false;
}

bool fs_init(void) {
	fs->temp_tex = NULL;
	fs->temp_surf = NULL;
	fs->progress = 0;
	fs->total_count = MAX_RES_PNG + MAX_RES_MP3 + MAX_RES_OGG + MAX_RES_FNT + MAX_RES_SHEET + MAX_RES_PLIST;
	fs->threaded = false;
	fs->running = false;
	return false;
}

void fs_load_texture(const char* fn, int id) {
	if (fs->threaded) {
		fs->temp_surf = app->load_surf(fn);
		while (fs->temp_tex == NULL)
			SDL_Delay(1);
		app->free_surf(fs->temp_surf);
		fs->tex[id] = fs->temp_tex;
		fs->temp_surf = NULL;
		fs->temp_tex = NULL;
	}
	else {
		fs->temp_surf = app->load_surf(fn);
		fs->tex[id] = ren->tex_from_surf(fs->temp_surf, fs->temp_no_scale);
		app->free_surf(fs->temp_surf);
	}
}

void fs_update_from_loop(void) {
	if (!fs->running || !fs->threaded)
		return;
	if (fs->temp_surf != NULL && fs->temp_tex == NULL) {
		fs->temp_tex = ren->tex_from_surf(fs->temp_surf, fs->temp_no_scale);
	}
}

int SDLCALL fs_thread_func(void* data) {
	UNUSED1(data);
	LOAD_PNG("game_bg_01_001");
	LOAD_PNG("GJ_LaunchSheet");
	LOAD_PNG("goldFont");
	LOAD_PNG("bigFont");
	LOAD_PNG("chatFont");
	LOAD_PNG("floor");
	LOAD_PNG("fps_images");
	LOAD_PNG("GJ_button_01");
	LOAD_PNG("GJ_button_02");
	LOAD_PNG("GJ_button_03");
	LOAD_PNG("GJ_button_04");
	LOAD_PNG("GJ_GameSheet");
	LOAD_PNG("GJ_gradientBG");
	LOAD_PNG("GJ_moveBtn");
	LOAD_PNG("GJ_moveSBtn");
	LOAD_PNG("GJ_square01");
	LOAD_PNG("gk-icon");
	LOAD_PNG("gravityOverlay");
	LOAD_PNG("groundSquare_001");
	LOAD_PNG("loadingCircle");
	LOAD_PNG("sliderBar");
	LOAD_PNG("slidergroove");
	LOAD_PNG("slidergroove_02");
	LOAD_PNG("sliderthumb");
	LOAD_PNG("sliderthumbsel");
	LOAD_PNG("smallDot");
	LOAD_PNG("square01_001");
	fs->running = false;
	return 0;
}

void fs_run(void) {
	fs->running = true;
	fs->threaded = true;
	fs->thread_h = SDL_CreateThread(fs_thread_func, "pd_loader", NULL);
	if (fs->thread_h == NULL) {
		fs->threaded = false;
		SWARN("Failed to create loader thread (%s)", SDL_GetError());
		fs_thread_func(NULL);
	}
	else {
		SDL_DetachThread(fs->thread_h);
	}
}

void fs_destroy(void) {
	Tex** tex_ptr = fs->tex;
	while (tex_ptr != (Tex**)&fs->temp_surf) {
		if (*tex_ptr)
			ren->tex_destroy(*tex_ptr);
		tex_ptr++;
	}
	m_free(fs);
}
