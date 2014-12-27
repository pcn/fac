
typedef struct listset {
  const char *path;
  struct listset *next;
} listset;

void insert_to_listset(listset **list, const char *path);
void delete_from_listset(listset **list, const char *path);
int is_in_listset(const listset *list, const char *path);