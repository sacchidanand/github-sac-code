SERVER=127.0.0.1

all : server client

server: dummy
	g++ -o server mserver.c -lglut -lpthread -g

client: dummy
	g++ -o client mclient.c -lglut -lpthread -lGL -g

run: dummy
	./server

ping_pong: dummy
	./client $(SERVER)

runauto: dummy
	make ping_pong &
	./random4.sh

dummy:
