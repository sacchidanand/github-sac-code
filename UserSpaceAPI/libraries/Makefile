CC=gcc
CFLAGS=-Wall
FILES= server_basic.c displayInBits.c
EXE = main	
OBJECTS= $(FILES:.c=.o)

$(EXE): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o:%.c $(FILES)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
		rm -rf main server_basic.o client_basic.o displayInBits.o

.PHONY: clean
.PHONY: all
all: $(FILES) $(EXE)	

