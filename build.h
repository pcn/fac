#ifndef NEW_BUILD_H
#define NEW_BUILD_H

#include "fac.h"

void initialize_starting_time();

void mark_facfiles(struct all_targets *all);
void mark_all(struct all_targets *all);
void mark_rule(struct all_targets *all, struct rule *r);

void summarize_build_results(struct all_targets *all);

struct cmd_args {
  const char *create_dotfile, *create_makefile, *create_tupfile,
    *create_script, *create_tarball, *log_directory;
  const char **include_in_tar;
  bool clean, continual, git_add_files;
  listset *targets_requested;
};

void do_actual_build(struct cmd_args *args);

#endif
