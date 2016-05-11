###------------------------------ Definitions -------------------------------###

### Project Specific ###
-include Makefile.inc

# Makefile.inc should define
# TGT_EXE - target executable
# TGT_LIB - target library
# EXT_LIB - external libraries

TGT_EXE ?= exe
TGT_LIB ?= liblib.a


### Folder Structure ###
# SRC_DIR - implementation files
# INC_DIR - header files
# OBJ_DIR - object files
# DEP_DIR - dependency files
# LIB_DIR - external library binaries
# TST_EXE - test executable
# TST_SRC_DIR - test source files
# TST_OBJ_DIR - test build files

SRC_DIR := src
INC_DIR := include
OBJ_DIR := build
DEP_DIR := $(OBJ_DIR)
LIB_DIR := lib
TST_EXE := test_all
TST_SRC_DIR := test
TST_OBJ_DIR := $(TST_SRC_DIR)/$(OBJ_DIR)


### Program Files ###
# extension of source code files
SRC_EXT ?= c

# source, object, and dependency files
SRC := $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJ := $(SRC:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)
DEP := $(OBJ:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

# test executable, source, object, and dependency files
TST_SRC := $(wildcard $(TST_SRC_DIR)/*.$(SRC_EXT))
TST_OBJ := $(TST_SRC:$(TST_SRC_DIR)/%.$(SRC_EXT)=$(TST_OBJ_DIR)/%.o)
TST_DEP := $(TST_OBJ:%.o=%.d)

# cleaned files
CLN := $(TGT_EXE) $(TGT_LIB) $(OBJ_DIR) $(DEP_DIR) $(TST_EXE) $(TST_OBJ_DIR)


# external library directories
#EXT_LIB_DIR = $(LIB_FILE:/%=/)

# external library include directories
EXT_INC_DIR := $(EXT_LIB_DIR:%=%/include)

# external library archive files
EXT_LIB_A := $(EXT_LIB_DIR)/$(EXT_LIB).a

### Language Specific ###
# compiler
ifeq ($(SRC_EXT),c)
	CC := gcc
else ifeq ($(SRC_EXT),$(filter $(SRC_EXT), cpp cc))
	CC := g++
endif

# preprocessor flags
CPPFLAGS += -I$(INC_DIR) $(EXT_INC_DIR:%=-I%)

# compiler flags
CFLAGS += -g -std=c99 -pedantic -Wall -Wextra                              \
          -Waggregate-return -Wcast-align -Wformat=2                       \
          -Wpointer-arith -Wstrict-overflow=2 -Wstrict-prototypes -Wshadow \
          -Wwrite-strings -Wcast-qual -Wmissing-prototypes -Wswitch-enum   \
          -Wswitch-default -Wunreachable-code                              \
          -Werror # -Wconversion #  -Wfloat-equal
# other useful flags: -save-temps -masm=intel -m64 -march=native -Og -O -Os \
-Ofast -fno-stack-protector -fno-asynchronous-unwind-tables
CXXFLAGS += $(CFLAGS)

# linker flags
LDFLAGS += $(EXT_LIB_DIR:%=-L%)
LDLIBS += $(EXT_LIB:lib%=-l%) -lm


###--------------------------------- Rules ----------------------------------###

### Default Target ###
all: executable library test
	@echo all targets built


### External Libraries ###
$(LIB_DIR)/%.a:
	@echo building $@
	@$(MAKE) -C $(@D)


### Run Executable ###
run: $(TGT_EXE)
	./$(TGT_EXE)


### Main Executable ###
executable: $(TGT_EXE)

# link the final executable
$(TGT_EXE): $(OBJ) $(EXT_LIB_A)
	@echo linking: $@
	@$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	@echo successfully built: $@

# compile object files, and generate dependency files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(OBJ_DIR) $(DEP_DIR)
	@echo compiling: $< '->' $@
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -MMD -MP $< -o $@

# include dependency files
-include $(DEP)


### Library ###
library: $(TGT_LIB)

# creates static library from project's object files
$(TGT_LIB): $(OBJ)
	@echo archiving: $(TGT_LIB)
	@$(AR) -rcs $@ $^
	@echo successfully built: $@


### Test ###
test: $(TST_EXE)

# link the test executable
$(TST_EXE): $(TST_OBJ) $(TGT_LIB)
	@echo linking: $@
	@$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	@echo successfully built: $@

# compile object files, and generate dependency files
$(TST_OBJ_DIR)/%.o: $(TST_SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(TST_OBJ_DIR)
	@echo compiling: $< '->' $@
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -MMD -MP $< -o $@

# include dependency relations
-include $(TST_DEP)


### Clean ###
clean:
	@$(RM) -r $(CLN)
	@echo cleaning: $(CLN)


### Phony Targets ###
.PHONY: all run executable library test clean
