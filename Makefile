###------------------------------ Definitions -------------------------------###

### Project Specific ###
-include Makefile.inc

# Makefile.inc should define
# TGT_EXE - target executable
# TGT_LIB - target library

TGT_EXE ?= exe
TGT_LIB ?= lib
TGT_LIB_A := lib$(TGT_LIB).a


### Installation Folders ###
prefix ?= install
INST_INC := $(prefix)/include/$(TGT_LIB)
INST_LIB := $(prefix)/lib
INST_CLN := $(INST_INC) $(INST_LIB)/$(TGT_LIB_A)


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
TST_EXE := test-all
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
CLN := $(TGT_EXE) $(TGT_LIB_A) $(OBJ_DIR) $(DEP_DIR) $(TST_EXE) $(TST_OBJ_DIR)

# object files used in the executable
EXE_OBJ := main.o

# object files used in the library archive
LIB_OBJ := $(filter-out %$(EXE_OBJ),$(OBJ))

# external libraries
EXT_LIB_DIR := $(filter-out %.a,$(wildcard $(LIB_DIR)/*))
EXT_LIB := $(notdir $(EXT_LIB_DIR))
EXT_LIB_A := $(EXT_LIB:%=$(LIB_DIR)/lib%.a)


### Language Specific ###
# compiler
ifeq ($(SRC_EXT),c)
	CC := gcc
else ifeq ($(SRC_EXT),$(filter $(SRC_EXT),cpp cc))
	CC := g++
endif

# preprocessor flags
CPPFLAGS += -I$(INC_DIR)

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
LDFLAGS += -L$(LIB_DIR) 
LDLIBS += $(EXT_LIB:%=-l%) -lm


###--------------------------------- Rules ----------------------------------###

### Default Target ###
all: executable library test
	@echo all targets built


### External Libraries ###
$(LIB_DIR)/%.a:
	@echo building $@
	@$(MAKE) -C $(LIB_DIR)/$(*:lib%=%) install prefix=`pwd`


### Run Executable ###
run: $(TGT_EXE)
	./$(TGT_EXE)


### Main Executable ###
executable: $(TGT_EXE)

# link the final executable
$(TGT_EXE): $(EXT_LIB_A) $(OBJ)
	@echo linking: $@
	@$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $@
	@echo successfully built: $@

# compile object files, and generate dependency files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(OBJ_DIR) $(DEP_DIR)
	@echo compiling: $< '->' $@
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -MMD -MP $< -o $@

# include dependency files
-include $(DEP)


### Library ###
library: $(TGT_LIB_A)

# creates static library from project's object files
$(TGT_LIB_A): $(EXT_LIB_A) $(LIB_OBJ)
	@$(RM) $(TGT_LIB_A)
	@echo archiving: $(TGT_LIB_A)
	@$(AR) -rcs $@ $(LIB_OBJ)
	@echo merging with: $(EXT_LIB_A)
	@libtool -static -o $@ $@ $(EXT_LIB_A)
	@echo successfully built: $@


### Install ###
install: $(TGT_LIB_A)
	@echo installing to $(prefix)
	@mkdir -p $(INST_INC)
	@mkdir -p $(INST_LIB)
	@install -m 0644 $(INC_DIR)/*.h $(INST_INC)
	@install -m 0644 $^ $(INST_LIB)
	@echo successfully installed: $(INST_CLN)
#	$(file >> .uninstall,$(INST_CLN))
	@echo $(INST_CLN) >> .uninstall

uninstall:
	@$(RM) -r $(shell cat .uninstall) .uninstall
	@echo successfully uninstalled

### Test ###
test: $(TST_EXE)

# link the test executable
$(TST_EXE): $(TST_OBJ) $(TGT_LIB_A)
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
	@echo cleaning: $(CLN)
	@$(RM) -r $(CLN)

clean-libs:
	@for dir in $(EXT_LIB_DIR); do     \
		make -C $$dir uninstall clean clean-all; \
	done

clean-all: clean clean-libs

### Phony Targets ###
.PHONY: all executable library test run install uninstall clean clean-libs \
	clean-all
