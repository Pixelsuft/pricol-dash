#include <scenes/game.h>
#include <app/base.h>
#include <app/sdl2.h>
#include <ren/base.h>
#include <go/base.h>
#include <go/base.h>
#include <go/go.h>
#include <fs.h>
#include <minstd.h>
#define base ((Scene*)this)

// TODO: seperate file to parse, seperate func to transform pos

void scene_game_on_init(SceneGame* this) {
	this->def_bg_col.a = this->def_gr_col.a = 255.0f;
	array_init(&this->obj, 0, sizeof(GObject*), sizeof(GObject*) * 128);
	char* lv_str = fs->lv_data[0];
	char* iter = (char*)lv_str;
	char* prev_ch;
	char* prev_ch2;
	char pch, pch2;
	bool still_should_read = true;
	int audio_id = 0;
	while (still_should_read) {
		char* id_str = iter;
		while (*iter != ',' && *iter)
			iter++;
		if (!(*iter))
			break;
		prev_ch = iter;
		pch = *iter;
		*iter = '\0';
		iter++;
		char* val_str = iter;
		while (*iter != ',' && *iter != ';' && *iter)
			iter++;
		if (!(*iter))
			break;
		still_should_read = *iter == ',';
		prev_ch2 = iter;
		pch2 = *iter;
		*iter = '\0';
		iter++;
		if (id_str[0] == 'k') {
			if (id_str[1] == 'S') {
				switch (id_str[2]) {
				case '1': {
					this->def_bg_col.r = (float)ATOI(val_str);
					break;
				}
				case '2': {
					this->def_bg_col.g = (float)ATOI(val_str);
					break;
				}
				case '3': {
					this->def_bg_col.b = (float)ATOI(val_str);
					break;
				}
				case '4': {
					break;
					this->def_gr_col.r = (float)ATOI(val_str);
				}
				case '5': {
					this->def_gr_col.g = (float)ATOI(val_str);
					break;
				}
				case '6': {
					this->def_gr_col.b = (float)ATOI(val_str);
					break;
				}
				default: {
					SINFO("UNKNOWN HEAD %s:%s", id_str, val_str);
					break;
				}
				}
			}
			else if (id_str[1] == 'A') {
				if (id_str[2] == '1')
					audio_id = ATOI(val_str);
			}
		}
		*prev_ch = pch;
		*prev_ch2 = pch2;
	}
	while (*iter) {
		still_should_read = true;
		GObject* obj = NULL;
		while (still_should_read) {
			char* id_str = iter;
			while (*iter != ',' && *iter)
				iter++;
			if (!(*iter))
				break;
			prev_ch = iter;
			pch = *iter;
			*iter = '\0';
			iter++;
			char* val_str = iter;
			while (*iter != ',' && *iter != ';' && *iter)
				iter++;
			if (!(*iter))
				break;
			still_should_read = *iter == ',';
			prev_ch2 = iter;
			pch2 = *iter;
			*iter = '\0';
			iter++;
			if (*id_str && !id_str[1] && (obj || id_str[0] == '1')) {
				// Properties 1 - 9
				switch (id_str[0]) {
				case '1': {
					// Object ID
					switch (ATOI(val_str)) {
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
					case 40: {
						obj = f_alloc(sizeof(GBlock));
						gblock_create((GBlock*)obj);
						break;
					}
					case 8:
					case 39: {
						obj = f_alloc(sizeof(GSpike));
						gspike_create((GSpike*)obj);
						break;
					}
					}
					if (obj)
						obj->id = ATOI(val_str);
					break;
				}
				case '2': {
					obj->pos.x = ATOF(val_str);
					break;
				}
				case '3': {
					obj->pos.y = 500.0f - ATOF(val_str);
					break;
				}
				case '4': {
					obj->flip |= (val_str[0] == '1') ? 1 : 0;
					break;
				}
				case '5': {
					obj->flip |= (val_str[0] == '1') ? 2 : 0;
					break;
				}
				case '6': {
					obj->rot = ATOF(val_str);
					break;
				}
				}
			}
			else if (*id_str && obj) {
				// Properties 10 - 99
			}
			*prev_ch = pch;
			*prev_ch2 = pch2;
		}
		if (obj) {
			obj->on_init(obj, this);
			array_push(&this->obj, sizeof(GObject*), &obj);
		}
	}
}

void scene_game_on_run(SceneGame* this) {
	app->clock_reset();
	this->cam_pos.x = this->cam_pos.y = 0.f;
}

void scene_game_on_update(SceneGame* this) {
	this->cam_pos.x = -ren->offset.x;
	this->cam_pos.y = -ren->offset.y;
	for (GObject** obj = this->obj.data; obj != ARRAY_END(&this->obj); obj++) {
		(*obj)->on_update(*obj, this);
	}
}

void scene_game_on_draw(SceneGame* this) {
	ren->clear(&this->def_bg_col);
	ren->fill_rect_s(&RECT(0, 500, 100000, 5), &this->def_gr_col);
	ren->fill_rect_s(&RECT(100, 100, 30, 30), &this->def_bg_col);
	ren->fill_rect_s(&RECT(100, 200, 30, 30), &this->def_gr_col);
	for (GObject** obj = this->obj.data; obj != ARRAY_END(&this->obj); obj++) {
		if ((*obj)->pos.x + 50.f < this->cam_pos.x)
			continue;
		else if ((*obj)->pos.x - 50.f > this->cam_pos.x + ren->vs.w)
			continue;
		(*obj)->on_draw(*obj, this);
	}
}

void scene_game_on_stop(SceneGame* this) {

}

void scene_game_on_destroy(SceneGame* this) {
	for (GObject** obj = this->obj.data; obj != ARRAY_END(&this->obj); obj++) {
		f_free(*obj);
	}
	array_destroy(&this->obj);
}

Scene* scene_game_create(void) {
	SceneGame* this = f_alloc(sizeof(SceneGame));
	scene_fill_defaults(base);
	FCAST(base->on_init, scene_game_on_init);
	FCAST(base->on_run, scene_game_on_run);
	FCAST(base->on_update, scene_game_on_update);
	FCAST(base->on_draw, scene_game_on_draw);
	FCAST(base->on_stop, scene_game_on_stop);
	FCAST(base->on_destroy, scene_game_on_destroy);
	return base;
}
