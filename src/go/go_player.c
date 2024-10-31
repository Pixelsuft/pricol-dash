#include <go/player.h>
#include <fs.h>

void go_player_init(Player* this, SceneGame* game) {
	this->tex1 = fs->tex[RES_PNG("player_01_001.png")];
	this->tex2 = fs->tex[RES_PNG("player_01_2_001.png")];
	this->pos.x = 0.f;
	this->pos.y = 400.f;
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.position.x = this->pos.x;
	body_def.position.y = this->pos.y;
	body_def.type = b2_dynamicBody;
	this->body = b2CreateBody(game->world, &body_def);
	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	b2Polygon box = b2MakeBox(15.f, 15.f);
	this->shape = b2CreatePolygonShape(this->body, &shape_def, &box);
}

void go_player_run(Player* this, SceneGame* game) {
	this->pos.x = 0.f;
	this->pos.y = 400.f;
}

void go_player_update(Player* this, SceneGame* game) {
	b2Vec2 vel = b2Body_GetLinearVelocity(this->body);
	vel.x = 10.4f * 30.f;
	b2Body_SetLinearVelocity(this->body, vel);
	b2Vec2 cur_pos = b2Body_GetPosition(this->body);
	this->pos.x = cur_pos.x;
	this->pos.y = cur_pos.y;
}

void go_player_draw(Player* this, SceneGame* game) {
	ren->tex_col(this->tex1, &RGBA(0, 255, 0, 255));
	ren->copy(this->tex1, &this->pos);
	ren->tex_col(this->tex2, &RGBA(0, 0, 255, 255));
	ren->copy(this->tex2, &this->pos);
	ren->tex_col(this->tex2, &RGBA(255, 255, 255, 255));
}

void go_player_destroy(Player* this, SceneGame* game) {
	b2DestroyShape(this->shape, false);
	b2DestroyBody(this->body);
}

void player_create(Player* this) {
	this->on_init = go_player_init;
	this->on_run = go_player_run;
	this->on_update = go_player_update;
	this->on_draw = go_player_draw;
	this->on_destroy = go_player_destroy;
}