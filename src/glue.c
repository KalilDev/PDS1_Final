#include "glue.h"
#include "allegro5/system.h"
#include "resource.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>

bool init(void) {
  srand(time(NULL));
  if (!al_init()) {
    fprintf(stderr, "Error initialising Allegro.\n");
    return false;
  }
  al_set_org_name("Kalildev");
  al_set_app_name("3D Pinball Space Cadet");
  al_init_image_addon();
  al_init_font_addon();
  // al_init_primitives_addon();
#ifdef ALLEGRO_ANDROID
  al_android_set_apk_file_interface();
#endif

  struct resource_manager *rm;
  if (!(rm = resource_manager_new())) {
    fprintf(stderr, "Error loading resources.\n");
    return false;
  }

  set_global_resource_manager(rm);
  return true;
}

void done(void) {
  // Free resources
  resource_manager_destroy(global_resource_manager());
  set_global_resource_manager(NULL);
}