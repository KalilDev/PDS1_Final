#include "sprite.h"
#include <allegro5/allegro5.h>

bool aabb_sprite_collides(struct aabb_sprite *a, struct aabb_sprite *b) {
  return rect_collides(a->aabb, b->aabb);
}

struct aabb_sprite *aabb_sprite_create(ALLEGRO_BITMAP *sprite,
                                       struct rect aabb) {
  struct aabb_sprite *result = malloc(sizeof(struct aabb_sprite));
  if (result == NULL) {
    return NULL;
  }
  result->sprite = sprite;
  result->aabb = aabb;
  return result;
}

struct aabb_sprite *aabb_sprite_new(char *filename, struct rect aabb) {
  struct aabb_sprite *result = malloc(sizeof(struct aabb_sprite));
  if (result == NULL) {
    return NULL;
  }
  result->sprite = al_load_bitmap(filename);
  result->aabb = aabb;
  return result;
}

void aabb_sprite_draw(struct aabb_sprite *sprite) {
  al_draw_bitmap(sprite->sprite, sprite->aabb.offset.x, sprite->aabb.offset.x,
                 0);
}

void aabb_sprite_destroy(struct aabb_sprite *sprite) {
  if (sprite == NULL) {
    return;
  }
  al_destroy_bitmap(sprite->sprite);
  free(sprite);
}
