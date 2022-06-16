#include "aabb.h"
#include <stdbool.h>

struct offset offset_create(int x, int y) {
  struct offset result = {
      x,
      y,
  };
  return result;
}

struct size size_create(unsigned int width, unsigned int height) {
  struct size result = {
      width,
      height,
  };
  return result;
}
struct size size_resize(struct size size, int dx, int dy) {
  return size_create(size.width + dx, size.height + dy);
}
struct size size_resizeo(struct size size, struct offset o) {
  return size_resize(size, o.x, o.y);
}

struct rect rect_from_size_and_offset(struct offset offset, struct size size) {
  struct rect result = {
      offset,
      size,
  };
  return result;
}

struct rect rect_translate(struct rect rect, int dx, int dy) {
  return rect_translateo(rect, offset_create(dx, dy));
}

struct rect rect_translateo(struct rect rect, struct offset offset) {
  return rect_from_size_and_offset(offset_add(rect.offset, offset), rect.size);
}

struct rect rect_resize(struct rect rect, int dx, int dy) {
  return rect_from_size_and_offset(rect.offset, size_resize(rect.size, dx, dy));
}

struct rect rect_resizeo(struct rect rect, struct offset offset) {
  return rect_from_size_and_offset(rect.offset,
                                   size_resizeo(rect.size, offset));
}

struct rect rect_resize(struct rect rect, int dx, int dy);

struct rect rect_resizeo(struct rect rect, struct offset offset);

bool offset_greater(struct offset a, struct offset b) {
  return a.x > b.x && a.y > b.y;
}
bool offset_smaller(struct offset a, struct offset b) {
  return a.x < b.x && a.y < b.y;
}
struct offset offset_from_size(struct size s) {
  return offset_create(s.width, s.height);
}
struct offset offset_translate(struct offset s, int dx, int dy) {
  return offset_create(s.x + dx, s.y + dy);
}
struct offset offset_add(struct offset a, struct offset b) {
  return offset_create(a.x + b.x, a.y + b.y);
}
struct offset rect_start(struct rect rect) {
  return rect.offset;
}
struct offset rect_end(struct rect rect) {
  return offset_add(rect.offset, offset_from_size(rect.size));
}

bool rect_containso(struct rect rect, struct offset o) {
  return offset_greater(rect_start(rect), o) &&
         offset_smaller(rect_end(rect), o);
}

bool rect_containsr(struct rect a, struct rect b) {
  return rect_containso(a, rect_start(b)) && rect_containso(a, rect_end(b));
}

struct offset rect_top_left(struct rect a) {
  return rect_start(a);
}

struct offset rect_top_right(struct rect a) {
  return offset_translate(rect_start(a), a.size.width, 0);
}
struct offset rect_bottom_left(struct rect a) {
  return offset_translate(rect_start(a), 0, a.size.height);
}
struct offset rect_bottom_right(struct rect a) {
  return rect_end(a);
}
bool rect_collides(struct rect a, struct rect b) {
  return rect_containso(a, rect_top_left(b)) ||
         rect_containso(a, rect_top_right(b)) ||
         rect_containso(a, rect_bottom_left(b)) ||
         rect_containso(a, rect_bottom_right(b));
}