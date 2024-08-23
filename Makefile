CFLAGS := -Wall -Wextra
LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: a.out run

a.out: src/main.c
	gcc $(CFLAGS) src/main.c -o a.out $(LDFLAGS)

run:
	./a.out

clean:
	rm -f a.out
