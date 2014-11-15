CXX = g++
CXXFLAGS = -Wall -MMD -L/opt/X11/lib -I/opt/X11/include
EXEC = flood
OBJECTS = window.o cell.o grid.o textdisplay.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
