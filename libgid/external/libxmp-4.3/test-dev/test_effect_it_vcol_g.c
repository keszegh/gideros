#include "test.h"
#include "../src/effects.h"
#include "../src/mixer.h"
#include "../src/virtual.h"
#include <math.h>

/*
Periodtable for Tuning 0, Normal
  C-1 to B-1 : 856,808,762,720,678,640,604,570,538,508,480,453
  C-2 to B-2 : 428,404,381,360,339,320,302,285,269,254,240,226
  C-3 to B-3 : 214,202,190,180,170,160,151,143,135,127,120,113

Amiga limits: 907 to 108
*/

#define PERIOD ((int)round(1.0 * info.channel_info[0].period / 4096))

/* From 08_sad_song.it, channel 06, pattern 004/011 */

static int vals[] = {
	214, 214, 214, 214,	/* 0 */
	214, 214, 214, 214,	/* 1 */
	214, 214, 214, 214,	/* 2 */
	214, 214, 214, 214,	/* 3 */
	286, 286, 286, 286,	/* 4 */
	286, 286, 286, 286,	/* 5 */
	143, 143, 143, 143,	/* 6 */
	143, 143, 143, 143,	/* 7 */
	143, 143, 143, 143,	/* 8 */
	143, 143, 143, 143,	/* 9 */
	286, 286, 286, 286,	/* 10 */
	286, 286, 286, 286,	/* 11 */
	120, 120, 120, 120,	/* 12 */
	120, 120, 120, 120,	/* 13 */
	120, 120, 120, 120,	/* 14 */
	120, 120, 120, 120,	/* 15 */
	120, 120, 127, 135,	/* 16 */
	135, 135, 135, 135,	/* 17 */
	143, 143, 143, 143,	/* 18 */
	143, 143, 143, 143,	/* 19 */
	143, 143, 143, 143,	/* 20 */
	143, 143, 143, 143,	/* 21 */
	143, 143, 149, 156,	/* 22 */
	163, 163, 170, 177,	/* 23 */
	180, 180, 180, 180,	/* 24 */
	180, 180, 180, 180,	/* 25 */
	180, 180, 180, 180,	/* 26 */
	180, 180, 180, 180,	/* 27 */
	180, 180, 188, 196,	/* 28 */
	205, 205, 214, 214,	/* 29 */
	214, 214, 214, 214,	/* 30 */
	214, 214, 214, 214,	/* 31 */
	143, 143, 143, 143,	/* 32 */
	143, 143, 143, 143,	/* 33 */
	143, 143, 143, 143,	/* 34 */
	143, 143, 143, 143,	/* 35 */
	143, 143, 143, 143,	/* 36 */
	143, 143, 143, 143,	/* 37 */
	143, 143, 149, 156,	/* 38 */
	160, 160, 160, 160,	/* 39 */
	160, 160, 160, 160,	/* 40 */
	160, 160, 160, 160,	/* 41 */
	160, 160, 160, 160,	/* 42 */
	160, 160, 160, 160,	/* 43 */
	180, 180, 180, 180,	/* 44 */
	180, 180, 180, 180,	/* 45 */
	180, 180, 188, 191,	/* 46 */
	191, 191, 191, 191,	/* 47 */
	191, 191, 191, 191,	/* 48 */
	191, 191, 191, 191,	/* 49 */
	191, 191, 191, 191,	/* 50 */
	191, 191, 191, 191,	/* 51 */
	286, 286, 286, 286,	/* 52 */
	286, 286, 286, 286,	/* 53 */
	286, 286, 286, 286,	/* 54 */
	286, 286, 286, 286,	/* 55 */
	143, 143, 143, 143,	/* 56 */
	143, 143, 143, 143,	/* 57 */
	143, 143, 143, 143,	/* 58 */
	143, 143, 143, 143,	/* 59 */
	191, 191, 191, 191,	/* 60 */
	191, 191, 191, 191,	/* 61 */
	191, 191, 183, 180,	/* 62 */
	180, 180, 180, 180	/* 63 */
};

TEST(test_effect_it_vcol_g)
{
	xmp_context opaque;
	struct context_data *ctx;
	struct player_data *p;
	struct mixer_voice *vi;
	struct xmp_frame_info info;
	int i, voc, ret;

	opaque = xmp_create_context();
	ctx = (struct context_data *)opaque;
	p = &ctx->p;

	ret = xmp_load_module(opaque, "data/vcol_g.it");
	fail_unless(ret == 0, "can't load module");

	xmp_start_player(opaque, 44100, 0);

	for (i = 0; i < 64 * 4; i++) {
		xmp_play_frame(opaque);
		xmp_get_frame_info(opaque, &info);

		voc = map_channel(p, 0);
       	 	fail_unless(voc >= 0, "virtual map");
       	 	vi = &p->virt.voice_array[voc];
	
		fail_unless(PERIOD == vals[i], "portamento error");
	}
}
END_TEST
