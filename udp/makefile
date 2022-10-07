GCC = g++-12
EXEC = app
CFLAGS = -c -std=c++2a

INC = -I ./include

${EXEC}: main.o server.o client.o
	@${GCC} -pthread main.o server.o client.o -o ${EXEC} ${INC}

main.o: main.cpp server.o client.o
	@${GCC} ${CFLAGS} main.cpp  ${INC}

server.o: server/server.hpp server/server.cpp
	@${GCC} ${CFLAGS} server/server.cpp

client.o: client/client.hpp client/client.cpp
	@${GCC} ${CFLAGS} client/client.cpp

run: ${EXEC}
	@./${EXEC}

clean:
	@rm -f main.o server.o client.o

cleanall: 
	@rm -f main.o server.o client.o app ${EXEC}

All: ${EXEC}