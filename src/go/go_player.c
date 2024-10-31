#include <go/player.h>
#include <fs.h>

void go_player_init(Player* this, SceneGame* game) {
	this->tex1 = fs->tex[RES_PNG("player_01_001.png")];
	this->tex2 = fs->tex[RES_PNG("player_01_2_001.png")];
}

void go_player_run(Player* this, SceneGame* game) {
	this->pos.x = 0.f;
	this->pos.y = 400.f;
}

void go_player_update(Player* this, SceneGame* game) {
	this->pos.x += 10.4f * 30.f * dt;
}

void go_player_draw(Player* this, SceneGame* game) {
	ren->tex_col(this->tex1, &RGBA(0, 255, 0, 255));
	ren->copy(this->tex1, &this->pos);
	ren->tex_col(this->tex2, &RGBA(0, 0, 255, 255));
	ren->copy(this->tex2, &this->pos);
	ren->tex_col(this->tex2, &RGBA(255, 255, 255, 255));
}

void go_player_destroy(Player* this, SceneGame* game) {}

void player_create(Player* this) {
	this->on_init = go_player_init;
	this->on_run = go_player_run;
	this->on_update = go_player_update;
	this->on_draw = go_player_draw;
	this->on_destroy = go_player_destroy;
}