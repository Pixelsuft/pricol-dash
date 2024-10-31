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
#define LOAD_FNT(fn) do { \
	int temp_id = RES_FNT(fn ".fnt"); \
	fs_load_fnt((ren->t_sc == 2.0f ? (fn "-hd.fnt") : fn ".fnt"), temp_id, RES_PNG(fn ".png")); \
} while (0)

FileSystem* fs;

bool fs_create(void) {
	fs = m_alloc(sizeof(FileSystem));
	if (fs == NULL)
		return true;
	return false;
}

bool fs_init(void) {
	MEMSET(fs->tex, 0, sizeof(fs->tex));
	MEMSET(fs->fnt, 0, sizeof(fs->fnt));
	fs->temp_tex = NULL;
	fs->temp_surf = NULL;
	fs->progress = 0;
	fs->total_count = MAX_RES_PNG + MAX_RES_MP3 + MAX_RES_OGG + MAX_RES_FNT + MAX_RES_SHEET + MAX_RES_PLIST + 1;
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
		int rect_buf[4];
		SASSERT(SSCANF(xbuf, "{{%i,%i},{%i,%i}}", &rect_buf[0], &rect_buf[1], &rect_buf[2], &rect_buf[3]) == 4);
		// Rotated
		name_buf = xml_node_name(xml_node_child(data, 5));
		xml_string_copy(name_buf, xbuf, xml_string_length(name_buf));
		xbuf[xml_string_length(name_buf)] = '\0';
		// Magic
		bool rotated = xbuf[0] == 't' || xbuf[1] == 't';
		res->is_sub = true;
		res->real_src.x = (float)rect_buf[0];
		res->real_src.y = (float)rect_buf[1];
		if (rotated) {
			res->real_rot = -90.f;
			res->real_src.w = (float)rect_buf[3];
			res->real_src.h = (float)rect_buf[2];
			res->size.w = (float)rect_buf[3] / ren->t_sc;
			res->size.h = (float)rect_buf[2] / ren->t_sc;
		}
		else {
			res->real_rot = 0.f;
			res->real_src.w = (float)rect_buf[2];
			res->real_src.h = (float)rect_buf[3];
			res->size.w = (float)rect_buf[2] / ren->t_sc;
			res->size.h = (float)rect_buf[3] / ren->t_sc;
		}
	}
	xml_document_free(document, false);
	fs->progress++;
}

void fs_load_fnt(const char* fn, int id, int png_id) {
	size_t size;
	char* buf = app->read_res_file(fn, &size);
	if (buf == NULL)
		return;
	bmfont_init(&fs->fnt[id], buf, size);
	fs->fnt[id].page = fs->tex[png_id];
	m_free(buf);
	fs->progress++;
}

void fs_load_levels(const char* fn) {
	size_t size;
	char* buf = app->read_res_file(fn, &size);
	if (buf == NULL)
		return;
	char* iter = buf;
	for (size_t i = 0; i < 7; i++) {
		fs->lv_data[i] = iter;
		while (*iter != '\n')
			iter++;
		*iter = '\0';
		iter++;
	}
	fs->progress++;
}

int SDLCALL fs_thread_func(void* data) {
	UNUSED1(data);
	// First of all, loading screen
	LOAD_PNG("game_bg_01_001");
	LOAD_PNG("GJ_LaunchSheet");
	LOAD_SHEET("GJ_LaunchSheet");
	LOAD_PNG("goldFont");
	LOAD_FNT("goldFont");
	LOAD_PNG("sliderBar");
	LOAD_PNG("slidergroove");
	// Continue
	LOAD_PNG("bigFont");
	LOAD_PNG("chatFont");
	LOAD_PNG("GJ_GameSheet");
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
	LOAD_PNG("slidergroove_02");
	LOAD_PNG("sliderthumb");
	LOAD_PNG("sliderthumbsel");
	LOAD_PNG("smallDot");
	LOAD_PNG("square01_001");
	LOAD_SHEET("GJ_GameSheet");
	SLOG_INFO("Loading ended!!");
	fs_load_levels("full_lv.txt");
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
	m_free(fs->lv_data);
	BMFont* fnt_ptr = fs->fnt;
	while (fnt_ptr != (BMFont*)&fs->tex) {
		bmfont_destroy(fnt_ptr);
		fnt_ptr++;
	}
	Tex** tex_ptr = fs->tex;
	while (tex_ptr != (Tex**)&fs->lv_data) {
		if (*tex_ptr)
			ren->tex_destroy(*tex_ptr);
		tex_ptr++;
	}
	m_free(fs);
}
