#ifndef P_AABB_H
#define P_AABB_H

#include <stdbool.h>

struct offset {
  int x, y;
};

struct size {
  unsigned int width, height;
};

union size_or_offset {
  struct size size;
  struct offset offset;
};

struct rect {
  struct offset offset;
  struct size size;
};

struct offset offset_create(int x, int y);
struct size size_create(unsigned int width, unsigned int height);
struct size size_resize(struct size size, int dx, int dy);
struct size size_resizeo(struct size size, struct offset o);
struct rect rect_from_size_and_offset(struct offset offset, struct size size);
struct rect rect_translate(struct rect rect, int dx, int dy);
struct rect rect_translateo(struct rect rect, struct offset offset);
struct rect rect_resize(struct rect rect, int dx, int dy);
struct rect rect_resizeo(struct rect rect, struct offset offset);
bool offset_greater(struct offset a, struct offset b);
bool offset_smaller(struct offset a, struct offset b);
struct offset offset_from_size(struct size s);
struct offset offset_translate(struct offset s, int dx, int dy);
struct offset offset_add(struct offset a, struct offset b);
struct offset rect_start(struct rect rect);
struct offset rect_end(struct rect rect);
bool rect_containso(struct rect rect, struct offset o);
bool rect_containsr(struct rect a, struct rect b);
struct offset rect_top_left(struct rect a);
struct offset rect_top_right(struct rect a);
struct offset rect_bottom_left(struct rect a);
struct offset rect_bottom_right(struct rect a);
bool rect_collides(struct rect a, struct rect b);
#endif