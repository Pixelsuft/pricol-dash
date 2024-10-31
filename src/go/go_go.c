#include <go/go.h>
#include <ren/base.h>
#include <fs.h>
#define base ((GObject*)this)

void gblock_on_draw(GBlock* this) {
	ren->copy_rot(this->tex, &base->pos, base->rot, base->flip);
}

void gblock_on_init(GBlock* this) {
	base->size.w = base->size.h = 30.f;
	if (base->id == 1)
		this->tex = fs->tex[RES_PNG("square_01_001.png")];
	else if (base->id == 2)
		this->tex = fs->tex[RES_PNG("square_02_001.png")];
	else if (base->id == 3)
		this->tex = fs->tex[RES_PNG("square_03_001.png")];
	else if (base->id == 4)
		this->tex = fs->tex[RES_PNG("square_04_001.png")];
	else if (base->id == 5)
		this->tex = fs->tex[RES_PNG("square_05_001.png")];
	else if (base->id == 6)
		this->tex = fs->tex[RES_PNG("square_06_001.png")];
	else if (base->id == 7)
		this->tex = fs->tex[RES_PNG("square_07_001.png")];
	else
		this->tex = NULL;
}

void gblock_create(GBlock* this) {
	go_fill_base(base);
	FCAST(base->on_init, gblock_on_init);
	FCAST(base->on_draw, gblock_on_draw);
}

void gspike_on_draw(GSpike* this) {
	ren->copy_rot(this->tex, &base->pos, base->rot, base->flip);
}

void gspike_on_init(GSpike* this) {
	base->size.w = base->size.h = 30.f;
	this->tex = fs->tex[RES_PNG("spike_01_001.png")];
}

void gspike_create(GSpike* this) {
	go_fill_base(base);
	FCAST(base->on_init, gspike_on_init);
	FCAST(base->on_draw, gspike_on_draw);
}
