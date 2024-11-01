#include <scenes/game.h>
#include <app/base.h>
#include <app/sdl2.h>
#include <ren/base.h>
#include <go/base.h>
#include <go/base.h>
#include <go/go.h>
#include <go/player.h>
#include <fs.h>
#include <minstd.h>
#define base ((Scene*)this)

// TODO: seperate file to parse, seperate func to transform pos

void scene_game_on_init(SceneGame* this) {
	this->def_bg_col.a = this->def_gr_col.a = 255.0f;
	array_init(&this->obj, 0, sizeof(GObject*), sizeof(GObject*) * 128);
	char* lv_str = fs->lv_data[0]; // TODO: level selection
	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity.y = 9.81f * 120.f;
	world_def.gravity.y = 0.f;
	this->world = b2CreateWorld(&world_def);
	// Parsing begins
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

	{
		// Ground hack
		GBlock* ground = f_alloc(sizeof(GBlock));
		gblock_create(ground);
		ground->parent.id = -1;
		ground->parent.pos.y = 600.0f;
		ground->parent.pos.x = 1000.0f;
		ground->parent.on_init(&ground->parent, this);
		array_push(&this->obj, sizeof(GObject*), &ground);
	}
	this->pl = f_alloc(sizeof(Player));
	player_create(this->pl);
	this->pl->on_init(this->pl, this);
	this->floor = fs->tex[RES_PNG("floor.png")];
	this->ground = fs->tex[RES_PNG("groundSquare_001.png")];
}

void scene_game_on_run(SceneGame* this) {
	app->clock_reset();
	this->cam_pos.x = -200.f;
	this->cam_pos.y = 150.f;
	this->ground_pos = 64.f;
	this->pl->on_run(this->pl, this);
}

static bool has_key = false;
void scene_game_on_update(SceneGame* this) {
	this->cam_pos.x += 10.4f * 30.f * dt;
	ren->offset.x = -this->cam_pos.x;
	ren->offset.y = -this->cam_pos.y;
	b2World_Step(this->world, dt, 4);
	for (GObject** obj = this->obj.data; obj != ARRAY_END(&this->obj); obj++) {
		(*obj)->on_update(*obj, this);
	}
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK) {
		if (!has_key) {
			has_key = true;
			this->pl->holding_jump_key = true;
		}
	}
	else
		has_key = false;
	this->pl->on_update(this->pl, this);
	this->pl->holding_jump_key = false;
	this->ground_pos -= 10.4f * 30.f * dt;
	if (this->ground_pos <= -64.f)
		this->ground_pos += 128.f;
}

void scene_game_on_draw(SceneGame* this) {
	ren->clear(&this->def_bg_col);
	// ren->fill_rect_s(&RECT(0, 400, 100000, 5), &this->def_gr_col);
	for (GObject** obj = this->obj.data; obj != ARRAY_END(&this->obj); obj++) {
		if ((*obj)->pos.x + 50.f < this->cam_pos.x)
			continue;
		else if ((*obj)->pos.x - 50.f > this->cam_pos.x + ren->vs.w)
			continue;
		(*obj)->on_draw(*obj, this);
	}
	// Ground
	ren->offset.x = 0.f;
	ren->tex_col(this->ground, &this->def_gr_col);
	for (float x = this->ground_pos; x < this->ground_pos + 128.f * 8.f; x += 128.f) {
		Point dst = { x, 500.f + 64.f };
		ren->copy(this->ground, &dst);
	}
	ren->copy(this->floor, &POINT(ren->vs.w / 2.0f, 500.f));
	ren->offset.x = -this->cam_pos.x;
	this->pl->on_draw(this->pl, this);
}

void scene_game_on_stop(SceneGame* this) {

}

void scene_game_on_destroy(SceneGame* this) {
	this->pl->on_destroy(this->pl, this);
	f_free(this->pl);
	for (GObject** obj = this->obj.data; obj != ARRAY_END(&this->obj); obj++) {
		(*obj)->on_destroy(*obj, this);
		f_free(*obj);
	}
	array_destroy(&this->obj);
	b2DestroyWorld(this->world);
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
