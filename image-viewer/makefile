CC = cc
CFLAGS = -Wall -Wextra -std=c11 \
    $(shell sdl2-config --cflags) \
    -I/opt/homebrew/include

LDFLAGS = \
    $(shell sdl2-config --libs) \
    -L/opt/homebrew/lib \
    -lSDL2_image

SRC = image_viewer.c
OUT = viewer

$(OUT): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)
