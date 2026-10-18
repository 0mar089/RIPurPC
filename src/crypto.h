#ifndef CRYPTO_H
#define CRYPTO_H

#include <windows.h>
#include <bcrypt.h>

extern BCRYPT_ALG_HANDLE  hRsaAlg;
extern BCRYPT_KEY_HANDLE  hPubKey;
extern BCRYPT_ALG_HANDLE  hAesAlg;
extern BCRYPT_KEY_HANDLE  hAesKey;
extern BYTE               aes_key[32];

BOOL crypto_init(void);
BOOL generate_aes_key(void);
BOOL aes_init(void);
void cleanup_crypto(void);

#endif