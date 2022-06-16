#ifndef LIBPINBALL_H
#define LIBPINBALL_H

#include <stdbool.h>

enum resource_manager_resource {
  RES_DISPLAY = 0,
  RES_LEN,
};

bool init();
void *resource_manager_get_global(enum resource_manager_resource res);
void run_game_loop();
void done();

#endif