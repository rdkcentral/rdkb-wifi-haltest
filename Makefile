#* ******************************************************************************
#* Copyright (C) 2022 Sky group of companies, All Rights Reserved
#* * --------------------------------------------------------------------------
#* * THIS SOFTWARE CONTRIBUTION IS PROVIDED ON BEHALF OF SKY PLC. 
#* * BY THE CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
#* * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#* * A PARTICULAR PURPOSE ARE DISCLAIMED
#* ******************************************************************************
#*
#*   ** Project      : cunit_hal_test
#*   ** @addtogroup  : cunit_hal_test
#*   ** @file        : makefile
#*   ** @author      : gerald.weatherup@sky.uk
#*   ** @date        : 20/05/2022
#*   **
#*   ** @brief : Makefile for hal_test
#*   ** 
#*
#* ******************************************************************************
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BIN_DIR := $(ROOT_DIR)/bin
TOP_DIR := $(ROOT_DIR)

SRC_DIRS = $(ROOT_DIR)/src
SRC_DIRS += $(ROOT_DIR)/stubs/src
INC_DIRS := $(ROOT_DIR)/../include

ifeq ($(TARGET),)
$(info TARGET NOT SET )
$(info TARGET FORCED TO Linux)
TARGET=linux
endif

$(info TARGET [$(TARGET)])

ifeq ($(TARGET),arm)
HAL_LIB_DIR := $(ROOT_DIR)/libs
LDFLAGS = -Wl,-rpath,$(HAL_LIB_DIR) -L$(HAL_LIB_DIR) -lhal_wifi
endif

.PHONY: clean list all

export LDFLAGS
export BIN_DIR
export SRC_DIRS
export INC_DIRS
export TARGET
export TOP_DIR

.PHONY: clean list build

build:
	@echo HTS [$@]
	make -C ./hts-core

list:
	@echo HTS [$@]
	make -C ./hts-core list

clean:
	@echo HTS [$@]
	make -C ./hts-core clean
