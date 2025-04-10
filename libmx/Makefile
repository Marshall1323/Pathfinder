LIB = libmx.a

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADERS = $(wildcard $(INC_DIR)/*.h)

COMPILER = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -g

ARCHIVER = ar
ARFLAGS = rcs

MKDIR_P = mkdir -p
REMOVE = rm -rf

.PHONY: build clean uninstall reinstall

build: $(LIB)

$(LIB): $(OBJ_FILES)
	$(ARCHIVER) $(ARFLAGS) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(COMPILER) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(OBJ_DIR):
	$(MKDIR_P) $@

clean:
	$(REMOVE) $(OBJ_DIR)

uninstall: clean
	$(REMOVE) $(LIB)

reinstall: uninstall build
