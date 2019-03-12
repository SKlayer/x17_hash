/*
 * 应该是第一个X17的Python库了....
 * 修修补补又三年
 * @hanlin.chen
 */





#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "sph/sph_blake.h"
#include "sph/sph_bmw.h"
#include "sph/sph_groestl.h"
#include "sph/sph_jh.h"
#include "sph/sph_keccak.h"
#include "sph/sph_skein.h"
#include "sph/sph_luffa.h"
#include "sph/sph_cubehash.h"
#include "sph/sph_shavite.h"
#include "sph/sph_simd.h"
#include "sph/sph_echo.h"
#include "sph/sph_hamsi.h"
#include "sph/sph_fugue.h"
#include "sph/sph_shabal.h"
#include "sph/sph_whirlpool.h"
#include "sph/sph_sha2.h"
#include "sph/sph_haval.h"



typedef struct {
    sph_blake512_context    blake1;
    sph_bmw512_context      bmw1;
    sph_groestl512_context  groestl1;
    sph_skein512_context    skein1;
    sph_jh512_context       jh1;
    sph_keccak512_context   keccak1;
    sph_luffa512_context    luffa1;
    sph_cubehash512_context cubehash1;
    sph_shavite512_context  shavite1;
    sph_simd512_context     simd1;
    sph_echo512_context     echo1;
    sph_hamsi512_context    hamsi1;
    sph_fugue512_context    fugue1;
    sph_shabal512_context   shabal1;
    sph_whirlpool_context   whirlpool1;
    sph_sha512_context      sha5121;
    sph_haval256_5_context  haval1;
} Xhash_context_holder;

static Xhash_context_holder base_contexts;


void init_X17hash_contexts()
{
    sph_blake512_init(&base_contexts.blake1);
    sph_bmw512_init(&base_contexts.bmw1);
    sph_groestl512_init(&base_contexts.groestl1);
    sph_skein512_init(&base_contexts.skein1);
    sph_jh512_init(&base_contexts.jh1);
    sph_keccak512_init(&base_contexts.keccak1);
    sph_luffa512_init(&base_contexts.luffa1);
    sph_cubehash512_init(&base_contexts.cubehash1);
    sph_shavite512_init(&base_contexts.shavite1);
    sph_simd512_init(&base_contexts.simd1);
    sph_echo512_init(&base_contexts.echo1);
    sph_hamsi512_init(&base_contexts.hamsi1);
    sph_fugue512_init(&base_contexts.fugue1);
    sph_shabal512_init(&base_contexts.shabal1);
    sph_whirlpool_init(&base_contexts.whirlpool1);
    sph_sha512_init(&base_contexts.sha5121);
    sph_haval256_5_init(&base_contexts.haval1);
}


void x17hash(const char *input, char *output, int size)
{
    init_X17hash_contexts();
    Xhash_context_holder ctx;
    uint32_t hashA[16], hashB[16];

    memcpy(&ctx, &base_contexts, sizeof(base_contexts));

    sph_blake512 (&ctx.blake1, input, size);
    sph_blake512_close (&ctx.blake1, hashA);

    sph_bmw512 (&ctx.bmw1, hashA, 64);
    sph_bmw512_close(&ctx.bmw1, hashB);

    sph_groestl512 (&ctx.groestl1, hashB, 64);
    sph_groestl512_close(&ctx.groestl1, hashA);

    sph_skein512 (&ctx.skein1, hashA, 64);
    sph_skein512_close(&ctx.skein1, hashB);

    sph_jh512 (&ctx.jh1, hashB, 64);
    sph_jh512_close(&ctx.jh1, hashA);

    sph_keccak512 (&ctx.keccak1, hashA, 64);
    sph_keccak512_close(&ctx.keccak1, hashB);

    sph_luffa512 (&ctx.luffa1, hashB, 64);
    sph_luffa512_close (&ctx.luffa1, hashA);

    sph_cubehash512 (&ctx.cubehash1, hashA, 64);
    sph_cubehash512_close(&ctx.cubehash1, hashB);

    sph_shavite512 (&ctx.shavite1, hashB, 64);
    sph_shavite512_close(&ctx.shavite1, hashA);

    sph_simd512 (&ctx.simd1, hashA, 64);
    sph_simd512_close(&ctx.simd1, hashB);

    sph_echo512 (&ctx.echo1, hashB, 64);
    sph_echo512_close(&ctx.echo1, hashA);

    sph_hamsi512 (&ctx.hamsi1, hashA, 64);
    sph_hamsi512_close(&ctx.hamsi1, hashB);

    sph_fugue512 (&ctx.fugue1, hashB, 64);
    sph_fugue512_close(&ctx.fugue1, hashA);

    sph_shabal512 (&ctx.shabal1, (const unsigned char*)hashA, 64);
    sph_shabal512_close(&ctx.shabal1, hashB);

    sph_whirlpool (&ctx.whirlpool1, hashB, 64);
    sph_whirlpool_close(&ctx.whirlpool1, hashA);

    sph_sha512 (&ctx.sha5121, hashA, 64);
    sph_sha512_close(&ctx.sha5121, hashB);

    sph_haval256_5 (&ctx.haval1, hashB, 64);
    sph_haval256_5_close(&ctx.haval1, hashA);

    memcpy(output, hashA, 32);
}