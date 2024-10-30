#include <fs.h>
#include <app/base.h>

FileSystem* fs;

bool fs_create(void) {
	fs = m_alloc(sizeof(FileSystem));
	if (fs == NULL)
		return true;
	MEMSET(fs->tex, 0, sizeof(fs->tex));
	return false;
}

bool fs_init(void) {
	fs->temp_surf = NULL;
	fs->progress = 0;
	fs->total_count = MAX_RES_PNG + MAX_RES_MP3 + MAX_RES_OGG + MAX_RES_FNT + MAX_RES_SHEET + MAX_RES_PLIST;
	fs->threaded = false;
	fs->running = false;
	return false;
}

void fs_update_from_loop(void) {

}

int SDLCALL fs_thread_func(void* data) {
	UNUSED1(data);
	SINFO("hello from thread");
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
	m_free(fs);
}
