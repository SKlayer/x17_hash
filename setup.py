from distutils.core import setup, Extension

x17_hash_module = Extension('x17hash',
                               sources = ['x17_module.c',
                                          'x17.c',
                                          'sph/blake.c',
                                          'sph/bmw.c',
                                          'sph/groestl.c',
                                          'sph/jh.c',
                                          'sph/keccak.c',
                                          'sph/skein.c',
                                          'sph/cubehash.c',
                                          'sph/echo.c',
                                          'sph/luffa.c',
                                          'sph/simd.c',
                                          'sph/hamsi.c',
                                          'sph/hamsi_helper.c',
                                          'sph/fugue.c',
                                          'sph/shavite.c',
                                          'sph/shabal.c',
                                          'sph/whirlpool.c',
                                          'sph/sha2big.c',
                                          'sph/haval.c'

                                          ],
                            include_dirs=['.', './sph'])

setup (name = 'x17_hash',
       version = '1.0',
       description = 'Bindings for proof of work used by X17',
       ext_modules = [x17_hash_module])
