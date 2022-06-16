#include "allegro5/display.h"
#include "libpinball.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum cli_arg_kind {
  value,
  negation_flag,
  flag,
};
struct cli_argument {
  const char alias;
  const char *name;
  const char *help;
  enum cli_arg_kind kind;
  const char *default_;
};

enum cli_arg_lookup_result { no_arg, has_arg, invalid_arg };

const struct cli_argument cli_args[] = {
    {'h', "help", "Display the help menu", negation_flag, NULL},
    {'d', "debug", "Debug the game", negation_flag, NULL},
    {'f', "fullscreen", "Fullscreen mode", flag, NULL},
};
const size_t cli_args_length = sizeof(cli_args) / sizeof(cli_args[0]);

enum cli_arg_lookup_result
cli_argument_lookup_arg(int argc, char **argv, const struct cli_argument *arg,
                        void *result) {
  for (char **it = argv; it != argv + argc; it++) {
    unsigned int lnlen = 0;
    if ((lnlen = strlen(*it)) < 2) {
      return false;
    }
    unsigned int arglen = strlen(arg->name);
    if (strncmp(*it, "--", 2) == 0 &&
        strncmp(*it + 2, arg->name, arglen) == 0) {
      // found the arg. Check if flag and there is no =
      if (arg->kind != value) {
        if (*it[2] == '=') {
          return invalid_arg;
        }
        *(bool *)result = arg->kind == flag ? true : false;
        return has_arg;
      }
      // found the arg and it is not flag
      if (*it[2] != '=') {
        return invalid_arg;
      }
      *(const char **)result = (*it) + 3;
      return has_arg;
    }
    if (*it[0] == '-' && *it[1] == arg->alias) {
      if (lnlen > 2) {
        return invalid_arg;
      }
      if (arg->kind != value) {
        *(bool *)result = arg->kind == flag ? true : false;
        return has_arg;
      }
      // The next arg is the value. It must not start with - tho
      if (it + 1 == argv + argc) {
        return invalid_arg;
      }
      const char *nextln = *it += 1;
      if (nextln[0] == '-') {
        return invalid_arg;
      }
      *(const char **)result = nextln;
      return has_arg;
    }
  }
  return no_arg;
}

const struct cli_argument *cli_argument_find_by_name(const char *name) {
  for (const struct cli_argument *it = cli_args;
       it != cli_args + cli_args_length; it++) {
    if (it->name == name) {
      return it;
    }
  }
  return NULL;
}

bool cli_argument_lookup_name(int argc, char **argv, const char *name,
                              void *result) {
  const struct cli_argument *arg = cli_argument_find_by_name(name);
  if (arg == NULL) {
    return false;
  }
  return cli_argument_lookup_arg(argc, argv, arg, result);
}

void cli_argument_show_help() {
  puts("Usage:");
  for (const struct cli_argument *it = cli_args;
       it != cli_args + cli_args_length; it++) {
    printf("-%c  ||  --%s  || def: ", it->alias, it->name);
    switch (it->kind) {
    case value:
      printf("\"%s\"", it->default_);
      break;
    case negation_flag:
      printf("false");
      break;
    case flag:
      printf("true");
      break;
    }

    printf("  || %s", it->help);
  }
}

int main(int argc, char **argv) {
  bool show_help = false;
  cli_argument_lookup_name(argc, argv, "help", &show_help);
  if (show_help) {
    cli_argument_show_help();
    return 0;
  }
  bool is_debug = false;
  cli_argument_lookup_name(argc, argv, "debug", &is_debug);
  bool is_fullscreen = false;
  cli_argument_lookup_name(argc, argv, "fullscreen", &is_fullscreen);

  if (!init()) {
    fprintf(stderr, "Error in initialization.\n");
    return 1;

    for (;;) {
      // joypad_find();

      /*while (true) {
        int result = do_menu();
        al_rest(0.250);
        if (result == 1) {
          //do_highscores(INT_MIN);
          continue;
        } else if (result == 2 || result == -1) {
          done();
          return 0;
        }
        break;
      }*/

      // joypad_stop_finding();

      ALLEGRO_DISPLAY *display =
          (ALLEGRO_DISPLAY *)resource_manager_get_global(RES_DISPLAY);
      int o = al_get_display_orientation(display);
      al_set_display_option(display, ALLEGRO_SUPPORTED_ORIENTATIONS, o);

      // player->load();
      run_game_loop();
      // do_highscores(player->getScore());
      // player->destroy();

      al_set_display_option(display, ALLEGRO_SUPPORTED_ORIENTATIONS,
                            ALLEGRO_DISPLAY_ORIENTATION_LANDSCAPE);
    }

    return 0;
  }
}
