#include <go/go.h>
#include <ren/base.h>
#define base ((GObject*)this)

void gblock_on_draw(GBlock* this) {
	ren->fill_rect_s(&RECT(base->pos.x, base->pos.y, 30, 30), &RGBA(255, 0, 0, 100));
}

void gblock_init(GBlock* this) {
	FCAST(base->on_draw, gblock_on_draw);
}
