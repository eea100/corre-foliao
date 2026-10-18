SRC = $(wildcard src/*.c)
CFLAGS = -Wall -Wextra -Iinclude
PKG_CONFIG ?= pkg-config

ifeq ($(OS),Windows_NT)
	RAYLIB_DIR = C:/raylib/w64devkit
	export PATH := $(RAYLIB_DIR)/bin;$(PATH)
	CC = $(RAYLIB_DIR)/bin/gcc
	OUT = CorreFoliao.exe
	CFLAGS += -I$(RAYLIB_DIR)/include
	LFLAGS = -L$(RAYLIB_DIR)/lib -lraylib -lopengl32 -lgdi32 -lwinmm
	RUN = ./$(OUT)
else
	CC = gcc
	OUT = CorreFoliao
	CFLAGS += $(shell $(PKG_CONFIG) --cflags raylib 2>/dev/null)
	LFLAGS = $(shell $(PKG_CONFIG) --libs raylib 2>/dev/null)
	ifeq ($(strip $(LFLAGS)),)
		LFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	endif
	RUN = ./$(OUT)
endif

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LFLAGS)

run: all
	$(RUN)

clean:
	rm -f CorreFoliao CorreFoliao.exe

.PHONY: all run cleanmake