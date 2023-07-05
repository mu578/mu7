//
// // -*- coding: utf-8, tab-width: 3 -*-

//                                                          _____                                           //
//                                                         (___  )                                          //
//                                            _   _  _   _   _/ /                                           //
//                                           | | | || | | | (  _)                                           //
//                                           | |_| || |_| | / /                                             //
//                                           | ._,_| \___/ /_/                                              //
//                                           | |                                                            //
//                                           |_|                                                            //

// mu7_gemm.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu7/mu7_reference/mu7_lsame.h>
#include <mu7/mu7_reference/mu7_operator.h>
#include <mu7/mu7_reference/mu7_xerbla.h>

#ifndef MU7_GEMM_H
#define MU7_GEMM_H 1

MU0_BEGIN_CDECL

//#!
//#! macro<_Tp, _Up, _Rp, _Sp>(
//#!   const char8  __transa
//#! , const char8  __transb
//#! , const sint   __m
//#! , const sint   __n
//#! , const sint   __k
//#! , const _Sp    __alpha
//#! , const _Tp &* __a
//#! , const sint   __lda
//#! , const _Up &* __b
//#! , const sint   __ldb
//#! , const _Sp    __beta
//#! ,       _Up &* __c
//#! , const sint   __ldc
//#! ) : void
//#!
#	define mu7_gemm(_Tp, _Up, _Rp, _Sp, __transa, __transb, __m, __n, __k, __alpha, __a, __lda, __b, __ldb, __beta, __c, __ldc)                                                                                            \
mu0_scope_begin                                                                                                                                                                                                           \
	const _Tp __mu7_gemm__one__          = mu0_const_cast(_Up, 1);                                                                                                                                                         \
	const _Tp __mu7_gemm__zero__         = mu0_const_cast(_Up, 0);                                                                                                                                                         \
	      _Sp __mu7_gemm__temp__;                                                                                                                                                                                          \
	                                                                                                                                                                                                                       \
	const mu0_sinteger __mu7_gemm__m__   = mu0_const_sinteger(__m);                                                                                                                                                        \
	const mu0_sinteger __mu7_gemm__n__   = mu0_const_sinteger(__n);                                                                                                                                                        \
	const mu0_sinteger __mu7_gemm__n__   = mu0_const_sinteger(__k);                                                                                                                                                        \
	const mu0_sinteger __mu7_gemm__lda__ = mu0_const_sinteger(__lda);                                                                                                                                                      \
	const mu0_sinteger __mu7_gemm__ldb__ = mu0_const_sinteger(__ldb);                                                                                                                                                      \
	const mu0_sinteger __mu7_gemm__ldc__ = mu0_const_sinteger(__ldc);                                                                                                                                                      \
	                                                                                                                                                                                                                       \
	const _Tp * __mu7_gemm__a__          = mu0_const_cast(_Tp *, __a);                                                                                                                                                     \
	const _Up * __mu7_gemm__b__          = mu0_const_cast(_Up *, __b);                                                                                                                                                     \
	      _Rp * __mu7_gemm__c__          = mu0_cast(_Rp *, __c);                                                                                                                                                           \
	                                                                                                                                                                                                                       \
	const _Sp __mu7_gemm__alpha__        = mu0_const_cast(_Sp, __alpha);                                                                                                                                                   \
	const _Sp __mu7_gemm__beta__         = mu0_const_cast(_Sp, __beta);                                                                                                                                                    \
	                                                                                                                                                                                                                       \
	      mu0_sinteger __mu7_gemm__i__;                                                                                                                                                                                    \
	      mu0_sinteger __mu7_gemm__info__;                                                                                                                                                                                 \
	      mu0_sinteger __mu7_gemm__j__;                                                                                                                                                                                    \
	      mu0_sinteger __mu7_gemm__l__;                                                                                                                                                                                    \
	      mu0_sinteger __mu7_gemm__ncola__;                                                                                                                                                                                \
	      mu0_sinteger __mu7_gemm__nrowa__;                                                                                                                                                                                \
	      mu0_sinteger __mu7_gemm__nrowb__;                                                                                                                                                                                \
	      mu0_sinteger __mu7_gemm__ka__;                                                                                                                                                                                   \
	      mu0_sinteger __mu7_gemm__kb__;                                                                                                                                                                                   \
	      mu0_sinteger __mu7_gemm__nota__ = mu7_lsame(__transa, 'N');                                                                                                                                                      \
	      mu0_sinteger __mu7_gemm__notb__ = mu7_lsame(__transb, 'N');                                                                                                                                                      \
	                                                                                                                                                                                                                       \
	if (__mu7_gemm__nota__) {                                                                                                                                                                                              \
		__mu7_gemm__ka__    = __mu7_gemm__k__;                                                                                                                                                                              \
		__mu7_gemm__nrowa__ = __mu7_gemm__m__;                                                                                                                                                                              \
		__mu7_gemm__ncola__ = __mu7_gemm__k__;                                                                                                                                                                              \
		mu0_unused(__mu7_gemm__ka__);                                                                                                                                                                                       \
		mu0_unused(__mu7_gemm__ncola__);                                                                                                                                                                                    \
	} else {                                                                                                                                                                                                               \
		__mu7_gemm__ka__    = __mu7_gemm__m__;                                                                                                                                                                              \
		__mu7_gemm__nrowa__ = __mu7_gemm__k__;                                                                                                                                                                              \
		__mu7_gemm__ncola__ = __mu7_gemm__m__;                                                                                                                                                                              \
		mu0_unused(__mu7_gemm__ka__);                                                                                                                                                                                       \
		mu0_unused(__mu7_gemm__ncola__);                                                                                                                                                                                    \
	}                                                                                                                                                                                                                      \
	if (__mu7_gemm__notb__) {                                                                                                                                                                                              \
		__mu7_gemm__kb__    = __mu7_gemm__n__;                                                                                                                                                                              \
		__mu7_gemm__nrowb__ = __mu7_gemm__k__;                                                                                                                                                                              \
		mu0_unused(__mu7_gemm__kb__);                                                                                                                                                                                       \
	} else {                                                                                                                                                                                                               \
		__mu7_gemm__kb__    = __mu7_gemm__k__;                                                                                                                                                                              \
		__mu7_gemm__nrowb__ = __mu7_gemm__n__;                                                                                                                                                                              \
		mu0_unused(__mu7_gemm__kb__);                                                                                                                                                                                       \
	}                                                                                                                                                                                                                      \
	__mu7_gemm__info__ = 0;                                                                                                                                                                                                \
	if (!__mu7_gemm__nota__ && !mu7_lsame(__transa, 'C') && !mu7_lsame(__transa, 'T')) {                                                                                                                                   \
		__mu7_gemm__info__ = 1;                                                                                                                                                                                             \
	} else if (!__mu7_gemm__notb__ && !mu7_lsame(__transb, 'C') && !mu7_lsame(__transb, 'T')) {                                                                                                                            \
		__mu7_gemm__info__ = 2;                                                                                                                                                                                             \
	} else if (__mu7_gemm__m__ < 0) {                                                                                                                                                                                      \
		__mu7_gemm__info__ = 3;                                                                                                                                                                                             \
	} else if (__mu7_gemm__n__ < 0) {                                                                                                                                                                                      \
		__mu7_gemm__info__ = 4;                                                                                                                                                                                             \
	} else if (__mu7_gemm__k__ < 0) {                                                                                                                                                                                      \
		__mu7_gemm__info__ = 5;                                                                                                                                                                                             \
	} else if (__mu7_gemm__lda__ < mu0_max(1, __mu7_gemm__nrowa__)) {                                                                                                                                                      \
		__mu7_gemm__info__ = 8;                                                                                                                                                                                             \
	} else if (__mu7_gemm__ldb__ < mu0_max(1, __mu7_gemm__nrowb__)) {                                                                                                                                                      \
		__mu7_gemm__info__ = 10;                                                                                                                                                                                            \
	} else if (__mu7_gemm__ldc__ < mu0_max(1, __mu7_gemm__m__)) {                                                                                                                                                          \
		__mu7_gemm__info__ = 13;                                                                                                                                                                                            \
	}                                                                                                                                                                                                                      \
	if (__mu7_gemm__info__ != 0) {                                                                                                                                                                                         \
		mu7_xerbla("GEMM", __mu7_gemm__info__);                                                                                                                                                                             \
		goto __mu7_gemm__exit__;                                                                                                                                                                                            \
	}                                                                                                                                                                                                                      \
	if (__mu7_gemm__m__ == 0 || __mu7_gemm__n__ == 0 || ((__mu7_gemm__alpha__ == __mu7_gemm__zero__ || __mu7_gemm__k__ == 0) && __mu7_gemm__beta__ == __mu7_gemm__one__)) {                                                \
		goto __mu7_gemm__exit__;                                                                                                                                                                                            \
	}                                                                                                                                                                                                                      \
	if (__mu7_gemm__alpha__ == __mu7_gemm__zero__) {                                                                                                                                                                       \
		if (__mu7_gemm__beta__ == __mu7_gemm__zero__) {                                                                                                                                                                     \
			for (__mu7_gemm__j__ = 1;  __mu7_gemm__j__ <= __mu7_gemm__n__; ++__mu7_gemm__j__) {                                                                                                                              \
				for (__mu7_gemm__i__ = 1;  __mu7_gemm__i__ <= __mu7_gemm__m__; ++__mu7_gemm__i__) {                                                                                                                           \
					__mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) = __mu7_gemm__zero__;                                                                                   \
				}                                                                                                                                                                                                             \
			}                                                                                                                                                                                                                \
		} else {                                                                                                                                                                                                            \
			for (__mu7_gemm__j__ = 1;  __mu7_gemm__j__ <= __mu7_gemm__n__; ++__mu7_gemm__j__) {                                                                                                                              \
				for (__mu7_gemm__i__ = 1;  __mu7_gemm__i__ <= __mu7_gemm__m__; ++__mu7_gemm__i__) {                                                                                                                           \
					__mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) = __mu7_gemm__beta__                                                                                    \
						* __mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__);                                                                                                   \
				}                                                                                                                                                                                                             \
			}                                                                                                                                                                                                                \
		}                                                                                                                                                                                                                   \
		goto __mu7_gemm__exit__;                                                                                                                                                                                            \
	}                                                                                                                                                                                                                      \
	if (__mu7_gemm__notb__) {                                                                                                                                                                                              \
		if (__mu7_gemm__nota__) {                                                                                                                                                                                           \
			for (__mu7_gemm__j__ = 1;  __mu7_gemm__j__ <= __mu7_gemm__n__; ++__mu7_gemm__j__) {                                                                                                                              \
				if (__mu7_gemm__beta__ == __mu7_gemm__zero__) {                                                                                                                                                               \
					for (__mu7_gemm__i__ = 1;  __mu7_gemm__i__ <= __mu7_gemm__m__; ++__mu7_gemm__i__) {                                                                                                                        \
						__mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) = __mu7_gemm__zero__;                                                                                \
					}                                                                                                                                                                                                          \
				} else if (__mu7_gemm__beta__ != __mu7_gemm__one__) {                                                                                                                                                         \
					for (__mu7_gemm__i__ = 1;  __mu7_gemm__i__ <= __mu7_gemm__m__; ++__mu7_gemm__i__) {                                                                                                                        \
						__mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) = __mu7_gemm__beta__                                                                                 \
							* __mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__);                                                                                                \
					}                                                                                                                                                                                                          \
				}                                                                                                                                                                                                             \
				for (__mu7_gemm__l__ = 1;  __mu7_gemm__l__ <= __mu7_gemm__k__; ++__mu7_gemm__l__) {                                                                                                                           \
					__mu7_gemm__temp__ = __mu7_gemm__alpha__ * __mu7_mat__(__mu7_gemm__b__, __mu7_gemm__ldb__, __mu7_gemm__kb__, __mu7_gemm__l__, __mu7_gemm__j__);                                                            \
					for (__mu7_gemm__i__ = 1;  __mu7_gemm__i__ <= __mu7_gemm__m__; ++__mu7_gemm__i__) {                                                                                                                        \
						__mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) = __mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) \
							+ (__mu7_gemm__temp__ * __mu7_mat__(__mu7_gemm__a__, __mu7_gemm__lda__, __mu7_gemm__ka__, __mu7_gemm__i__, __mu7_gemm__l__));                                                                        \
					}                                                                                                                                                                                                          \
				}                                                                                                                                                                                                             \
			}                                                                                                                                                                                                                \
		} else {                                                                                                                                                                                                            \
			for (__mu7_gemm__j__ = 1;  __mu7_gemm__j__ <= __mu7_gemm__n__; ++__mu7_gemm__j__) {                                                                                                                              \
				for (__mu7_gemm__i__ = 1;  __mu7_gemm__i__ <= __mu7_gemm__m__; ++__mu7_gemm__i__) {                                                                                                                           \
					__mu7_gemm__temp__ = __mu7_gemm__zero__;                                                                                                                                                                   \
					for (__mu7_gemm__l__ = 1;  __mu7_gemm__l__ <= __mu7_gemm__k__; ++__mu7_gemm__l__) {                                                                                                                        \
						__mu7_gemm__temp__ = __mu7_gemm__temp__ + (__mu7_mat__(__mu7_gemm__a__, __mu7_gemm__lda__, __mu7_gemm__ka__, __mu7_gemm__l__, __mu7_gemm__i__)                                                          \
							* __mu7_mat__(__mu7_gemm__b__, __mu7_gemm__ldb__, __mu7_gemm__kb__, __mu7_gemm__l__, __mu7_gemm__j__));                                                                                              \
					}                                                                                                                                                                                                          \
					if (__mu7_gemm__beta__ == __mu7_gemm__zero__) {                                                                                                                                                            \
						__mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) = __mu7_gemm__alpha__ * __mu7_gemm__temp__;                                                          \
					} else {                                                                                                                                                                                                   \
						__mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) = __mu7_gemm__alpha__ * __mu7_gemm__temp__                                                           \
							+ __mu7_gemm__beta__ * __mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__);                                                                           \
					}                                                                                                                                                                                                          \
				}                                                                                                                                                                                                             \
			}                                                                                                                                                                                                                \
		}                                                                                                                                                                                                                   \
	} else {                                                                                                                                                                                                               \
		if (__mu7_gemm__nota__) {                                                                                                                                                                                           \
			for (__mu7_gemm__j__ = 1;  __mu7_gemm__j__ <= __mu7_gemm__n__; ++__mu7_gemm__j__) {                                                                                                                              \
				if (__mu7_gemm__beta__ == __mu7_gemm__zero__) {                                                                                                                                                               \
					for (__mu7_gemm__i__ = 1;  __mu7_gemm__i__ <= __mu7_gemm__m__; ++__mu7_gemm__i__) {                                                                                                                        \
						 __mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) = __mu7_gemm__zero__;                                                                               \
					}                                                                                                                                                                                                          \
				} else if (__mu7_gemm__beta__ != __mu7_gemm__one__) {                                                                                                                                                         \
					for (__mu7_gemm__i__ = 1;  __mu7_gemm__i__ <= __mu7_gemm__m__; ++__mu7_gemm__i__) {                                                                                                                        \
						__mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) = __mu7_gemm__beta__                                                                                 \
							* __mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__);                                                                                                \
					}                                                                                                                                                                                                          \
				}                                                                                                                                                                                                             \
				for (__mu7_gemm__l__ = 1;  __mu7_gemm__l__ <= __mu7_gemm__k__; ++__mu7_gemm__l__) {                                                                                                                           \
					__mu7_gemm__temp__ = __mu7_gemm__alpha__ * __mu7_mat__(__mu7_gemm__b__, __mu7_gemm__ldb__, __mu7_gemm__kb__, __mu7_gemm__j__, __mu7_gemm__l__);                                                            \
					for (__mu7_gemm__i__ = 1;  __mu7_gemm__i__ <= __mu7_gemm__m__; ++__mu7_gemm__i__) {                                                                                                                        \
						__mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) = __mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) \
							+ (__mu7_gemm__temp__ * __mu7_mat__(__mu7_gemm__a__, __mu7_gemm__lda__, __mu7_gemm__ka__, __mu7_gemm__i__, __mu7_gemm__l__));                                                                        \
					}                                                                                                                                                                                                          \
				}                                                                                                                                                                                                             \
			}                                                                                                                                                                                                                \
		} else {                                                                                                                                                                                                            \
			for (__mu7_gemm__j__ = 1; __mu7_gemm__j__ <= __mu7_gemm__n__; ++__mu7_gemm__j__) {                                                                                                                               \
				for (__mu7_gemm__i__ = 1; __mu7_gemm__i__ <= __mu7_gemm__m__; ++__mu7_gemm__i__) {                                                                                                                            \
					__mu7_gemm__temp__ = __mu7_gemm__zero__;                                                                                                                                                                   \
					for (__mu7_gemm__l__ = 1; __mu7_gemm__l__ <= __mu7_gemm__k__; ++__mu7_gemm__l__) {                                                                                                                         \
						__mu7_gemm__temp__ = __mu7_gemm__temp__ + (__mu7_mat__(__mu7_gemm__a__, __mu7_gemm__lda__, __mu7_gemm__ka__, __mu7_gemm__l__, __mu7_gemm__i__)                                                          \
							* __mu7_mat__(__mu7_gemm__b__, __mu7_gemm__ldb__, __mu7_gemm__kb__, __mu7_gemm__j__, __mu7_gemm__l__));                                                                                              \
					}                                                                                                                                                                                                          \
					if (__mu7_gemm__beta__ == __mu7_gemm__zero__) {                                                                                                                                                            \
						__mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) = __mu7_gemm__alpha__ * __mu7_gemm__temp__;                                                          \
					} else {                                                                                                                                                                                                   \
						__mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__) = __mu7_gemm__alpha__ * __mu7_gemm__temp__                                                           \
							+ __mu7_gemm__beta__ * __mu7_mat__(__mu7_gemm__c__, __mu7_gemm__ldc__, __mu7_gemm__n__, __mu7_gemm__i__, __mu7_gemm__j__);                                                                           \
					}                                                                                                                                                                                                          \
				}                                                                                                                                                                                                             \
			}                                                                                                                                                                                                                \
		}                                                                                                                                                                                                                   \
	}                                                                                                                                                                                                                      \
	__mu7_gemm__exit__:;                                                                                                                                                                                                   \
mu0_scope_end

MU0_END_CDECL

#endif /* !MU7_GEMM_H */

/* EOF */