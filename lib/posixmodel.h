#ifndef POSIXMODEL_H
#define POSIXMODEL_H

#include "hashset.h"
#include "intmap.h"

#include <sys/types.h>

#include <stdbool.h>

enum inode_type {
  not_here = 0, is_file, is_directory, is_symlink, is_dir_or_symlink
};

struct inode {
  struct hash_entry e;
  enum inode_type type;
  struct inode *parent;
  bool is_written;
  bool is_read;
  union {
    struct hash_table children;
    char *readlink;
  } c; /* c for "contents" */
  char name[];
};

struct posixmodel {
  struct inode *root;
  int num_fds;
  struct intmap processes; // holds mappings from threads to processes
};

void free_inode(struct inode *);

void init_posixmodel(struct posixmodel *m);
void free_posixmodel(struct posixmodel *m);

struct inode *lookup_fd(struct posixmodel *m, pid_t pid, int fd);

void model_dup2(struct posixmodel *m, pid_t pid, int fdorig, int fdtarget);

void model_fork(struct posixmodel *m, pid_t parent, pid_t child);

char *model_realpath(struct inode *i);
struct inode *model_cwd(struct posixmodel *m, pid_t pid);
struct inode *model_lstat(struct posixmodel *m, struct inode *cwd,
                          const char *path0);
struct inode *model_stat(struct posixmodel *m, struct inode *cwd,
                         const char *path0);

int model_chdir(struct posixmodel *m, struct inode *cwd,
                const char *dir, pid_t pid);
void model_newthread(struct posixmodel *m, pid_t parent, pid_t child);

int model_mkdir(struct posixmodel *m, struct inode *cwd, const char *dir);

void model_unlink(struct posixmodel *m, struct inode *cwd, const char *f);

void model_symlink(struct posixmodel *m, struct inode *parent, const char *name,
                   const char *contents);

int model_opendir(struct posixmodel *m, struct inode *cwd,
                  const char *dir, pid_t pid, int fd);
void model_close(struct posixmodel *m, pid_t pid, int fd);
int model_readdir(struct posixmodel *m, pid_t pid, int fd);

void model_rename(struct posixmodel *m, struct inode *cwd,
                  const char *from, const char *to);

struct inode *model_creat(struct posixmodel *m, struct inode *cwd, const char *path);

void model_output(struct posixmodel *m,
                  hashset *read_from_directories,
                  hashset *read_from_files,
                  hashset *written_to_files);

#endif
