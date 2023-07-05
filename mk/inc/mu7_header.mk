#
# # -*- coding: utf-8, tab-width: 3 -*-

#                                                          _____                                           #
#                                                         (___  )                                          #
#                                            _   _  _   _   _/ /                                           #
#                                           | | | || | | | (  _)                                           #
#                                           | |_| || |_| | / /                                             #
#                                           | ._,_| \___/ /_/                                              #
#                                           | |                                                            #
#                                           |_|                                                            #

# mu7_header.mk
#
# Copyright (C) 2023 mu578. All rights reserved.
#

ifeq ($(strip $(MU7_ROOT_PATH)),)
$(error MU7_ROOT_PATH is not set)
endif

MU7_MODULE_NAME ?= mu7
MU7_MODULE_PATH ?= $(MU7_ROOT_PATH)
LOCAL_CFLAGS    += -I$(MU7_MODULE_PATH)

# EOF