EXEC = app
CFLAGS = -c -std=c++20

INC = -I ./include

${EXEC}: main.o serialize.o unserialize.o tools.o
	@g++ main.o serialize.o unserialize.o tools.o -o ${EXEC} ${INC}

main.o: main.cpp serialize.o unserialize.o tools.o
	@g++ ${CFLAGS} main.cpp  ${INC}

serialize.o: include/serialize/serialize.hpp include/serialize/serialize.cpp tools.o
	@g++ ${CFLAGS} include/serialize/serialize.cpp

unserialize.o: include/unserialize/unserialize.hpp include/unserialize/unserialize.cpp tools.o
	@g++ ${CFLAGS} include/unserialize/unserialize.cpp

tools.o: include/tools/tools.hpp include/tools/tools.cpp 
	@g++ ${CFLAGS} include/tools/tools.cpp

run: ${EXEC}
	@./${EXEC}

clean:
	@rm -f main.o serialize.o unserialize.o tools.o

cleanall: 
	@rm -f main.o serialize.o unserialize.o tools.o app ${EXEC}

All: ${EXEC}