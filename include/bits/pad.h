#include "aabb.h"
#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>

struct pad_sprite_piece {
  ALLEGRO_BITMAP *image;
  struct offset offset;
};

struct pad_sprite_pair {
  const struct pad_sprite_piece *regular;
  const struct pad_sprite_piece *pressed;
};

enum pad_sprite_color {
  pad_sprite_blue,
  pad_sprite_green,
  pad_sprite_yellow,
  pad_sprite_red,
  pad_sprite_colors_len,
};

struct pad_sprites {
  const struct pad_sprite_pair *pairs;
  struct offset start;
  struct offset end;
};

struct pad_sprites *pad_sprites_load(char *prefix);
void pad_sprite_draw(struct pad_sprites *sprites, enum pad_sprite_color color);
void pad_sprites_destroy(struct pad_sprites *sprites);