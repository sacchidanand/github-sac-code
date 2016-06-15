CC = gcc 
FILES = bfs.c
OUT_EXE= bfs

build:$(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)

r:build
	bfs

clean:
	-rm -rf *.o core bfs *.out 1

rebuild:clean build

