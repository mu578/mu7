// -*- coding: utf-8, tab-width: 3 -*-

//                                                          _____                                           //
//                                                         (___  )                                          //
//                                            _   _  _   _   _/ /                                           //
//                                           | | | || | | | (  _)                                           //
//                                           | |_| || |_| | / /                                             //
//                                           | ._,_| \___/ /_/                                              //
//                                           | |                                                            //
//                                           |_|                                                            //

// mu7_lsame.c
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu7/mu7_reference/mu7_lsame.h>

mu0_bool_t mu7_lsame(const mu0_tchar8_t ca, const mu0_tchar8_t cb)
{
	return (ca == cb) ? mu0_true : mu0_false;
}

/* EOF */