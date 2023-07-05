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

// mu7_xerbla.c
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu7/mu7_reference/mu7_xerbla.h>

void mu7_xerbla(const mu0_tchar8_t * srname, const mu0_sint32_t info)
{
	mu0_console_error(
		"%8s: parameter number %2d had a wrong value.\n"
		, srname
		, info
	);
}

/* EOF */