#include "pebble.h"
#include "plane.h"

void plane_render(Plane *plane, GContext *ctx) {
	graphics_draw_bitmap_in_rect(ctx, plane->bitmaps[plane->rot], (GRect) {.origin = {(plane->x / 10 - plane->w / 2), (plane->y / 10 - plane->h / 2)}, .size = {plane->w, plane->h}});
}

void plane_move(Plane *plane) {
	int32_t plane_angle = plane->rot * TRIG_MAX_ANGLE / 16;
	plane->x += (cos_lookup(plane_angle) * plane->speed / TRIG_MAX_RATIO);
	plane->y += (-sin_lookup(plane_angle) * plane->speed / TRIG_MAX_RATIO);
	// Optimize later
	if (plane->x / 10 > 144 + 5) {
		plane->x = -50;
	} else if (plane->x / 10 < -5) {
		plane->x = (144 + 5) * 10;
	}
}

void update_bitmaps(Plane *plane) {
	if (plane->rot % 4 == 0) {
		plane->w = 15;
		plane->h = 12;
	} else if (plane->rot % 4 == 1) {
		plane->w = 16;
		plane->h = 12;
	} else if (plane->rot % 4 == 2) {
		plane->w = 17;
		plane->h = 15;
	} else {
		plane->w = 16;
		plane->h = 16;
	}
	if (plane->rot / 4 % 2 == 1) {
		int16_t tmp = plane->w;
		plane->w = plane->h;
		plane->h = tmp;
	}
}

Plane *plane_create(int player, int x, int y, int rot) {
	Plane *new_plane = malloc(sizeof(Plane));
	new_plane->player = player;
	new_plane->x = x * 10;
	new_plane->y = y * 10;
	new_plane->rot = rot;
	new_plane->speed = 20;
	new_plane->cdwn = 20;
	new_plane->w = 15;
	new_plane->h = 12;
	if (player == 1) {
		// Yes, it's awful, but RotBitmapLayer doesn't work for my purposes
		new_plane->bitmaps[0] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R0);
		new_plane->bitmaps[1] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R1);
		new_plane->bitmaps[2] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R2);
		new_plane->bitmaps[3] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R3);
		new_plane->bitmaps[4] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R4);
		new_plane->bitmaps[5] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R5);
		new_plane->bitmaps[6] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R6);
		new_plane->bitmaps[7] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R7);
		new_plane->bitmaps[8] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R8);
		new_plane->bitmaps[9] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R9);
		new_plane->bitmaps[10] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R10);
		new_plane->bitmaps[11] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R11);
		new_plane->bitmaps[12] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R12);
		new_plane->bitmaps[13] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R13);
		new_plane->bitmaps[14] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R14);
		new_plane->bitmaps[15] = gbitmap_create_with_resource(RESOURCE_ID_PLANE1_R15);
	}
	return new_plane;
}

void plane_destroy(Plane *plane) {
	// Not sure if free() does this automatically
	for (int i = 0; i < 16; ++i) {
		gbitmap_destroy(plane->bitmaps[i]);
	}
	free(plane);
}