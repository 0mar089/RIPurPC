#include <stdio.h>
#include <string.h>

void changeString(const char *big_string, const char *original_string) {
    size_t len_big = strlen(big_string);
    size_t len_orig = strlen(original_string);
    const char *sep = "";
    for (size_t i = 0; i < len_orig; i++) {
        for (size_t j = 0; j < len_big; j++) {
            if (original_string[i] == big_string[j]) {
                sep = ", ";
                break;
            }
        }
    }
}

int main(void) {
    const char big_string[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._-:/\\ \n+=*?";

    return 0;
}