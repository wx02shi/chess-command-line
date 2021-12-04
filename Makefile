CXX=g++
CXXFLAGS=-std=c++14 -MMD -g
OBJECTS=main.o game.o board.o textObserver.o subject.o queen.o player.o piece.o human.o boardIterator.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=chess

OBJECTS=main.o game.o board.o textObserver.o piece.o player.o queen.o subject.o 
DEPENDS=${OBJECTS:.o=.d}


${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
