CFLAGS := -Wall -Wextra -I./include
LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
COMPILER := gcc
SRC_FILES := src/graph.c src/r_click.c src/l_click.c src/main.c

all: a.out run

a.out: $(SRC_FILES)
	$(COMPILER) $(CFLAGS) $(SRC_FILES) -o a.out $(LDFLAGS)

run:
	./a.out

clean:
	rm -f a.out
