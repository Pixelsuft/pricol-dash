#include <go/go.h>
#include <ren/base.h>
#include <fs.h>
#define base ((GObject*)this)

void gblock_on_draw(GBlock* this) {
	ren->copy(fs->tex[RES_PNG("square_01_001.png")], &base->pos);
}

void gblock_init(GBlock* this) {
	FCAST(base->on_draw, gblock_on_draw);
}
