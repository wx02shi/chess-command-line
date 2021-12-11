CXX=g++
CXXFLAGS=-std=c++14 -MMD -g
OBJECTS=main.o game.o board.o textObserver.o subject.o queen.o player.o piece.o human.o empty.o knight.o pawn.o rook.o king.o bishop.o PieceVisitor.o isCheckVisitor.o isStalemateVisitor.o window.o graphicsObserver.o l1.o computer.o l2.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=chess

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
