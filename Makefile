CXX=g++
CXXFLAGS=-std=c++14 -MMD -g
OBJECTS=main.o game.o board.o textObserver.o subject.o queen.o player.o piece.o human.o boardIterator.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=chess

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
