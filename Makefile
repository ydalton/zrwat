CFLAGS := -Wall -Wextra -Wpedantic -std=c99
LDFLAGS := -lSDL2 -lGL -lGLEW
BIN := zrwat
OBJ := \
	main.o \
	zrwat.o \
	shader.o \
	game.o

BUILD_OBJS := $(patsubst %,build/%,$(OBJ))

build/$(BIN): $(BUILD_OBJS)
	@echo "  LD    $(BIN)"
	@$(CC) -o $(BIN) $(BUILD_OBJS) $(LDFLAGS)

build/%.o: src/%.c
	@echo "  CC    $@"
	@$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f build/$(BIN) $(BUILD_OBJS)

.PHONY: $(BIN)
