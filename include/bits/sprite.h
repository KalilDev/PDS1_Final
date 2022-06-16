#ifndef P_SPRITE_H
#define P_SPRITE_H
#include "aabb.h"
#include "allegro5/bitmap_draw.h"
#include "allegro5/bitmap_io.h"
#include <allegro5/bitmap.h>

struct aabb_sprite {
  ALLEGRO_BITMAP *sprite;
  struct rect aabb;
};

bool aabb_sprite_collides(struct aabb_sprite *a, struct aabb_sprite *b);

struct aabb_sprite *aabb_sprite_create(ALLEGRO_BITMAP *sprite,
                                       struct rect aabb);

struct aabb_sprite *aabb_sprite_new(char *filename, struct rect aabb);

void aabb_sprite_draw(struct aabb_sprite *sprite);

void aabb_sprite_destroy(struct aabb_sprite *sprite);

#endif