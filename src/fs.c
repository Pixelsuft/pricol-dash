#include <fs.h>
#include <app/base.h>
#include <xml.h>

#define LOAD_PNGL(fn) do { \
	fs->temp_no_scale = true; \
	int temp_id = RES_PNG(fn ".png"); \
	fs_load_texture(fn ".png", temp_id); \
} while (0)
#define LOAD_PNG(fn) do { \
	fs->temp_no_scale = false; \
	int temp_id = RES_PNG(fn ".png"); \
	fs_load_texture((ren->t_sc == 2.0f ? (fn "-hd.png") : fn ".png"), temp_id); \
} while (0)
#define LOAD_SHEET(fn) do { \
	int temp_id = RES_PLIST(fn ".plist"); \
	fs_load_sheet((ren->t_sc == 2.0f ? (fn "-hd.plist") : fn ".plist"), temp_id, RES_PNG(fn ".png")); \
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
	fs->progress++;
}

void fs_update_from_loop(void) {
	if (!fs->running || !fs->threaded)
		return;
	if (fs->temp_surf != NULL && fs->temp_tex == NULL) {
		fs->temp_tex = ren->tex_from_surf(fs->temp_surf, fs->temp_no_scale);
	}
}

void fs_load_sheet(const char* fn, int id, int png_id) {
	size_t size;
	char* buf = app->read_res_file(fn, &size);
	if (buf == NULL)
		return;
	// Remove header (unsafe)
	uint8_t* ptr = (uint8_t*)buf;
	while (*ptr != '\n') {
		ptr++;
		size--;
	}
	ptr++;
	size--;
	while (*ptr != '\n') {
		ptr++;
		size--;
	}
	ptr++;
	size--;
	struct xml_document* document = xml_parse_document(ptr, size);
	m_free(buf);
	if (!document) {
		SASSERT(0);
		return;
	}
	Tex* src_tex = fs->tex[png_id];
	struct xml_node* root = xml_document_root(document);
	struct xml_node* root_node = xml_node_child(xml_node_child(root, 0), 1);
	for (size_t i = 0; i < xml_node_children(root_node); i += 2) {
		char xbuf[128];
		struct xml_string* name_buf = xml_node_content(xml_node_child(root_node, i));
		xml_string_copy(name_buf, xbuf, xml_string_length(name_buf));
		xbuf[xml_string_length(name_buf)] = '\0';
		Tex* res = ren->tex_dup(src_tex);
		fs->tex[get_png_id(xbuf)] = res;
		struct xml_node* data = xml_node_child(root_node, i + 1);
		// Frame
		name_buf = xml_node_content(xml_node_child(data, 1));
		xml_string_copy(name_buf, xbuf, xml_string_length(name_buf));
		xbuf[xml_string_length(name_buf)] = '\0';
		SINFO("%s", xbuf);
		// Offset
		name_buf = xml_node_content(xml_node_child(data, 3));
		xml_string_copy(name_buf, xbuf, xml_string_length(name_buf));
		xbuf[xml_string_length(name_buf)] = '\0';
		SINFO("%s", xbuf);
		// Rotated
		name_buf = xml_node_name(xml_node_child(data, 5));
		xml_string_copy(name_buf, xbuf, xml_string_length(name_buf));
		xbuf[xml_string_length(name_buf)] = '\0';
		SINFO("%s", xbuf);
		// Source Color
		name_buf = xml_node_content(xml_node_child(data, 7));
		xml_string_copy(name_buf, xbuf, xml_string_length(name_buf));
		xbuf[xml_string_length(name_buf)] = '\0';
		SINFO("%s", xbuf);
		// Source Size
		name_buf = xml_node_content(xml_node_child(data, 9));
		xml_string_copy(name_buf, xbuf, xml_string_length(name_buf));
		xbuf[xml_string_length(name_buf)] = '\0';
		SINFO("%s", xbuf);
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
	LOAD_SHEET("GJ_LaunchSheet");
	SLOG_INFO("Loading ended!!");
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
