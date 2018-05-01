all:	server client
server:	server.cpp PaqueteDatagrama SocketDatagrama data
	g++ server.cpp PaqueteDatagrama.o SocketDatagrama.o data.o -o server
client:	client.cpp PaqueteDatagrama SocketDatagrama data
	g++ client.cpp PaqueteDatagrama.o SocketDatagrama.o data.o -o client
PaqueteDatagrama:	PaqueteDatagrama.h PaqueteDatagrama.cpp
	g++ PaqueteDatagrama.cpp -c
SocketDatagrama:	SocketDatagrama.h SocketDatagrama.cpp
	g++ SocketDatagrama.cpp -c
data:	data.h data.cpp
	g++ data.cpp -c
clean:
	rm -f *.o server client
