CC := clang
CFLAGS := -g -fsanitize=address
LFLAGS := -lSDL3 -lSDL3_ttf -lvcs_sdl -lm

demo: demo.c
	$(CC) $< -o $@ $(CFLAGS) $(LFLAGS)
