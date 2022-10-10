EXEC = client server
CFLAGS = -c -std=c++2a

INC = -I ./include

all: server client

server: mserver.o request.o serialize.o unserialize.o tools.o client.o server.o response.o
	@g++ -pthread mserver.o request.o serialize.o unserialize.o tools.o client.o server.o response.o -o server ${INC}

client: mclient.o request.o serialize.o unserialize.o tools.o client.o server.o response.o
	@g++ -pthread mclient.o request.o serialize.o unserialize.o tools.o client.o server.o response.o -o client ${INC}

mclient.o: mclient.cpp serialize.o unserialize.o tools.o request.o response.o
	@g++ ${CFLAGS} mclient.cpp  ${INC}

mserver.o: mserver.cpp serialize.o unserialize.o tools.o request.o response.o
	@g++ ${CFLAGS} mserver.cpp  ${INC}

serialize.o: include/serialize/serialize.hpp include/serialize/serialize.cpp tools.o
	@g++ ${CFLAGS} include/serialize/serialize.cpp

unserialize.o: include/unserialize/unserialize.hpp include/unserialize/unserialize.cpp tools.o
	@g++ ${CFLAGS} include/unserialize/unserialize.cpp

tools.o: include/tools/tools.hpp include/tools/tools.cpp 
	@g++ ${CFLAGS} include/tools/tools.cpp

request.o: request.cpp request.hpp tools.o serialize.o unserialize.o
	@g++ ${CFLAGS} request.cpp

response.o: response.cpp response.hpp tools.o serialize.o unserialize.o
	@g++ ${CFLAGS} response.cpp

client.o: include/udp/client/client.hpp include/udp/client/client.cpp
	@g++ ${CFLAGS} include/udp/client/client.cpp

server.o: include/udp/server/server.hpp include/udp/server/server.cpp
	@g++ ${CFLAGS} include/udp/server/server.cpp

run: 
	client  \
	echo "client run" \
	server \
	echo "server run"


clean:
	@rm -f mserver.o mclient.o serialize.o unserialize.o tools.o client.o server.o request.o response.o

cleanall: 
	@rm -f mserver.o mclient.o serialize.o unserialize.o tools.o client.o server.o request.o response.o server client ${EXEC}

All: server