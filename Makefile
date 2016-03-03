CXX = g++
CXXFLAGS = -Wall -MMD -g -L/usr/X11R6/lib -lX11
EXEC = quadris
OBJECTS = quadris.o board.o window.o boarddisplay.o block.o level.o levelzero.o levelone.o leveltwo.o levelthree.o levelfour.o levelfive.o IBlock.o JBlock.o LBlock.o TBlock.o ZBlock.o OBlock.o SBlock.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

.PHONY: clean

