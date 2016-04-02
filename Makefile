# executable and library target files
TARGET_EXE = exe
TARGET_LIB = libclab.a

# folder structure
# SRC_DIR - implementation files 
# INC_DIR - header files 
# OBJ_DIR - object files 
# DEP_DIR - dependency files 
# LIB_DIR - external library binaries 
# LIB_INC - external library headers 

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build
DEP_DIR = $(OBJ_DIR)
LIB_DIR = lib
LIB_INC = $(LIB_DIR)/include

# source files extension and corresponding compiler
SRC_EXT = c
CC = gcc

# preprocessor, compiler, and linker flags
PPFLAGS = -I$(INC_DIR) -I$(LIB_INC)
CFLAGS = $(PPFLAGS) -g -std=c99 -pedantic -Wall -Wextra \
          -Waggregate-return -Wcast-align -Wfloat-equal -Wformat=2 \
          -Wpointer-arith -Wstrict-overflow=2 -Wstrict-prototypes -Wshadow -Wwrite-strings \
          -Wcast-qual -Wmissing-prototypes -Wswitch-enum -Wswitch-default -Wunreachable-code \
          # -Werror # -Wconversion
# other useful flags: -save-temps -masm=intel -m64 -march=native -Og -O -Os -Ofast 
LFLAGS = -L$(LIB_DIR) -lm -lpcg_random

# source, object, and dependency files
SRC = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJ = $(SRC:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)
DEP = $(OBJ:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

all: $(TARGET_EXE)

# link the final executable
$(TARGET_EXE): $(OBJ)
	@echo linking: $@
	@$(CC) $^ $(LFLAGS) -o $@
	@echo successfully built: $@

# compile object files, and generate dependency files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DEP_DIR)
	@echo compiling: $< '->' $@
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(CC) $(CFLAGS) -MM $< > $(DEP_DIR)/$*.d

# include dependency files
-include $(DEP)

$(TARGET_LIB): $(OBJ)
	@echo archiving: $(TARGET_LIB)
	@ar -cr $(TARGET_LIB) $<

library: $(TARGET_LIB)

clean:
	@$(RM) -r $(TARGET_EXE) $(TARGET_LIB) $(OBJ_DIR) # $(DEP_DIR)
	@echo cleaning: $(TARGET_EXE), $(TARGET_LIB), $(OBJ_DIR) #, $(DEP_DIR)

run: $(TARGET_EXE)
	./$(TARGET_EXE)

.PHONY: all library clean run
