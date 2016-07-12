SERVER=127.0.0.1

all : server client

server: dummy
	g++ -o m_server m_server.cpp -lglut -lpthread

client: dummy
	g++ -o m_client1 m_client1.cpp -lglut -lpthread

run: dummy
	./m_server

ping_pong: dummy
	./m_client1 $(SERVER)

runauto: dummy
	make ping_pong &
	./random4.sh

dummy:
