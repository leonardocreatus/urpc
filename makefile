EXEC = app
CFLAGS = -c -std=c++20

INC = -I ./include

${EXEC}: main.o serialize.o unserialize.o
	@g++ main.o serialize.o unserialize.o -o ${EXEC} ${INC}

main.o: main.cpp serialize.o unserialize.o
	@g++ ${CFLAGS} main.cpp  ${INC}

serialize.o: include/serialize/serialize.hpp include/serialize/serialize.cpp 
	@g++ ${CFLAGS} include/serialize/serialize.cpp

unserialize.o: include/unserialize/unserialize.hpp include/unserialize/unserialize.cpp 
	@g++ ${CFLAGS} include/unserialize/unserialize.cpp

run: ${EXEC}
	@./${EXEC}

clean:
	@rm -f main.o serialize.o unserialize.o

cleanall: 
	@rm -f main.o serialize.o unserialize.o app ${EXEC}

All: ${EXEC}