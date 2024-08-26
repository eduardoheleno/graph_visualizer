CFLAGS := -Wall -Wextra -I./include
LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
COMPILER := gcc

all: a.out run

a.out: src/main.c
	$(COMPILER) $(CFLAGS) src/graph.c src/r_click.c src/l_click.c src/main.c -o a.out $(LDFLAGS)

run:
	./a.out

clean:
	rm -f a.out
