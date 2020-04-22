CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla 
#CXXFLAGS = -std=c++14 -Wall -MMD


EXEC = chess
OBJECTS = main.o errormessage.o cell.o colour.o board.o move.o bishop.o king.o knight.o pawn.o piece.o queen.o rook.o chessplayer.o computer.o gameplayer.o human.o level1.o position.o level2.o level3.o level4.o info.o observer.o subject.o textdisplay.o graphicsdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -L/usr/X11/lib -I/usr/X11/include
-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

