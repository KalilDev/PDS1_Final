#include "resource.h"
#include "stdlib.h"

struct resource {
  void *resource;
  void (*destructor)(void *);
};

struct resource_manager {
  struct resource *resources;
};

static struct resource_manager *__global_resource_manager;

struct resource_manager *global_resource_manager() {
  return __global_resource_manager;
}

void set_global_resource_manager(struct resource_manager *rm) {
  __global_resource_manager = rm;
}

struct resource_manager *resource_manager_new() {
  struct resource_manager *rm = malloc(sizeof(struct resource_manager) +
                                       sizeof(struct resource *) * RES_LEN);
  struct resource *res_it = rm->resources = (struct resource *)(rm + 1);
  // TODO
  return rm;
}

void *resource_manager_get(const struct resource_manager *rm,
                           enum resource_manager_resource res) {
  return rm->resources[(size_t)res].resource;
}
void *resource_manager_get_global(enum resource_manager_resource res) {
  return resource_manager_get(global_resource_manager(), res);
}

void resource_manager_destroy(struct resource_manager *rm) {
  for (size_t i = 0; i < RES_LEN; i++) {
    rm->resources[i].destructor(rm->resources[i].resource);
  }
  free(rm);
}
