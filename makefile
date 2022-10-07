EXEC = app
CFLAGS = -c -std=c++2a

INC = -I ./include

${EXEC}: main.o person.o serialize.o unserialize.o tools.o client.o server.o sum.o
	@g++ -pthread main.o person.o serialize.o unserialize.o tools.o client.o server.o sum.o -o ${EXEC} ${INC}

main.o: main.cpp serialize.o unserialize.o tools.o sum.o
	@g++ ${CFLAGS} main.cpp  ${INC}

serialize.o: include/serialize/serialize.hpp include/serialize/serialize.cpp tools.o
	@g++ ${CFLAGS} include/serialize/serialize.cpp

unserialize.o: include/unserialize/unserialize.hpp include/unserialize/unserialize.cpp tools.o
	@g++ ${CFLAGS} include/unserialize/unserialize.cpp

tools.o: include/tools/tools.hpp include/tools/tools.cpp 
	@g++ ${CFLAGS} include/tools/tools.cpp

person.o: person.cpp person.hpp tools.o serialize.o unserialize.o
	@g++ ${CFLAGS} person.cpp

sum.o: sum.cpp sum.hpp tools.o serialize.o unserialize.o
	@g++ ${CFLAGS} sum.cpp

client.o: include/udp/client.hpp include/udp/client.cpp
	@g++ ${CFLAGS} include/udp/client.cpp

server.o: include/udp/server.hpp include/udp/server.cpp
	@g++ ${CFLAGS} include/udp/server.cpp

run: ${EXEC}
	@./${EXEC}

clean:
	@rm -f main.o serialize.o unserialize.o tools.o client.o server.o sum.o person.o

cleanall: 
	@rm -f main.o serialize.o unserialize.o tools.o client.o server.o sum.o person.o app ${EXEC}

All: ${EXEC}