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

// mu7_operator.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition.h>

#ifndef MU7_OPERATOR_H
#define MU7_OPERATOR_H

#	undef  MU7_HAVE_ROW_MAJOR_ORDER
#	define MU7_HAVE_ROW_MAJOR_ORDER 1

#	if MU7_HAVE_ROW_MAJOR_ORDER
#	define ___mu7_mat___(__x, __m, __n, __i, __j) __x[((__i) * (__n)) + (__j)]
#	else
#	define ___mu7_mat___(__x, __m, __n, __i, __j) __x[((__j) * (__m)) + (__i)]
#	endif

#	define __mu7_vat__(__x, __i) __x[((__i) - 1)]
#	define __mu7_mat__(__x, __m, __n, __j, __i) ___mu7_mat___(__x, __m, __n, ((__j) - 1), ((__i) - 1))

#endif /* !MU7_OPERATOR_H */

/* EOF */