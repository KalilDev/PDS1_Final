#ifndef P_RESOURCE_H
#define P_RESOURCE_H

enum resource_manager_resource {
  RES_DISPLAY = 0,
  RES_LEN,
};

struct resource_manager;

struct resource_manager *global_resource_manager();

void set_global_resource_manager(struct resource_manager *rm);

struct resource_manager *resource_manager_new();

void *resource_manager_get(const struct resource_manager *rm,
                           enum resource_manager_resource res);

void *resource_manager_get_global(enum resource_manager_resource res);

void resource_manager_destroy(struct resource_manager *rm);

#endif
