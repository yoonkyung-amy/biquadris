CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -Wall -MMD
OBJECTS = action.o block.o block_I.o block_J.o block_L.o block_O.o block_S.o block_T.o block_tiny.o block_Z.o blockDispenser.o blockDispenser_I.o blockDispenser_J.o blockDispenser_L.o blockDispenser_O.o blockDispenser_S.o blockDispenser_T.o blockDispenser_tiny.o blockDispenser_Z.o Color.o command_interpreter.o graphicdisplay.o grid.o heavy.o level.o level_0.o level_1.o level_2.o level_3.o level_4.o observer.o sequence.o subject.o subscription.o terminal.o tetris.o tetrisAbstract.o tetrisDecorator.o textdisplay.o userInterface.o window.o blockShape.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = biquadris

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -L/usr/X11/lib -I/usr/X11/include

-include ${DEPENDS}

.PHONY: clean-all clean

clean-all :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS}