### Target Files
TARGET_EXE = exe
TARGET_LIB = libc-lab.a


### External library pcg_random ###
EXT = pcg_random
EXT_DIR = pcg-c-0.94


### Base Makefile ###
include MakefileBase


### Make external library ### 
$($(EXT)_A_SRC):
	@echo building $(EXT)
	@make -C $(EXT_DIR)/src
