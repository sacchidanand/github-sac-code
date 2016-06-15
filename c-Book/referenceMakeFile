FILES = itoa.c
CC= gcc
EXE = exec
CFLAGS = -g -Wall
OBJECTS = $(FILES:.c=.o)

.PHONY:all
all: $(FILES) $(EXE)

$(EXE):	$(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(FILES)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf a.out 1 exec *.o

.PHONY: clean
