CFLAGS := -Wall -Wextra -I./include
LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
COMPILER := gcc
SRC_FILES := src/reset.c src/graph.c src/r_click.c src/l_click.c src/main.c

all: a.out

a.out: $(SRC_FILES)
	$(COMPILER) $(CFLAGS) $(SRC_FILES) -o spv $(LDFLAGS)

run:
	./spv 2 4

clean:
	rm -f spv
