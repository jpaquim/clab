# 
# PCG Random Number Generation for C.
# 
# Copyright 2014 Melissa O'Neill <oneill@pcg-random.org>
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# For additional information about the PCG random number generation scheme,
# including its license and other licensing options, visit
# 
#     http://www.pcg-random.org
#

# Simplified Makefile for library compilation

TARGET_LIB = libpcg_random.a
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
CPPFLAGS += -Iinclude
CFLAGS += -O3 -std=c99

all: library
	@echo library built

library: $(TARGET_LIB)

$(TARGET_LIB): $(OBJ)
	@echo archiving: $(TARGET_LIB)
	@ar rc $@ $^
	@ranlib $@

build/%.o: src/%.c
	@mkdir -p build
	@echo compiling: $< '->' $@
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r build $(TARGET_LIB)
