all:	server client

gfx:	gfx.c gfx.h
	gcc -c gfx.c -o gfx.o
server:	server.cpp PaqueteDatagrama.o SocketDatagrama.o data.o spider.o gfx.o
	g++ server.cpp PaqueteDatagrama.o SocketDatagrama.o data.o gfx.o spider.o -o server -lX11 -lpthread
client:	client.cpp PaqueteDatagrama.o SocketDatagrama.o data.o
	g++ client.cpp PaqueteDatagrama.o SocketDatagrama.o data.o -o client
PaqueteDatagrama.o:	PaqueteDatagrama.h PaqueteDatagrama.cpp
	g++ PaqueteDatagrama.cpp -c
SocketDatagrama.o:	SocketDatagrama.h SocketDatagrama.cpp
	g++ SocketDatagrama.cpp -c
data.o:	data.h data.cpp
	g++ data.cpp -c
spider.o: spider.h spider.cpp
	g++ spider.cpp -c 
clean:
	rm -f *.o server client
