#include <go/go.h>
#include <ren/base.h>
#include <fs.h>
#define base ((GObject*)this)

void gblock_on_draw(GBlock* this, SceneGame* game) {
	if (ren->glow && this->glow) {
		float ox = base->pos.x;
		float oy = base->pos.y;
		if (base->id == 2)
			base->pos.y -= 14.f;
		ren->copy_rot(this->glow, &base->pos, base->rot, base->flip);
		base->pos.x = ox;
		base->pos.y = oy;
	}
	if (this->tex)
		ren->copy_rot(this->tex, &base->pos, base->rot, base->flip);
}

void gblock_on_init(GBlock* this, SceneGame* game) {
	this->glow = NULL;
	if (base->id == 1) {
		this->tex = fs->tex[RES_PNG("square_01_001.png")];
		this->glow = fs->tex[RES_PNG("square_01_glow_001.png")];
	}
	else if (base->id == 2) {
		this->tex = fs->tex[RES_PNG("square_02_001.png")];
		this->glow = fs->tex[RES_PNG("square_02_glow_001.png")];
	}
	else if (base->id == 3) {
		this->tex = fs->tex[RES_PNG("square_03_001.png")];
		this->glow = fs->tex[RES_PNG("square_03_glow_001.png")];
	}
	else if (base->id == 4) {
		this->tex = fs->tex[RES_PNG("square_04_001.png")];
		this->glow = fs->tex[RES_PNG("square_04_glow_001.png")];
	}
	else if (base->id == 5) {
		this->tex = fs->tex[RES_PNG("square_05_001.png")];
	}
	else if (base->id == 6) {
		this->tex = fs->tex[RES_PNG("square_06_001.png")];
		this->glow = fs->tex[RES_PNG("square_06_glow_001.png")];
	}
	else if (base->id == 7) {
		this->tex = fs->tex[RES_PNG("square_07_001.png")];
		this->glow = fs->tex[RES_PNG("square_07_glow_001.png")];
	}
	else if (base->id == 40) {
		this->tex = fs->tex[RES_PNG("plank_01_001.png")];
	}
	else if (base->id == -1)
		this->tex = NULL;
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.position.x = base->pos.x;
	body_def.position.y = base->pos.y;
	body_def.type = b2_staticBody;
	this->body = b2CreateBody(game->world, &body_def);
	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	b2Polygon box = (base->id == -1) ?
		b2MakeBox(100000.f, 100.f) :
		b2MakeBox(15.f, base->id == 40 ? 7.f : 15.f);
	this->shape = b2CreatePolygonShape(this->body, &shape_def, &box);
}

void gblock_on_destroy(GBlock* this, SceneGame* game) {
	b2DestroyShape(this->shape, false);
	b2DestroyBody(this->body);
}

void gblock_create(GBlock* this) {
	go_fill_base(base);
	FCAST(base->on_init, gblock_on_init);
	FCAST(base->on_draw, gblock_on_draw);
	FCAST(base->on_destroy, gblock_on_destroy);
}

void gspike_on_draw(GSpike* this, SceneGame* game) {
	if (ren->glow) {
		base->pos.y += .5f;
		ren->copy_rot(this->glow, &base->pos, base->rot, base->flip);
		base->pos.y -= .5f;
	}
	ren->copy_rot(this->tex, &base->pos, base->rot, base->flip);
}

void gspike_on_init(GSpike* this, SceneGame* game) {
	this->glow = NULL;
	if (base->id == 8) {
		this->tex = fs->tex[RES_PNG("spike_01_001.png")];
		this->glow = fs->tex[RES_PNG("spike_01_glow_001.png")];
	}
	else if (base->id == 39) {
		this->tex = fs->tex[RES_PNG("spike_02_001.png")];
	}
}

void gspike_create(GSpike* this) {
	go_fill_base(base);
	FCAST(base->on_init, gspike_on_init);
	FCAST(base->on_draw, gspike_on_draw);
}
