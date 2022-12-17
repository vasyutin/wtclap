#-----------------------------------------------------------------
# File: Makefile
# Description: Compiles example with GCC C++ compiler (including 
#    MinGW-w64 for Windows)
#
# Copyright (c) 2022 Sergey Vasyutin. All rights reserved.
#
# See the file COPYING in the top directory of this distribution 
# for more information.
#
# Note:
#    release: mingw32-make/make
#    debug:   mingw32-make/make debug=true
#-----------------------------------------------------------------
CC=gcc
CXX=g++

INCLUDES=-I../../src -I../../src/tclap/include
LDLIBS=-static
LDFLAGS=

ifeq ($(OS),Windows_NT)
	APP_BIN_NAME=wtclap-and-tclap-together.exe
else
	APP_BIN_NAME=wtclap-and-tclap-together
endif

BUILD_DIR=../../../../build

#-----------------------------------------------------------------
ifeq ($(debug), true)
	OPTIMIZE=-O0 -g3 -DDEBUG
	LDFLAGS+=-g3
	BIN_DIR=$(BUILD_DIR)/debug
else
	OPTIMIZE=-O3 -DNDEBUG
	BIN_DIR=$(BUILD_DIR)/release
endif

APP_BIN=$(BIN_DIR)/$(APP_BIN_NAME)
OBJ_DIR=$(BIN_DIR)/obj

CFLAGS=$(OPTIMIZE) $(INCLUDES) -Wall -Wextra -MMD
CXXFLAGS=-std=c++14 $(OPTIMIZE) $(INCLUDES) -Wall -Wextra -Wno-psabi -MMD

ifeq ($(OS),Windows_NT)
	MKDIR_BIN=@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)" 2> nul
	MKDIR_OBJ=@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)" 2> nul
else
	MKDIR_BIN=@mkdir -p $(BIN_DIR) 2> /dev/null
	MKDIR_OBJ=@mkdir -p $(OBJ_DIR) 2> /dev/null
endif

#-----------------------------------------------------------------
# Default target
#-----------------------------------------------------------------
all: app-binary

.PHONY: all clean

#-----------------------------------------------------------------
# Sources
#-----------------------------------------------------------------
APP_SRCS=../../src/wtclap-and-tclap-together.cpp
APP_OBJS=$(subst ../../src/,$(OBJ_DIR)/,$(subst .cpp,.o,$(APP_SRCS)))

$(OBJ_DIR)/%.o: ../../src/%.cpp
	$(MKDIR_OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(APP_BIN): $(APP_OBJS)
	$(MKDIR_BIN)
	$(CXX) $(LDFLAGS) -o $(APP_BIN) $(LDLIBS) $(APP_OBJS)
ifneq ($(debug), true)
	strip $(APP_BIN)
endif

app-binary: $(APP_BIN)

#-----------------------------------------------------------------
# Dependencies (recompile when headers have changed)
#-----------------------------------------------------------------
DEPENDENCIES=$(APP_OBJS:%.o=%.d) $(TPCL_OBJS:%.o=%.d)

-include $(DEPENDENCIES)

clean:
ifeq ($(OS),Windows_NT)
	if exist "$(subst /,\,$(BUILD_DIR))" ( for /D %%i in ("$(subst /,\,$(BUILD_DIR))\*.*") do rmdir /S /Q %%i > nul 2> nul )
	if exist "$(subst /,\,$(BUILD_DIR))" rmdir /S /Q "$(subst /,\,$(BUILD_DIR))"
else
	rm -rf "$(BUILD_DIR)"
endif
