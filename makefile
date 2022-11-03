EXEC = client server
CFLAGS = -O2 -c -std=c++17 -fopenmp

INC = -I ./include

all: server client

server: mserver.o request.o serialize.o unserialize.o tools.o client.o server.o model.o coding.o
	@g++-10 mserver.o request.o serialize.o unserialize.o tools.o client.o server.o model.o coding.o -fopenmp -o server ${INC}

client: mclient.o request.o serialize.o unserialize.o tools.o client.o server.o model.o coding.o
	@g++-10 mclient.o request.o serialize.o unserialize.o tools.o client.o server.o model.o coding.o -fopenmp -o client ${INC}

mclient.o: mclient.cpp serialize.o unserialize.o tools.o request.o
	@g++-10 ${CFLAGS} mclient.cpp  ${INC}

mserver.o: mserver.cpp serialize.o unserialize.o tools.o request.o
	@g++-10 ${CFLAGS} mserver.cpp  ${INC}

serialize.o: include/serialize/serialize.hpp include/serialize/serialize.cpp tools.o
	@g++-10 ${CFLAGS} include/serialize/serialize.cpp

unserialize.o: include/unserialize/unserialize.hpp include/unserialize/unserialize.cpp tools.o
	@g++-10 ${CFLAGS} include/unserialize/unserialize.cpp

tools.o: include/tools/tools.hpp include/tools/tools.cpp 
	@g++-10 ${CFLAGS} include/tools/tools.cpp

request.o: request.cpp request.hpp tools.o serialize.o unserialize.o
	@g++-10 ${CFLAGS} request.cpp

client.o: include/udp/client/client.hpp include/udp/client/client.cpp
	@g++-10 ${CFLAGS} include/udp/client/client.cpp

server.o: include/udp/server/server.hpp include/udp/server/server.cpp
	@g++-10 ${CFLAGS} include/udp/server/server.cpp

model.o: include/arithmetic_coding/model.hpp include/arithmetic_coding/model.cpp
	@g++-10 ${CFLAGS} include/arithmetic_coding/model.cpp

coding.o: include/arithmetic_coding/coding.hpp include/arithmetic_coding/coding.cpp
	@g++-10 ${CFLAGS} include/arithmetic_coding/coding.cpp

run: 
	client  \
	echo "client run" \
	server \
	echo "server run"


clean:
	@rm -f mserver.o mclient.o serialize.o unserialize.o tools.o client.o server.o request.o model.o coding.o

cleanall: 
	@rm -f mserver.o mclient.o serialize.o unserialize.o tools.o client.o server.o request.o model.o coding.o server client ${EXEC}

All: server