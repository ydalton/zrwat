CFLAGS := -Wall -Wextra -Wpedantic -std=c99
LDFLAGS := -lSDL2 -lGL -lGLEW
BIN := zrwat
OBJ := \
	main.o \
	zrwat.o \
	shader.o \
	game.o

BUILD_OBJS := $(patsubst %,build/%,$(OBJ))
BUILD_BIN := $(patsubst %,build/%,$(BIN))

build/$(BIN): $(BUILD_OBJS)
	@echo "  LD    $(BIN)"
	@$(CC) -o $(BUILD_BIN) $(BUILD_OBJS) $(LDFLAGS)

build/%.o: src/%.c
	@echo "  CC    $@"
	@$(CC) -c $< $(CFLAGS) -o $@

clean:
	@echo "  CLEAN build/"
	@rm -r build/*

.PHONY: $(BUILD_BIN) clean
