FILES = atoi.c itoa.c
CC= gcc
EXE = exec
CFLAGS = -g
OBJECTS = $(FILES:.c=.o)

all: $(FILES) $(EXE)

$(EXE):	$(OBJECTS)
	$(CC) $(FILES) $(CFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf a.out 1 atoi itoa

rebuild: clean build
