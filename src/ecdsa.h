/*
  Copyright (c) 2012, Nils Schneider <nils@nilsschneider.net>
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include <libuecc/ecc.h>

typedef struct _ecdsa_verify_context {
   ecc_25519_work_t s1;
   ecc_int256_t u2;
   ecc_int256_t r;
} ecdsa_verify_context;

/* Generates a new secret key.
 * 1 on success, else 0
 */
int ecdsa_new_secret(ecc_int256_t *secret);

void ecdsa_public_from_secret(ecc_int256_t *pub, const ecc_int256_t *secret);

int ecdsa_is_valid_pubkey(const ecc_25519_work_t *pubkey);

void ecdsa_split_signature(ecc_int256_t *r, ecc_int256_t *s, const unsigned char *signature);

void ecdsa_verify_prepare(ecdsa_verify_context *ctx, const ecc_int256_t *hash, const unsigned char *signature);

int ecdsa_verify_with_pubkey(const ecdsa_verify_context *ctx, const ecc_25519_work_t *pubkey);
