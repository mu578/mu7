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

# mu7_source.mk
#
# Copyright (C) 2023 mu578. All rights reserved.
#

define walk-dir-recursive
	$(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk-dir-recursive, $(e)))
endef

define walk-dir
	$(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(e))
endef

ifeq ($(strip $(MU7_ROOT_PATH)),)
$(error MU7_ROOT_PATH is not set)
endif

MU7_MODULE_NAME  ?= mu7
MU7_MODULE_PATH  ?= $(MU7_ROOT_PATH)
MU7_SOURCE_FILES ?= $(call walk-dir-recursive, $(MU7_MODULE_PATH)/source)
MU7_FILTER_FILES ?= $(filter %.c, $(MU7_SOURCE_FILES))

LOCAL_SRC_FILES  += $(MU7_FILTER_FILES)
LOCAL_CFLAGS     += -I$(MU7_MODULE_PATH)

# EOF